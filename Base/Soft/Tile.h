#pragma once
class  TileOrder
{
public:
	TileOrder() {};
	~TileOrder() {};

public:
	wstring strImageFile;
	Vector2 offset = Vector2(0.0f, 0.0f);
	Vector2 offsetSize = Vector2(0.0f, 0.0f);

	int     order		= 0;
	int		type		= 0;
	int		objectType	= 0;
	int     flip		= 0;    // X Flip, Y Flip
	float   angle		= 0.0f;

};

class Tile : public GameObject
{
public: // 持失切 & 社瑚切
	Tile();
	~Tile();

public: // override
	void  Update(Matrix V, Matrix P)  override;
	void  Render()  override;
	void  Reset()   override;

public:
	void  SetOrder(int nOrder) { m_nOrder = nOrder; }
	void  SetOrder(Texture* pTexture, int order, wstring strImageFile, Vector2 offset, Vector2 offsetSize, int flip, float angle);

	TileOrder*  FindTileOrder(int nOrder);

private:
	class Texture* texturePtr = nullptr;

	vector<TileOrder*>  m_cvOrders;
	int      m_nOrder = 0;
	
};
