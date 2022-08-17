#include "Common.h"
#include "Core.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(_In_ HINSTANCE hInstance,
                   _In_opt_ HINSTANCE hPrevInstance,
                   _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow)
{
#if _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    WNDCLASS wc = { 0 };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"Game";

    assert(RegisterClass(&wc));

    HWND hWnd = CreateWindowEx(0,
                               wc.lpszClassName, wc.lpszClassName,
                               WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
                               0, 0,
                               CW_USEDEFAULT, CW_USEDEFAULT,
                               NULL,
                               NULL,
                               GetModuleHandle(NULL),
                               NULL
    );

    assert(hWnd != NULL);

    ShowWindow(hWnd, SW_SHOWNORMAL);
    UpdateWindow(hWnd);

    Core::Get()->init(hWnd);

    MSG msg = { };
    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        Core::Get()->progress();
    }

    return 0;
}