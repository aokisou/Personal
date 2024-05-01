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

	void CreateSlime(Math::Vector2 _pos);
	void CreateWolf(Math::Vector2 _pos);
	void CreateOrc(Math::Vector2 _pos);
	void CreateBee(Math::Vector2 _pos);
	void CreateMinotaur(Math::Vector2 _pos);

	void SetDrawTutorial(int _data);

	void TutorialUpdate();
	void TutorialDraw();

	void SetFalseEntry() { m_bEntry = false; }

	//クラスアドレス
	Player* GetPlayer() { return m_player; }
	std::vector<BaseEnemy*> GetEnemy() { return m_enemy; }

private:
	void Init()override;
	void Release()override;
	void Reset();
	void SetMap();//デバグ用マップを変える

	void MapRange();

	void ShakeReset(bool& _b);

	void Enemy();
	void EnemyErase();

	bool m_bEntry = false;

	float m_scrollX = 0.0f;
	float m_minScrollX = 0.0f;
	float m_maxScrollX = 0.0f;

	int m_nowMap = 0;
	std::string m_mapName[3] = { "map/tutorial.csv","map/stage1.csv","map/boss.csv" };

	Player* m_player = nullptr;
	std::vector<BaseEnemy*> m_enemy;

	Hit* m_hit = nullptr;

	Map* m_map = nullptr;

	MapHit* m_mapHit = nullptr;

	int m_mapRangeStart = 0;
	int m_mapRangeEnd = 0;

	int m_shakeCnt = 0;
	bool m_BigShake = false;
	bool m_smallShake = false;

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
	KdTexture m_tutorialTex;

	float m_arrowSizeAng = 0;
	Math::Matrix m_arrowMat = Math::Matrix::Identity;
	KdTexture m_arrowTex;//これは行先を示す画像

	bool m_bEnter = false;
	Math::Vector2 startCut = {};
	Math::Matrix m_enterMat = Math::Matrix::Identity;
	KdTexture m_enterTex;
};