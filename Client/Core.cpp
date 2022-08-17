#include "Common.h"
#include "Core.h"
#include "SceneMgr.h"
#pragma warning(disable:6387)

Core::Core()
{
}

Core::~Core()
{
}

void Core::init(HWND hWnd, int width, int height)
{
    RECT rect = { 0, 0, width, height };
    AdjustWindowRect(&rect, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, false);
    MoveWindow(hWnd, 100, 100, rect.right - rect.left, rect.bottom - rect.top, 0);

    SceneMgr::Get()->init(hWnd, width, height);
}

void Core::progress()
{
    SceneMgr::Get()->render();
}