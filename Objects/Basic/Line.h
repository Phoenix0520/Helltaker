#pragma once
class Line
{
public:
	void  Update(Matrix V, Matrix P);
	void  Render();
	void  CreateVertexBuffer();
	void  ClearLine();

public:
	void  AddLine(float x1, float y1, float x2, float y2);
private:


private:
	struct Vertex
	{
		Vector3 Position;
		Color   Color;
	};

	vector<Vector2*>    m_cvLines;

	ID3D11Buffer		*m_pVertexBuffer = nullptr;   // c++정점->ID3D11Buffer(Device)->pipeline(DeviceContext)
	ID3D11VertexShader  *m_pVertexShader = nullptr;   // Shader로 작성된 파일을 I/F
	ID3D11PixelShader   *m_pPixelShader = nullptr;    // Shader Pixel
	ID3D10Blob          *m_pVsBlob = nullptr;          // HLSL->Binary변환
	ID3D10Blob          *m_pPsBlob = nullptr;          // HLSL->Binary변환
	ID3D11InputLayout   *m_pInputLayout = nullptr;    // 정점 --> Line,Rectangle,Triangle
													  // 입력데이터를 어떤식으로 처리?
	int   m_nVerexCount = 0;
	class  ColorShader  *m_pShader = nullptr;

public: // 생성자 & 소멸자
	Line();
	~Line();
};
