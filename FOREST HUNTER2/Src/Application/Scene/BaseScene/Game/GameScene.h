#pragma once

#include "../BaseScene.h"

class Player;
class BaseEnemy;
class Hit;
class Map;
class MapHit;
class HPBar;

class GameScene :public BaseScene
{
public:
	GameScene(int* _fps) { m_maxFps = _fps; Init(); }
	~GameScene() { Release(); }

	void PreUpdate();
	void Update()override;
	void Draw(KdTexture* _pTex)override;
	void DynamicDraw2D()override;
	void UpdateBack();

	void SetTrueShake() { m_shake = true; }

	void CreateSlime(Math::Vector2 _pos);
	void CreateWolf(Math::Vector2 _pos);
	void CreateOrc(Math::Vector2 _pos);
	void CreateBee(Math::Vector2 _pos);
	void CreateMinotaur(Math::Vector2 _pos);

	void SetDrawTutorial(int _data);

	void SetFalseEntry() { m_bEntry = false; }
	void ResetScreenScale();

	//クラスアドレス
	std::shared_ptr<Player> GetPlayer() { return m_player; }
	std::vector < std::shared_ptr<BaseEnemy>> GetEnemy() { return m_enemy; }

private:
	void Init()override;
	void Release()override;
	void Reset();
	void MapRange();
	void TutorialUpdate();
	void TutorialDraw();

	void ArrowUpdate();
	void ArrowDraw();

	void ShakeReset(bool& _b);

	void Enemy();
	void EnemyErase();

	//デバグ用
	void SetMap();

	int m_nowMap = 0;
	int m_nextMap = 0;

	bool m_bEntry = false;

	float m_scrollX = 0.0f;
	float m_minScrollX = 0.0f;
	float m_maxScrollX = 0.0f;

	std::string m_mapName[3] = { "map/tutorial.csv","map/stage1.csv","map/boss.csv" };

	std::shared_ptr<Player> m_player = nullptr;
	std::vector<std::shared_ptr<BaseEnemy>> m_enemy;

	Hit* m_hit = nullptr;

	Map* m_map = nullptr;

	MapHit* m_mapHit = nullptr;

	int m_mapRangeStart = 0;
	int m_mapRangeEnd = 0;

	int m_shakeCnt = 0;
	bool m_shake = false;

	const float m_backScrollSpeed[5] = { 0.0f, 0.1f, 0.2f, 0.3f, 0.4f };
	Math::Vector2 m_backPos[5];
	Math::Vector2 m_2ndBackPos[5];
	Math::Matrix m_backMat[5];
	Math::Matrix m_2ndBackMat[5];
	KdTexture m_backTex[5];
	std::string m_backName[5] = { "Texture/BackGround/1.png","Texture/BackGround/2.png","Texture/BackGround/3.png","Texture/BackGround/4.png",
								  "Texture/BackGround/5.png" };

	bool m_bAction = true;
	float m_tutorialAlpha = 0.0f;
	int m_tutorialCutY = 0;
	Math::Matrix m_tutorialMat = Math::Matrix::Identity;
	Math::Matrix m_keyMat = Math::Matrix::Identity;
	KdTexture m_tutorialTex;
	KdTexture m_keyTex;

	float m_arrowSizeAng = 0;
	Math::Matrix m_arrowMat = Math::Matrix::Identity;
	KdTexture m_arrowTex;//これは行先を示す画像

	bool m_bGoal = false;
	Math::Vector2 m_startCut = {};
	Math::Matrix m_goalMat = Math::Matrix::Identity;
	KdTexture m_goalTex;

	float m_scale = 0.0f;

	int m_minuets = 0;
	int m_seconds = 0;
	int m_frame = 0;

	Math::Matrix m_numMat[5];
	KdTexture m_numTex[11];

	bool m_bStart = false;
	int m_stageNameAlpha = 0;
	Math::Matrix m_stageMat;
	KdTexture m_stageNameTex;

	const std::string m_stageFileName[3] = { "Texture/text/tutorial.png","Texture/text/stage1.png", "Texture/text/boss.png" };
};