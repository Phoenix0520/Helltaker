#include "framework.h"
#include "Line.h"
#include "ColorShader.h"

Line::Line()
{
	m_pShader = new ColorShader(L"./Shader/HLSL/Color.hlsl");
}

Line::~Line()
{
	// COM I/F 생성된 변수는 DELETE로 해제되는 것이 아니고 
	// Release로 해제하여야 한다
	SAFE_RELEASE(m_pVertexBuffer);   // c++정점->ID3D11Buffer(Device)->pipeline(DeviceContext)
	SAFE_DELETE(m_pShader);

	for (UINT i = 0; i < m_cvLines.size(); i++)
	{
		SAFE_DELETE(m_cvLines[i]);
	}
	m_cvLines.erase(m_cvLines.begin(), m_cvLines.end());
}
void Line::ClearLine()
{
	SAFE_RELEASE(m_pVertexBuffer);
	for (UINT i = 0; i < m_cvLines.size(); i++)
	{
		SAFE_DELETE(m_cvLines[i]);
	}
	m_cvLines.erase(m_cvLines.begin(), m_cvLines.end());
}
void Line::Update(Matrix V, Matrix P)
{
	if (m_cvLines.size() == 0)
		return;

	// 자기자신에 대한 Matrix

	Matrix W, T, S;

	D3DXMatrixTranslation(&T, 0.0f, 0.0f, 0.0f);
	D3DXMatrixScaling(&S, 1.0f, 1.0f, 1.0f);

	W = S * T;

	D3DXMatrixIdentity(&W);
	m_pShader->Update(W, V, P);
}

void Line::Render()
{
	if (m_cvLines.size() == 0)
		return;
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	// IA단계  : Device
	DeviceContext->IASetVertexBuffers(0,   // slot
		1,   // buffer의 갯수
		&this->m_pVertexBuffer,
		&stride,
		&offset);
	DeviceContext->IASetInputLayout(m_pShader->GetLayout());

	// D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP
	// D3D11_PRIMITIVE_TOPOLOGY_LINELIST
	// D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	// VS _OM단계
	m_pShader->Draw(m_cvLines.size(), 0);
}

void Line::AddLine(float x1, float y1, float x2, float y2)
{
	Vector2 *pPoint = new Vector2(x1, y1);
	m_cvLines.push_back(pPoint);
	pPoint = new Vector2(x2, y2);
	m_cvLines.push_back(pPoint);
}

void Line::CreateVertexBuffer()
{
	if (m_cvLines.size() == 0)
		return;
	if (m_pVertexBuffer)
		SAFE_RELEASE(m_pVertexBuffer);

	Vertex *vertices = new Vertex[m_cvLines.size()];

	for (UINT i = 0; i < m_cvLines.size(); i++)
	{
		Vector2 *p = m_cvLines[i];
		vertices[i].Position = Vector3(p->x, p->y, 0.0f);
		vertices[i].Color = Color(1.0f, 1.0f, 0.0f, 0.0f);
	}

	// 위에 선언된 데이터를 VertextBuffer에 Setting
	// DX에서 Craete,Get()를 사용할때 변수명칭 앞에 "I"자가 있으면
	// 무조건 Desctrpion이 붙는다
	D3D11_BUFFER_DESC         desc;    // input
	{
		ZeroMemory(&desc, sizeof(desc));              // 변수가 0로 초기화
		desc.Usage = D3D11_USAGE_DYNAMIC;             // *생성한후에 변경할수  한다
		desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE; // *생성한후에 변경할수  한다
		desc.ByteWidth = sizeof(Vertex)*m_cvLines.size();              // Vector3,Color ( 3*4 + 4*4)
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;    // 12 +16 = 28

		//* D3D11_BIND_VERTEX_BUFFER = 0x1L,     정점
		//* D3D11_BIND_INDEX_BUFFER = 0x2L,      중복되는 정점을 Index로 구분하여 사용
		//* D3D11_BIND_CONSTANT_BUFFER = 0x4L,   상수Buffer, User가 HLSL에 데이터 보낼때
		// D3D11_BIND_SHADER_RESOURCE = 0x8L,    ImageFile
	}

	D3D11_SUBRESOURCE_DATA    data;    // input
	{
		ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
		data.pSysMem = vertices;
	}

	HRESULT hr = Device->CreateBuffer(&desc, &data, &m_pVertexBuffer);
	assert(SUCCEEDED(hr));
}





