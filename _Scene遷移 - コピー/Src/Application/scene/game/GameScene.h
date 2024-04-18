#pragma once

#include "../BaseScene.h"

class BaseObject;
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
	BaseObject* GetPlayer() { return m_player; }
	BaseObject* GetEnemy() { return m_enemy; }
private:
	void Init()override;
	void Release()override;

	std::string m_mapNme[1] = { "map/map.csv" };

	BaseObject* m_player;
	BaseObject* m_enemy;

	Hit* m_hit;

	Map* m_map;

	MapHit* m_mapHit;

	KdTexture m_playerTex;
	KdTexture m_enemyTex;
	KdTexture m_mapTex;
};