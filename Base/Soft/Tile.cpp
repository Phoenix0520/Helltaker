#include "framework.h"
#include "Tile.h"

Tile::Tile()
{

}

Tile::~Tile()
{
	for (UINT i = 0; i < m_cvOrders.size(); i++)
		delete m_cvOrders[i];

	m_cvOrders.erase(m_cvOrders.begin(), m_cvOrders.end());
}

void Tile::Update(Matrix V, Matrix P)
{
	return;
	if (texturePtr)
		texturePtr->Update(V, P);
}

void Tile::Render()
{
	Matrix V, P, R;

	V = CAMERA->GetViewMatrix();
	P = CAMERA->GetProjMatrix();

	TileOrder* tileOrder = FindTileOrder(m_nOrder);

	if (!tileOrder)
		return;
	if (!texturePtr)
		return;

	texturePtr->SetImageFile(tileOrder->strImageFile);
	texturePtr->SetOffset(tileOrder->offset);
	texturePtr->SetOffsetSize(tileOrder->offsetSize);

	texturePtr->SetPosition(GetPosition());
	texturePtr->Update(V, P);
	texturePtr->Render();
}

void Tile::Reset()
{
}

void Tile::SetOrder(Texture* pTexture, int order, wstring strImageFile, Vector2 offset, Vector2 offsetSize, int flip, float angle)
{
	TileOrder* tileOrder = new TileOrder();

	if (!tileOrder)
	{
		tileOrder = new TileOrder();
		m_cvOrders.push_back(tileOrder);
	}
	texturePtr = pTexture;

	tileOrder->order = order;
	tileOrder->strImageFile = strImageFile;
	tileOrder->offset = offset;
	tileOrder-> offsetSize = offsetSize;
	tileOrder->flip = flip;    
	tileOrder->angle = angle;

	Vector2 size = SRVMANAGER->FindSpriteSize(strImageFile);

 	if (offsetSize.x < 1.0f)
		tileOrder->offsetSize.x = size.x;
	if (offsetSize.y < 1.0f)
		tileOrder->offsetSize.y = size.y;
}

TileOrder* Tile::FindTileOrder(int nOrder)
{
	TileOrder* tileOrder = nullptr;
	
	for (UINT i = 0; i < m_cvOrders.size(); i++)
	{
		if (m_cvOrders[i]->order != nOrder)
			continue;
	
	
		tileOrder = m_cvOrders[i];
		break;
	}

	
	return tileOrder;
}