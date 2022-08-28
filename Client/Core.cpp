#include "Common.h"
#include "Core.h"
#pragma warning(disable:6387)

Core::Core()
    : m_hWnd(NULL)
{
}

Core::~Core()
{
}

void Core::init(HWND hWnd, int width, int height)
{
    m_hWnd = hWnd;

    RECT rect = { 0, 0, width, height };
    AdjustWindowRect(&rect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, false);
    MoveWindow(hWnd, 100, 100, rect.right - rect.left, rect.bottom - rect.top, 0);

    TimeMgr::Get()->init();
    KeyMgr::Get()->init();
    SceneMgr::Get()->init(width, height);
}

void Core::progress()
{
    TimeMgr::Get()->update();
    KeyMgr::Get()->update();
    SceneMgr::Get()->update();

    SceneMgr::Get()->render();

    TimeMgr::Get()->render();
}