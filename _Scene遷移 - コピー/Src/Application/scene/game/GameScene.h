#pragma once

#include "../BaseScene.h"

class Player;
class BaseEnemy;
class Hit;
class Map;
class MapHit;

class Game:public BaseScene
{
public:
	Game(int _fps) { m_maxFps = _fps; }
	~Game() { Release(); }

	int Update()override;
	void Draw()override;
	void Init()override;

	//クラスアドレス
	Player* GetPlayer() { return m_player; }
	BaseEnemy* GetEnemy() { return m_enemy; }
private:
	void Release()override;

	std::string m_mapNme[1] = { "map/map.csv" };

	Player* m_player;
	BaseEnemy* m_enemy;

	Hit* m_hit;

	Map* m_map;

	MapHit* m_mapHit;

	KdTexture m_playerTex;
	KdTexture m_enemyTex;
	KdTexture m_mapTex;
};