#pragma once

enum class State
{
	none,
	open,
	close
};

struct ANode
{
	Math::Matrix mat;
	Math::Vector2 pos;
	Math::Vector2 num;
	int data;
	int cost;	//コスト
	int h;		//想定スコア
	int score;	//スコア
	State state;
	std::shared_ptr<ANode> rootNode;
};

class Scene
{
private:
	std::shared_ptr<ANode> SearchMinScoreNode();
	std::vector<std::shared_ptr<ANode>> GetPath(std::shared_ptr<ANode> _node);
	void OpenNodeState(std::shared_ptr<ANode> _node);
	void Move(std::shared_ptr<ANode> _node);
	float GetAngleDeg(Math::Vector2 src, Math::Vector2 dest);
	void Reset();

	std::vector<std::vector<std::shared_ptr<ANode>>> m_nodeList;
	std::vector<std::shared_ptr<ANode>> m_minScoreNode;
	std::shared_ptr<ANode> m_nowMinScoreNode;

	Math::Vector2 m_goalNum;

	Math::Matrix m_pmat;
	Math::Vector2 m_ppos;
	Math::Vector2 m_pmove;
	Math::Vector2 m_num;
	KdTexture m_tex;

	bool m_bKey;
	bool m_bOK;

	int m_frame;

	const std::string m_file[5] = { "map/map1.csv","map/map2.csv" ,"map/map3.csv" ,"map/map4.csv" ,"map/map5.csv" };

public:

	// 初期設定
	void Init();

	// 解放
	void Release();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

	// GUI処理
	void ImGuiUpdate();

private:

	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
