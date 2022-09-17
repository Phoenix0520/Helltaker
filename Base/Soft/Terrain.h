#pragma once

class Terrain  // ÁöÇü,
{
private:
	Terrain();
	~Terrain();

public:
	static  Terrain* GetInstance()
	{
		static Terrain instance;
		return &instance;
	}

public:
	void    Update(Matrix V, Matrix P);
	void    Render();

	void    SetSceneMap(string sceneName);
	void    SetOffset(float x, float y)   { m_Offset = Vector2(x, y); }
	void    SetTileSize(float x, float y) { m_Size   = Vector2(x, y); }
	void    Clear();

public:
	Vector2  GetOffset()     {return  m_Offset;}
	Vector2  GetTileSize()   { return m_Size; }
	POINT    GetMapSize()    { return m_MapSize; }

private:
	class Texture*	FindTexture(wstring strMap);
	class Tile*		FindTile(wstring strMap);

private:
	class		Texture * m_pTexture;
	void		OpenFile(string strFileName);
	Vector2		m_Offset = Vector2(-500.0f, 600.0f);
	Vector2		m_Size   = Vector2(100.0f, 100.0f);
	POINT		m_MapSize = POINT{ 6,10 };

	map<wstring, class Tile*>     m_cmTiles;

};

