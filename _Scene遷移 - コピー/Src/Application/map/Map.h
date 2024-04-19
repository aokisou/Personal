#pragma once

class Map
{
public:
	Map(){}
	~Map() { Release(); }

	void Update(float _scrollX);
	void Draw();

	void MapSrc(int _i);

	//“Ç‚İ‚İŒã‰Šú‰»(©“®Às)
	void SetMapData(std::string a_FileNme);

	int GetMaxHeight() { return m_data.size(); }
	int GetMaxWidth() { return m_data[0].size(); }

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

	KdTexture m_tex;
};