#pragma once
#include "Singleton.h"

class Quad;
class SceneMgr : public Singleton<SceneMgr>
{
	friend class Singleton<SceneMgr>;

private:
	SceneMgr();
	~SceneMgr();

public:
	void init(HWND hWnd, int width, int height);
	void render();

	ID3D11Device* device() { return m_pDevice; }
	ID3D11DeviceContext* dc() { return m_pImmediateContext; }
	
private:
	IDXGISwapChain*				m_pSwapChain;
	ID3D11Device*				m_pDevice;
	ID3D11DeviceContext*		m_pImmediateContext;

	ID3D11RenderTargetView*		m_pRenderTargetView;
	ID3D11DepthStencilView*		m_pDepthStencilView;

	Quad*						m_pQuad;
};