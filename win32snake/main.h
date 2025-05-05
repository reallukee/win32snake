#ifndef MAIN_H
#define MAIN_H

#include "game.h"

#define WINDOW_WIDTH_GAP    16
#define WINDOW_HEIGHT_GAP   39
#define WINDOW_WIDTH        CANVAS_WIDTH + WINDOW_WIDTH_GAP
#define WINDOW_HEIGHT       CANVAS_HEIGHT + WINDOW_HEIGHT_GAP

HINSTANCE hInst;

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow);

ATOM MyRegisterClass(
    HINSTANCE hInstance);

BOOL InitInstance(
    HINSTANCE hInstance,
    int nCmdShow);

LRESULT CALLBACK WndProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam);

#endif // !MAIN_H
