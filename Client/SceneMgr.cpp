#include "Common.h"
#include "SceneMgr.h"

#include "Core.h"

#include "Quad.h"

SceneMgr::SceneMgr()
	: m_pSwapChain(nullptr)
	, m_pDevice(nullptr)
	, m_pImmediateContext(nullptr)
	, m_pRenderTargetView(nullptr)
	, m_pDepthStencilView(nullptr)
	, m_pQuad(nullptr)
{
}

SceneMgr::~SceneMgr()
{
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pImmediateContext);
	SAFE_RELEASE(m_pRenderTargetView);
	SAFE_RELEASE(m_pDepthStencilView);

	SAFE_DELETE(m_pQuad);
}

void SceneMgr::init(int width, int height)
{
	HWND hWnd = Core::Get()->GetHandle();

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	// V-sync on
	//sd.BufferDesc.RefreshRate.Numerator = 60;
	//sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = true;

	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

//#if _DEBUG
//	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
//#endif

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		creationFlags,
		featureLevels,
		ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION,
		&sd,
		&m_pSwapChain,
		&m_pDevice,
		NULL,
		&m_pImmediateContext);

	assert(SUCCEEDED(hr));

	ID3D11Texture2D* pBackBuffer;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	assert(SUCCEEDED(hr));

	hr = m_pDevice->CreateRenderTargetView(pBackBuffer, 0, &m_pRenderTargetView);
	assert(SUCCEEDED(hr));

	SAFE_RELEASE(pBackBuffer);

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

	ID3D11Texture2D* pDepthStencilBuffer;
	hr = m_pDevice->CreateTexture2D(&depthStencilDesc, 0, &pDepthStencilBuffer);
	assert(SUCCEEDED(hr));

	hr = m_pDevice->CreateDepthStencilView(pDepthStencilBuffer, 0, &m_pDepthStencilView);
	assert(SUCCEEDED(hr));

	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = static_cast<float>(width);
	vp.Height = static_cast<float>(height);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	m_pImmediateContext->RSSetViewports(1, &vp);

	m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	m_pQuad = new Quad();
}

void SceneMgr::update()
{
	m_pQuad->update();
}

void SceneMgr::render()
{
	FLOAT color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, color);
	m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	m_pQuad->render();

	m_pSwapChain->Present(0, 0);
}