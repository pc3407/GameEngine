#pragma once

class Quad
{
public:
	Quad();
	~Quad();

public:
	void render();

private:
	ID3D11Buffer*		m_pVertexBuffer;
	UINT				m_vertexCount;

	ID3D11Buffer*		m_pIndexBuffer;
	UINT				m_indexCount;

	ID3D11InputLayout*	m_pInputLayout;

	ID3D11VertexShader*	m_pVertexShader;
	ID3D11PixelShader*	m_pPixelShader;
};