#include "raylib.h"
#include "globalmouse.h"
#include <iostream>

int main()
{
    SetConfigFlags(FLAG_WINDOW_TRANSPARENT |
                   FLAG_WINDOW_UNDECORATED |
                   FLAG_WINDOW_TOPMOST);

    InitWindow(1920, 1080, "overlay");

    int mon = GetCurrentMonitor();
    SetWindowSize(GetMonitorWidth(mon), GetMonitorHeight(mon));
    SetWindowPosition(0, 0);

    SetTargetFPS(165);

    if (!GlobalMouse_Init(GetMonitorWidth(mon), GetMonitorHeight(mon)))
    {
        TraceLog(LOG_ERROR, "No mouse device opened. Add yourself to the 'input' group:");
        TraceLog(LOG_ERROR, "  sudo usermod -aG input $USER   (then log out and back in)");
        CloseWindow();
        return 1;
    }

    for (int i = 0; i < 60; i++)
    {
        BeginDrawing();
        ClearBackground(BLANK);
        EndDrawing();
        if (IsCursorOnScreen())
            break;
    }
    if (IsCursorOnScreen())
    {
        Vector2 m = GetMousePosition();
        GlobalMouse_SetPosition((int)m.x, (int)m.y);
    }

    SetWindowState(FLAG_WINDOW_MOUSE_PASSTHROUGH);

    GlobalMouseState mouse;

    while (!WindowShouldClose())
    {
        GlobalMouse_Update(&mouse);

        Vector2 p = {(float)mouse.x, (float)mouse.y};
        if (mouse.leftClicked)
            std::cout << "left click\n";
        if (mouse.rightClicked)
            std::cout << "right click\n";
        if (mouse.middleClicked)
            std::cout << "i middle mouse\n";

        BeginDrawing();
        ClearBackground(BLANK);

        // DrawCircleV(p, 4, WHITE); // this draws a circle at the cursor
        EndDrawing();
    }

    GlobalMouse_Close();
    CloseWindow();
    return 0;
}
