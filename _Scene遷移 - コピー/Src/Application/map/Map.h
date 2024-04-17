#pragma once

class Map
{
public:
	Map(){}
	~Map() { Release(); }

	void Update();
	void Draw();

	//“Ç‚İ‚İŒã‰Šú‰»(©“®Às)
	void SetMapData(std::string a_FileNme);

	void SetTexture(KdTexture* _pTex) { m_pTex = _pTex; }

	int GetWidth() { return m_data.size(); }
	int GetHeight() { return m_data[0].size(); }

	Math::Vector2 GetPos(int _w, int _h) { return m_pos[_w][_h]; }
	int GetHalfSize();
	int GetMapData(int _w, int _h) { return m_data[_w][_h]; }

private:
	void Init();
	void Release();

	int m_Size = 64;

	std::vector<std::vector<int>> m_data;
	std::vector<std::vector<Math::Vector2>> m_pos;
	std::vector<std::vector<Math::Matrix>> m_mat;

	KdTexture* m_pTex;
};