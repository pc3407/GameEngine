#pragma once
#include <assert.h>

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#define SAFE_RELEASE(p)     { if(p) { (p)->Release(); (p) = NULL; } }
#define SAFE_DELETE(p)      { if(p) { delete (p); (p) = NULL; } }
#define SAFE_DELETE_ARRAR(p){ if(p) { delete [] (p); (p) = NULL; } }

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

private:
    IDXGISwapChain          *pSwapChain;
    ID3D11Device            *pDevice;
    ID3D11DeviceContext     *pImmediateContext;

    ID3D11RenderTargetView  *pRenderTargetView;
    ID3D11DepthStencilView  *pDepthStencilView;
};