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
	Game(int _fps) { m_maxFps = _fps; m_pTex = nullptr;}
	~Game() { Release(); }

	int Update();
	void Draw();
	void Init();

	//クラスアドレス
	Player* GetPlayer() { return m_player; }
	BaseEnemy* GetEnemy() { return m_enemy; }
private:
	void Release();

	std::string m_mapNme[1] = { "map/map.csv" };

	Player* m_player;
	BaseEnemy* m_enemy;

	Hit* m_hit;

	Map* m_map;

	MapHit* m_mapHit;
};