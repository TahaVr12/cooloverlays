// not sure if this works yet cause i havent tested ts on windowsings

#include "globalmouse.h"
#include <windows.h>

static bool g_lPrev = false, g_mPrev = false, g_rPrev = false;

bool GlobalMouse_Init(int /*screenWidth*/, int /*screenHeight*/)
{
    return true;
}

void GlobalMouse_Update(GlobalMouseState *out)
{
    POINT p;
    GetCursorPos(&p);
    out->x = p.x;
    out->y = p.y;

    bool l = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
    bool r = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;
    bool m = (GetAsyncKeyState(VK_MBUTTON) & 0x8000) != 0;

    out->left = l;
    out->right = r;
    out->middle = m;
    out->leftClicked = l && !g_lPrev;
    out->rightClicked = r && !g_rPrev;
    out->middleClicked = m && !g_mPrev;

    g_lPrev = l;
    g_rPrev = r;
    g_mPrev = m;
}

void GlobalMouse_SetPosition(int /*x*/, int /*y*/)
{
}

void GlobalMouse_Close()
{
}