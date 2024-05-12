#pragma once

class GameScene;

class Map
{
public:
	Map() { m_tex.Load("Texture/Map/MapTile.png"); }
	~Map() { Release(); }

	void Update(int _s,int _e,float _scrollX);
	void Draw(int _s, int _e);

	//“Ç‚İ‚İŒã‰Šú‰»(©“®Às“G”z’u‚à‚·‚é)
	void SetMapData(std::string a_FileNme);

	int GetMaxHeight() { return m_data.size(); }
	int GetMaxWidth() { return m_data[0].size(); }

	Math::Vector2 GetPos(int _w, int _h) { return m_pos[_w][_h]; }
	int GetHalfSize();
	int GetMapData(int _w, int _h) { return m_data[_w][_h]; }

	void SetOwner(GameScene* _pOwner) { m_pOwner = _pOwner; }
private:
	void Init();
	void Release();

	int m_Size = 64;

	std::vector<std::vector<int>> m_data;
	std::vector<std::vector<Math::Vector2>> m_pos;
	std::vector<std::vector<Math::Matrix>> m_mat;
	std::vector<std::vector<Math::Rectangle>> m_src;

	KdTexture m_tex;

	GameScene* m_pOwner = nullptr;
};