#pragma once

class GameScene;

class Map
{
public:
	Map(){}
	~Map() { Release(); }

	void Update(int _s,int _e,float _scrollX);
	void Draw(int _s, int _e);

	//読み込み後初期化(自動実行敵配置もする)
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
	//切取場所を決めてDrawする関数(Drawのループ中に呼び出す)
	//_i…ブロックの番号
	void Draw(Math::Matrix* _mat, int* _i);

	int m_Size = 64;

	std::vector<std::vector<int>> m_data;
	std::vector<std::vector<Math::Vector2>> m_pos;
	std::vector<std::vector<Math::Matrix>> m_mat;

	KdTexture m_tex;

	GameScene* m_pOwner = nullptr;
};