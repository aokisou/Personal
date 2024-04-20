#include "GameScene.h"
#include "../../object/player/Player.h"
#include "../../object/enemy/slime/Slime.h"
#include "../../hit/Hit.h"
#include "../../map/Map.h"
#include "../../hit/MapHit.h"
#include<vector>
#include "../../utility/utility.h"

int GameScene::Update()
{
	m_player->Action();
	m_enemy->Action();

	m_hit->ArrEmyHit();	//’e‚Ì“–‚½‚è”»’è‚©‚ç‚·‚é
	m_hit->PlyEmyHit();

	m_mapHit->MapObjHit(m_map, m_player);
	m_mapHit->MapObjHit(m_map, m_enemy);
	std::vector<Arrow*>* b = m_player->GetArrow();
	if (b->size() > 0)
	{
		std::vector<Arrow*>::iterator it = b->begin();
		while (it != b->end())
		{
			m_mapHit->MapObjHit(m_map, (BaseObject*)*it);
			it++;
		}
	}

	m_player->Update(m_scrollX);
	if (!m_player->GetbAlive())
	{
		return ChangeScene::result;
	}
	m_enemy->Update(m_scrollX);
	m_map->Update(m_scrollX);

	m_scrollX = m_player->GetPos().x;

	if (m_scrollX < m_minScrollX) 
	{ 
		m_scrollX = m_minScrollX; 
		if(m_player->GetPos().x - m_player->GetHalfSize() + m_player->GetSpaceWidthImg() < m_minScrollX - SCREEN::width / Half)
		{
			m_player->MapHitX(m_minScrollX - SCREEN::width / Half + m_player->GetHalfSize() - m_player->GetSpaceWidthImg(), 0);
		}
	}
	if (m_scrollX > m_maxScrollX)
	{
		m_scrollX = m_maxScrollX;
		if (m_player->GetPos().x + m_player->GetHalfSize() - m_player->GetSpaceWidthImg() > m_maxScrollX + SCREEN::width / Half)
		{
			m_player->MapHitX(m_maxScrollX + SCREEN::width / Half - m_player->GetHalfSize() + m_player->GetSpaceWidthImg(), 0);
		}
	}

	if (m_player->GetbAlive())
	{
		return ChangeScene::no;
	}
	else
	{
		return ChangeScene::result;
	}
}

void GameScene::Draw()
{
	m_map->Draw();
	m_enemy->Draw();
	m_player->Draw();
}

float GameScene::GetHp()
{
	return m_enemy->GetHP();
}

void GameScene::Init()
{
	bool bLoad = false;

	m_player = new Player;
	m_enemy = new Slime;
	m_hit = new Hit;
	m_map = new Map;
	m_mapHit = new MapHit;

	m_hit->Init();

	m_map->SetMapData(m_mapNme[0]);
	m_minScrollX = m_map->GetPos(0, 0).x + SCREEN::width / Half;
	m_maxScrollX = m_map->GetPos(0,(m_map->GetMaxWidth() - 1)).x - SCREEN::width / Half;

	m_enemy->SetOwner(this);
	m_hit->SetOwner(this);
}

void GameScene::Release()
{
	delete m_player;
	delete m_enemy;
	delete m_hit;
	delete m_map;
}