// globalmouse.h
#pragma once

struct GlobalMouseState
{
    int x = 0, y = 0;
    bool left = false, middle = false, right = false;
    bool leftClicked = false, middleClicked = false, rightClicked = false;
};

bool GlobalMouse_Init(int screenWidth, int screenHeight); // false if no device or permission
void GlobalMouse_Update(GlobalMouseState *out);           // udpate bradar
void GlobalMouse_SetPosition(int x, int y);               // self explanatory
void GlobalMouse_Close();                                 // self explanatory