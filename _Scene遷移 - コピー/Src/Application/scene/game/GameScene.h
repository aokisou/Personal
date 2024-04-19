#pragma once

#include "../BaseScene.h"

class Player;
class BaseEnemy;
class Hit;
class Map;
class MapHit;

class GameScene:public BaseScene
{
public:
	GameScene(int* _fps) { m_maxFps = _fps; Init(); }
	~GameScene() { Release(); }

	int Update()override;
	void Draw()override;

	//クラスアドレス
	Player* GetPlayer() { return m_player; }
	BaseEnemy* GetEnemy() { return m_enemy; }

	float GetHp()override;
private:
	void Init()override;
	void Release()override;

	float m_scrollX = 0.f;
	float m_minScrollX = 0.f;
	float m_maxScrollX = 0.f;

	std::string m_mapNme[1] = { "map/stage1.csv" };

	Player* m_player;
	BaseEnemy* m_enemy;

	Hit* m_hit;

	Map* m_map;

	MapHit* m_mapHit;

	KdTexture m_playerTex;
	KdTexture m_enemyTex;
	KdTexture m_mapTex;
};