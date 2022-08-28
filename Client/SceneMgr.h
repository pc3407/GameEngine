#pragma once
#include "Singleton.h"

class Quad;
class SceneMgr : public Singleton<SceneMgr>
{
	friend class Singleton<SceneMgr>;

private:
	SceneMgr();
	~SceneMgr();

private:
	IDXGISwapChain*			m_pSwapChain;
	ID3D11Device*			m_pDevice;
	ID3D11DeviceContext*	m_pImmediateContext;

	ID3D11RenderTargetView* m_pRenderTargetView;
	ID3D11DepthStencilView* m_pDepthStencilView;

	Quad* m_pQuad;

public:
	void init(int width, int height);
	void update();
	void render();

public:
	ID3D11Device* GetDevice() { return m_pDevice; }
	ID3D11DeviceContext* GetDC() { return m_pImmediateContext; }
};