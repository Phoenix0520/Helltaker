#pragma once

class DirectWrite
{
private:
	DirectWrite();
	~DirectWrite();

private:
	static DirectWrite* instance;

public:
	static void Create();
	static void Delete();

	static DirectWrite* Get();
	static ID2D1DeviceContext* GetDC() { return deviceContext; }

	static void CreateBackBuffer();
	static void DeleteBackBuffer();

	static void RenderText(wstring& text, RECT& rect);
	static void RenderText(wstring text, Vector2 pos, float R, float G, float B, float size);
	static void DrawLine(Vector2 start, Vector2 end, float strokeWidth);
	static void SkewRectangle(RECT rect, D2D1::ColorF color, float angle, float angle2);

	static void ChangeTextType(_In_z_ WCHAR const* fontFamilyName,
		DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch);

private:
	ID2D1Factory1* factory; //2D용 Device를 생성해주기 위함
	static IDWriteFactory* writeFactory; //DirectWrite기능을 생성하기 위함

	ID2D1Device* device;
	static ID2D1DeviceContext* deviceContext;

	static ID2D1Bitmap1* bitmap; //백버퍼용(D3D : Texture2D)
	static IDXGISurface* surface; //(D3D : RTV)

	static ID2D1SolidColorBrush* brush;  //텍스트 색상
	static IDWriteTextFormat*    format; //텍스트 폰트
	//static IDWriteTextFormat* formatLarge; //텍스트 폰트

};