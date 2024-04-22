#pragma once

#include "../BaseScene.h"

class Player;
class BaseEnemy;
class Hit;
class Map;
class MapHit;

#define backNum 5

class GameScene:public BaseScene
{
public:
	GameScene(int* _fps) { m_maxFps = _fps; Init(); }
	~GameScene() { Release(); }

	int Update()override;
	void Draw()override;
	void DynamicDraw2D()override;
	void UpdateBack();

	//クラスアドレス
	Player* GetPlayer() { return m_player; }
	std::vector<BaseEnemy*> GetEnemy() { return m_enemy; }

	float GetHp()override;

	void CreateSlime();
	void CreateWolf();
	void CreateOrc();
	//void Create();

private:
	void Init()override;
	void Release()override;

	float m_scrollX = 0.f;
	float m_minScrollX = 0.f;
	float m_maxScrollX = 0.f;

	std::string m_mapName[1] = { "map/stage1.csv" };

	Player* m_player = nullptr;
	std::vector<BaseEnemy*> m_enemy;

	Hit* m_hit = nullptr;

	Map* m_map = nullptr;

	MapHit* m_mapHit = nullptr;

	Math::Vector2 m_backPos[backNum];
	Math::Vector2 m_2ndBackPos[backNum];
	Math::Matrix m_backMat[backNum];
	Math::Matrix m_2ndBackMat[backNum];
	KdTexture m_backTex[backNum];
	std::string m_backName[backNum] = { "Texture/background/1.png","Texture/background/2.png","Texture/background/3.png","Texture/background/4.png",
										"Texture/background/5.png" };
};