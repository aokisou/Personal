#pragma once

#include "../BaseScene.h"

class Player;
class BaseEnemy;
class Hit;
class Map;
class MapHit;

#define BackNum 5

class GameScene:public BaseScene
{
public:
	GameScene(int* _fps) { m_maxFps = _fps; Init(); }
	~GameScene() { Release(); }

	int Update()override;
	void Draw(KdTexture* _pTex)override;
	void DynamicDraw2D()override;
	void UpdateBack();

	//クラスアドレス
	Player* GetPlayer() { return m_player; }
	std::vector<BaseEnemy*> GetEnemy() { return m_enemy; }

private:
	void Init()override;
	void Release()override;

	void MapRange();

	void ShakeReset(bool& _b);

	void DeadEnemy();
	void DeadEnemyErase();
	void EnemyErase();

	void CreateSlime();
	void CreateWolf();
	void CreateOrc();
	void CreateBee();

	float m_scrollX = 0.f;
	float m_minScrollX = 0.f;
	float m_maxScrollX = 0.f;

	std::string m_mapName[1] = { "map/stage1.csv" };

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

	const float m_backScrollSpeed[BackNum] = { 0.0f, 0.1f, 0.2f, 0.3f, 0.4f };
	Math::Vector2 m_backPos[BackNum];
	Math::Vector2 m_2ndBackPos[BackNum];
	Math::Matrix m_backMat[BackNum];
	Math::Matrix m_2ndBackMat[BackNum];
	KdTexture m_backTex[BackNum];
	std::string m_backName[BackNum] = { "Texture/background/1.png","Texture/background/2.png","Texture/background/3.png","Texture/background/4.png",
										"Texture/background/5.png" };
};