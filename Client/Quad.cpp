#include "Common.h"
#include "Quad.h"

#include "SceneMgr.h"

Quad::Quad()
	: m_vertexCount(0)
	, m_indexCount(0)
{
	m_vertices[0].Position = XMFLOAT3(-0.5f, 0.5f, 0.0f);
	m_vertices[0].Color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	
	m_vertices[1].Position = XMFLOAT3(+0.5f, 0.5f, 0.0f);
	m_vertices[1].Color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	
	m_vertices[2].Position = XMFLOAT3(-0.5f, -0.5f, 0.0f);
	m_vertices[2].Color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	
	m_vertices[3].Position = XMFLOAT3(0.5f, -0.5f, 0.0f);
	m_vertices[3].Color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	
	m_vertexCount = ARRAYSIZE(m_vertices);

	D3D11_BUFFER_DESC desc;
	desc.ByteWidth = sizeof(Vertex) * m_vertexCount;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = m_vertices;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	HRESULT hr = SceneMgr::Get()->GetDevice()->CreateBuffer(&desc, &initData, &m_pVertexBuffer);
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

	hr = SceneMgr::Get()->GetDevice()->CreateBuffer(&desc, &initData, &m_pIndexBuffer);
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

	hr = SceneMgr::Get()->GetDevice()->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &m_pVertexShader);
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

	hr = SceneMgr::Get()->GetDevice()->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &m_pPixelShader);
	assert(SUCCEEDED(hr));

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
			 D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,
			 D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	SceneMgr::Get()->GetDevice()->CreateInputLayout(layout, ARRAYSIZE(layout), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &m_pInputLayout);
	assert(SUCCEEDED(hr));
}

Quad::~Quad()
{
	
}

void Quad::update()
{
	if (KeyMgr::Get()->GetPress(Key::Right))
		m_vertices[3].Position.x += 2.0f * TimeMgr::Get()->GetDelta();
	else if (KeyMgr::Get()->GetPress(Key::Left))
		m_vertices[3].Position.x -= 2.0f * TimeMgr::Get()->GetDelta();

	SceneMgr::Get()->GetDC()->UpdateSubresource(m_pVertexBuffer, 0, NULL, m_vertices, sizeof(Vertex) * m_vertexCount, 0);
}

void Quad::render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	SceneMgr::Get()->GetDC()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	SceneMgr::Get()->GetDC()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	SceneMgr::Get()->GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	SceneMgr::Get()->GetDC()->IASetInputLayout(m_pInputLayout);

	SceneMgr::Get()->GetDC()->VSSetShader(m_pVertexShader, NULL, 0);
	SceneMgr::Get()->GetDC()->PSSetShader(m_pPixelShader, NULL, 0);

	SceneMgr::Get()->GetDC()->DrawIndexed(6, 0, 0);
}