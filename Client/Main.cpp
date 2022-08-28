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
    WNDCLASSEX wcex;
    ZeroMemory(&wcex, sizeof(wcex));

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = 0;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"WindowClass";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    assert(RegisterClassEx(&wcex));

    HWND hWnd = CreateWindow(wcex.lpszClassName, L"Game",
                             WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
                             0, 0,
                             CW_USEDEFAULT, CW_USEDEFAULT,
                             NULL,
                             NULL,
                             NULL,
                             NULL
    );

    assert(hWnd != NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    Core::Get()->init(hWnd);

    MSG msg;
    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        Core::Get()->progress();

    }

    return 0;
}