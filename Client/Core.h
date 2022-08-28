#pragma once
#include "Singleton.h"

class Core : public Singleton<Core>
{
    friend class Singleton<Core>;

private:
    Core();
    ~Core();

private:
    HWND m_hWnd;

public:
    void init(HWND hWnd, int width = 1280, int height = 720);
    void progress();
    
public:
    HWND GetHandle() { return m_hWnd; }
};