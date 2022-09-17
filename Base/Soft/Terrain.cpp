#include  "framework.h"
#include  "Terrain.h"
#include  "Tile.h"

///////////////////////////////////////////////////////////
// 생성자
//////////////////////////////////////////////////////////
Terrain::Terrain()
{
	wstring imgFile   =  L"./Images/Floor/Floor1.png";
	wstring shaderFile = L"./Shader/HLSL/Texture.hlsl";

	m_pTexture = new Texture(imgFile, shaderFile);
}

Terrain::~Terrain()
{
	for (auto v : m_cmTiles)
	{
		SAFE_DELETE(v.second);
	}
	m_cmTiles.clear();

}

void Terrain::Update(Matrix V, Matrix P)
{
	for (int i = 0; i < 10; i++)
	{
		for (auto v : m_cmTiles)
		{
			v.second->SetOrder(i);
			v.second->Update(V, P);
		}
	}
}

void Terrain::Render()
{
	for (int i = 0; i < 10; i++)
	{
		for (auto v : m_cmTiles)
		{
			v.second->SetOrder(i);
			v.second->Render();
		}
	}
}

void Terrain::SetSceneMap(string sceneName)
{
	string str = "./" + sceneName + ".txt";
	OpenFile(str);
}

void Terrain::Clear()
{
}

Texture * Terrain::FindTexture(wstring strMap)
{

	return nullptr;
}

Tile * Terrain::FindTile(wstring strMap)
{
	if (m_cmTiles.find(strMap) != m_cmTiles.end())
		return m_cmTiles.find(strMap)->second;

	return nullptr;
}

void Terrain::OpenFile(string strFileName)
{
	FILE  *fp;

	printf("%s\n", strFileName.c_str());
	fp = fopen(strFileName.c_str(), "r");
	if (fp == NULL)
		return;

	// Ascii File인 경우 1 Line씩 데이터를 read

	while (1)
	{
		char buf[1024];
		int  X, Y;
		char imgBuf[200];
		int  nOrder =0;
		Vector2 Offset = Vector2(0.0f,0.0f);
		Vector2 OffsetSize = Vector2(0.0f, 0.0f);
		int   nFlip = 0;
		float nAngle = 0.0f;

		if (!fgets(buf, 1024, fp)) 
			break;
	//	buf[strlen(buf) - 1] = '\0'; // NewLine데이터 삭제

		if (strlen(buf) < 10)
			continue;

		sscanf(buf, "%d %d %s %d", &X, &Y, imgBuf,&nOrder);
		
		string   str = imgBuf;
		wstring  str2;
		str2.assign(str.begin(), str.end());

		printf("%d %d %ls\n", X,Y, str2.c_str());

		// imgBuf의 내용은 SRVMANAGER에 저장
		wstring strImage = L"./Images/" + str2;
		// Texture에 저장
	
		// 6 * 10
		wstring strMap = to_wstring(X) + L"," + to_wstring(Y);

		SRVMANAGER->CreateShaderResourceView(strImage);
		Vector2 position = Vector2(m_Offset.x + X * m_Size.x,
			m_Offset.y - Y * m_Size.y);
		m_pTexture->SetPosition(position);

		m_pTexture->SetOffsetSize(SRVMANAGER->FindSpriteSize(strImage));
		
		Tile *pTile = FindTile(strMap);

		if (!pTile)
		{
			pTile = new Tile();
			m_cmTiles.insert(make_pair(strMap, pTile));
		}

		pTile->SetPosition(position);
		pTile->SetOrder(m_pTexture, nOrder, strImage, Offset, OffsetSize, nFlip, nAngle);
		
	}
	fclose(fp);


}


