#pragma once

class Slate : public GameObject
{
public:
	Slate();
	~Slate();

public:
	void Update(Matrix V, Matrix P) override;
	void Render() override;
	void Reset() override;

	int GetState() { return state; }
	void SetState(int val) { state = val; }

private:
	class Texture* texture = nullptr;

	int state = 0;
	bool plus = true;
	float val = -10.0f;

private:
	ID3D11Device*			device = nullptr;
	// CPU 영역 및 자원을 생성하는 영역입니다.

	// 직접 할당할수 없으며 해제도 불가능합니다.
	// 할당은 Desc 에 요청하여 할당합니다.
	// 해제는 Release() 라는 함수를 호출하여 해제합니다.

	ID3D11DeviceContext*	deviceContext = nullptr; 
	// GPU 영역 Device 에 대한 설정도 담겨있습니다.

	IDXGISwapChain*			swapChain = nullptr; 
	// 더블 버퍼링을 하는데 사용됩니다.


	ID3D11RenderTargetView* rtv = nullptr; // 실제 그려질 영역

};