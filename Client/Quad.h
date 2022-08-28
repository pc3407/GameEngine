#pragma once

struct Vertex
{
	XMFLOAT3 Position;
	XMFLOAT4 Color;
};

class Quad
{
public:
	Quad();
	~Quad();

public:
	void update();
	void render();

private:
	Vertex				m_vertices[4];
	UINT				m_vertexCount;
	ID3D11Buffer*		m_pVertexBuffer;

	UINT				m_indexCount;
	ID3D11Buffer*		m_pIndexBuffer;

	ID3D11InputLayout*	m_pInputLayout;

	ID3D11VertexShader*	m_pVertexShader;
	ID3D11PixelShader*	m_pPixelShader;
};