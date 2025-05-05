#include "main.h"

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    MyRegisterClass(hInstance);

    BOOL initInstanceResult = InitInstance(hInstance, nCmdShow);

    if (!initInstanceResult)
    {
        return FALSE;
    }

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);

        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(
    HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize         = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(101));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = L"Win32Snake";
    wcex.hIconSm        = NULL;

    return RegisterClassEx(&wcex);
}

BOOL InitInstance(
    HINSTANCE hInstance,
    int nCmdShow)
{
    DWORD dwStyle = WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX;

    RECT rect = {
        0,
        0,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
    };

    AdjustWindowRect(&rect, dwStyle, FALSE);

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    int x = (screenWidth - WINDOW_WIDTH) / 2;
    int y = (screenHeight - WINDOW_HEIGHT) / 2;

    hInst = hInstance;

    HWND hWnd = CreateWindowEx(
        WS_EX_COMPOSITED,
        L"Win32Snake",
        L"Win32Snake",
        dwStyle,
        x,
        y,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    BOOL value = TRUE;

    DwmSetWindowAttribute(
        hWnd,
        DWMWA_USE_IMMERSIVE_DARK_MODE,
        &value,
        sizeof(value)
    );

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);

    UpdateWindow(hWnd);

    return TRUE;
}

LRESULT CALLBACK WndProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        InitGame(hWnd);

        break;

    case WM_DESTROY:
        PostQuitMessage(0);

        break;

    case WM_GETMINMAXINFO:
    {
        MINMAXINFO* pInfo = (MINMAXINFO*)lParam;

        pInfo->ptMinTrackSize.x = WINDOW_WIDTH;
        pInfo->ptMinTrackSize.y = WINDOW_HEIGHT;
        pInfo->ptMaxTrackSize.x = WINDOW_WIDTH;
        pInfo->ptMaxTrackSize.y = WINDOW_HEIGHT;
    }

    break;

    case WM_TIMER:
    {
        BOOL moveSnakeResult = MoveSnake();

        if (!moveSnakeResult)
        {
            GameOver(hWnd);
        }

        InvalidateRect(hWnd, NULL, TRUE);
    }

    break;

    case WM_PAINT:
    {
        PAINTSTRUCT lpPaint;

        HDC hDC = BeginPaint(hWnd, &lpPaint);

        DrawField(hDC);
        DrawSnake(hDC);
        DrawSnakeFood(hDC);

        EndPaint(hWnd, &lpPaint);
    }

    break;

    case WM_KEYDOWN:
        HandleInput(hWnd, wParam);

        break;

    default:
        return DefWindowProc(
            hWnd,
            message,
            wParam,
            lParam
        );
    }

    return 0;
}
