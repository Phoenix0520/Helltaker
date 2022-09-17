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
	// CPU ���� �� �ڿ��� �����ϴ� �����Դϴ�.

	// ���� �Ҵ��Ҽ� ������ ������ �Ұ����մϴ�.
	// �Ҵ��� Desc �� ��û�Ͽ� �Ҵ��մϴ�.
	// ������ Release() ��� �Լ��� ȣ���Ͽ� �����մϴ�.

	ID3D11DeviceContext*	deviceContext = nullptr; 
	// GPU ���� Device �� ���� ������ ����ֽ��ϴ�.

	IDXGISwapChain*			swapChain = nullptr; 
	// ���� ���۸��� �ϴµ� ���˴ϴ�.


	ID3D11RenderTargetView* rtv = nullptr; // ���� �׷��� ����

};