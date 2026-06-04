
// gets the mouse position STRAIGHT from das kernel popcorn

#include "globalmouse.h"

#include <linux/input.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <cstring>
#include <cstdio>
#include <vector>

#define BITS_PER_LONG (sizeof(long) * 8)
#define NBITS(x) ((((x) - 1) / BITS_PER_LONG) + 1)
#define TEST_BIT(bit, arr) (((arr)[(bit) / BITS_PER_LONG] >> ((bit) % BITS_PER_LONG)) & 1)

static std::vector<int> g_fds;     // open mouse device fds
static int g_w = 1920, g_h = 1080; // screen boundings
static int g_x = 0, g_y = 0;       // accumulated cursor positionings
static bool g_l = false, g_m = false, g_r = false;
static bool g_lPrev = false, g_mPrev = false, g_rPrev = false;

static bool isMouse(int fd) // is this evdev device a mouse bro
{
    unsigned long ev[NBITS(EV_MAX)] = {0};
    unsigned long rel[NBITS(REL_MAX)] = {0};
    unsigned long key[NBITS(KEY_MAX)] = {0};

    if (ioctl(fd, EVIOCGBIT(0, sizeof(ev)), ev) < 0)
        return false;
    if (!TEST_BIT(EV_REL, ev) || !TEST_BIT(EV_KEY, ev))
        return false;

    ioctl(fd, EVIOCGBIT(EV_REL, sizeof(rel)), rel);
    if (!TEST_BIT(REL_X, rel) || !TEST_BIT(REL_Y, rel))
        return false;

    ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(key)), key);
    return TEST_BIT(BTN_LEFT, key); // has a left mouse buttonings
}

bool GlobalMouse_Init(int screenWidth, int screenHeight)
{
    g_w = screenWidth > 0 ? screenWidth : 1920;
    g_h = screenHeight > 0 ? screenHeight : 1080;
    g_x = g_w / 2; // ştart in das middles
    g_y = g_h / 2;

    DIR *dir = opendir("/dev/input");
    if (!dir)
        return false;

    struct dirent *e;
    while ((e = readdir(dir)) != nullptr)
    {
        if (strncmp(e->d_name, "event", 5) != 0)
            continue;

        char path[300];
        snprintf(path, sizeof(path), "/dev/input/%s", e->d_name);

        int fd = open(path, O_RDONLY | O_NONBLOCK);
        if (fd < 0)
            continue; // usually permission denied

        if (isMouse(fd))
            g_fds.push_back(fd);
        else
            close(fd);
    }
    closedir(dir);

    return !g_fds.empty();
}

void GlobalMouse_Update(GlobalMouseState *out)
{
    g_lPrev = g_l;
    g_mPrev = g_m;
    g_rPrev = g_r;

    struct input_event ev;
    for (int fd : g_fds)
    {
        // drain everythin this device queued since das last frame (non blocking tho)
        while (read(fd, &ev, sizeof(ev)) == (ssize_t)sizeof(ev))
        {
            if (ev.type == EV_REL)
            {
                if (ev.code == REL_X)
                    g_x += ev.value;
                else if (ev.code == REL_Y)
                    g_y += ev.value;
            }
            else if (ev.type == EV_KEY)
            {
                bool down = ev.value != 0; // 1 is press 0 is release
                if (ev.code == BTN_LEFT)
                    g_l = down;
                else if (ev.code == BTN_RIGHT)
                    g_r = down;
                else if (ev.code == BTN_MIDDLE)
                    g_m = down;
            }
        }
    }

    // keep das cursor on thi screen
    if (g_x < 0)
        g_x = 0;
    if (g_x > g_w - 1)
        g_x = g_w - 1;
    if (g_y < 0)
        g_y = 0;
    if (g_y > g_h - 1)
        g_y = g_h - 1;

    out->x = g_x;
    out->y = g_y;
    out->left = g_l;
    out->middle = g_m;
    out->right = g_r;
    out->leftClicked = g_l && !g_lPrev;
    out->middleClicked = g_m && !g_mPrev;
    out->rightClicked = g_r && !g_rPrev;
}

void GlobalMouse_SetPosition(int x, int y)
{
    if (x < 0)
        x = 0;
    if (x > g_w - 1)
        x = g_w - 1;
    if (y < 0)
        y = 0;
    if (y > g_h - 1)
        y = g_h - 1;
    g_x = x;
    g_y = y;
}

void GlobalMouse_Close()
{
    for (int fd : g_fds)
        close(fd);
    g_fds.clear();
}