#include "Common.h"
#include "Quad.h"

#include "SceneMgr.h"

struct Vertex
{
	XMFLOAT3 Position;
	XMFLOAT4 Color;
};

Quad::Quad()
	: m_vertexCount(0)
	, m_indexCount(0)
{
	Vertex vertices[4];

	vertices[0].Position = XMFLOAT3(-0.5f, 0.5f, 0.0f);
	vertices[0].Color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[1].Position = XMFLOAT3(+0.5f, 0.5f, 0.0f);
	vertices[1].Color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[2].Position = XMFLOAT3(-0.5f, -0.5f, 0.0f);
	vertices[2].Color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[3].Position = XMFLOAT3(0.5f, -0.5f, 0.0f);
	vertices[3].Color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	m_vertexCount = ARRAYSIZE(vertices);

	D3D11_BUFFER_DESC desc;
	desc.ByteWidth = sizeof(Vertex) * m_vertexCount;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = vertices;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	HRESULT hr = SceneMgr::Get()->device()->CreateBuffer(&desc, &initData, &m_pVertexBuffer);
	assert(SUCCEEDED(hr));

	UINT indices[6] = { 0, 1, 2, 2, 1, 3 };

	m_indexCount = ARRAYSIZE(indices);

	desc.ByteWidth = sizeof(UINT) * m_indexCount;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	initData.pSysMem = indices;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	hr = SceneMgr::Get()->device()->CreateBuffer(&desc, &initData, &m_pIndexBuffer);
	assert(SUCCEEDED(hr));

	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* vsBlob = nullptr;
	hr = D3DCompileFromFile(L"Box.hlsl",
		NULL,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"VS",
		"vs_5_0",
		flags, 0,
		&vsBlob, nullptr);

	assert(SUCCEEDED(hr));

	hr = SceneMgr::Get()->device()->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &m_pVertexShader);
	assert(SUCCEEDED(hr));

	ID3DBlob* psBlob = nullptr;
	hr = D3DCompileFromFile(L"Box.hlsl",
		NULL,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"PS",
		"ps_5_0",
		flags, 0,
		&psBlob, nullptr);

	assert(SUCCEEDED(hr));

	hr = SceneMgr::Get()->device()->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &m_pPixelShader);
	assert(SUCCEEDED(hr));

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
			 D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,
			 D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	SceneMgr::Get()->device()->CreateInputLayout(layout, ARRAYSIZE(layout), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &m_pInputLayout);
	assert(SUCCEEDED(hr));
}

Quad::~Quad()
{

}

void Quad::render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	SceneMgr::Get()->dc()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	SceneMgr::Get()->dc()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	SceneMgr::Get()->dc()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	SceneMgr::Get()->dc()->IASetInputLayout(m_pInputLayout);

	SceneMgr::Get()->dc()->VSSetShader(m_pVertexShader, NULL, 0);
	SceneMgr::Get()->dc()->PSSetShader(m_pPixelShader, NULL, 0);

	SceneMgr::Get()->dc()->DrawIndexed(m_indexCount, 0, 0);
}