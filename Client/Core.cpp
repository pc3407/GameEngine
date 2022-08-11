#include "Core.h"

#pragma warning(disable:6387)

Core::Core()
    : pSwapChain(nullptr)
    , pDevice(nullptr)
    , pImmediateContext(nullptr)
    , pRenderTargetView(nullptr)
    , pDepthStencilView(nullptr)
{
}

Core::~Core()
{
    SAFE_RELEASE(pSwapChain);
    SAFE_RELEASE(pDevice);
    SAFE_RELEASE(pImmediateContext);
}

void Core::init(HWND hWnd, int width, int height)
{
    RECT rect = { 0, 0, width, height };
    AdjustWindowRect(&rect, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, false);
    MoveWindow(hWnd, 100, 100, rect.right - rect.left, rect.bottom - rect.top, 0);

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = 1280;
    sd.BufferDesc.Height = 720;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = true;

    D3D_FEATURE_LEVEL featureLevels[] = {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1
    };

    HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL,
                                               D3D_DRIVER_TYPE_HARDWARE,
                                               NULL,
                                               0,
                                               featureLevels,
                                               ARRAYSIZE(featureLevels),
                                               D3D11_SDK_VERSION,
                                               &sd,
                                               &pSwapChain,
                                               &pDevice,
                                               NULL,
                                               &pImmediateContext);

    assert(SUCCEEDED(hr));

    ID3D11Texture2D* backBuffer;
    pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
    pDevice->CreateRenderTargetView(backBuffer, 0, &pRenderTargetView);
    SAFE_RELEASE(backBuffer);

    D3D11_TEXTURE2D_DESC depthStencilDesc;
    depthStencilDesc.Width = width;
    depthStencilDesc.Height = height;
    depthStencilDesc.MipLevels = 1;
    depthStencilDesc.ArraySize = 1;
    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    
    depthStencilDesc.SampleDesc.Count = 1;
    depthStencilDesc.SampleDesc.Quality = 0;
    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilDesc.CPUAccessFlags = 0;
    depthStencilDesc.MiscFlags = 0;

    ID3D11Texture2D* depthStencilBuffer;
    hr = pDevice->CreateTexture2D(&depthStencilDesc, 0, &depthStencilBuffer);
    assert(SUCCEEDED(hr));

    hr = pDevice->CreateDepthStencilView(depthStencilBuffer, 0, &pDepthStencilView);
    assert(SUCCEEDED(hr));
    SAFE_RELEASE(depthStencilBuffer);

    D3D11_VIEWPORT vp;
    vp.TopLeftX = 0.0f;
    vp.TopLeftY = 0.0f;
    vp.Width = static_cast<float>(width);
    vp.Height = static_cast<float>(height);
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;

    pImmediateContext->RSSetViewports(1, &vp);

    pImmediateContext->OMSetRenderTargets(1, &pRenderTargetView, pDepthStencilView);
}

void Core::progress()
{
    FLOAT color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    pImmediateContext->ClearRenderTargetView(pRenderTargetView, color);



    pSwapChain->Present(1, 0);
}