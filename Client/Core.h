#pragma once
#include "Singleton.h"

class Core : public Singleton<Core>
{
    friend class Singleton<Core>;

private:
    Core();
    ~Core();

public:
    void init(HWND hWnd, int width = 1280, int height = 720);
    void progress();
};