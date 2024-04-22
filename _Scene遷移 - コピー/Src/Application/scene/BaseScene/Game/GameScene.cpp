#include "GameScene.h"
#include "../../../Object/player/Player.h"
#include "../../../Object/enemy/slime/Slime.h"
#include "../../../Hit//Object/Hit.h"
#include "../../../Map/Map.h"
#include "../../../Hit/Map/MapHit.h"
#include<vector>
#include "../../../Utility/utility.h"

#define BackSize 2.3f

int GameScene::Update()
{
	m_player->Action();

	for (auto& i : m_enemy)
	{
		i->Action();
	}

	m_hit->ArrEmyHit();	//弾の当たり判定からする
	m_hit->PlyEmyHit();

	m_mapHit->MapObjHit(m_map, m_player);
	for (auto& i : m_enemy)
	{
		m_mapHit->MapObjHit(m_map, i);
	}

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

	for (auto& i : m_enemy)
	{
		i->Update(m_scrollX);
	}
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

	UpdateBack();

	if (m_player->GetAlive())
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
	for (int i = 0; i < backNum; i++)
	{
		Math::Rectangle src = { 0,0,576,324 };
		SHADER.m_spriteShader.SetMatrix(m_backMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_backTex[i], 0, 0, &src);
		SHADER.m_spriteShader.SetMatrix(m_2ndBackMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_backTex[i], 0, 0, &src);
	}
}

void GameScene::DynamicDraw2D()
{
	m_map->Draw();
	for (auto& i : m_enemy)
	{
		i->Draw();
	}
	m_player->Draw();
}

void GameScene::UpdateBack()
{
	for (int i = 0; i < backNum; i++)
	{
		//m_backPos[i].x = -(m_scrollX * (float)i / backNum);
		//if (m_backPos[i].x - 288 * BackSize < -576 * BackSize)
		//{
		//	while (m_backPos[i].x + 288 * BackSize < SCREEN::width + 288 * BackSize)
		//	{
		//		m_backPos[i].x += 576 * BackSize;
		//	}
		//}
		//m_2ndBackPos[i].x = -(m_scrollX * (float)i / backNum) + (576 * BackSize);
		//if (m_2ndBackPos[i].x - 288 * BackSize < -576 * BackSize)
		//{
		//	while (m_2ndBackPos[i].x + 288 * BackSize < m_backPos[i].x - 288 * BackSize)
		//	{
		//		m_2ndBackPos[i].x += 576 * BackSize;
		//	}
		//}
		m_backMat[i] = Math::Matrix::CreateScale(BackSize, BackSize, 1) * Math::Matrix::CreateTranslation(m_backPos[i].x, m_backPos[i].y, 0);
		m_2ndBackMat[i] = Math::Matrix::CreateScale(BackSize, BackSize, 1) * Math::Matrix::CreateTranslation(m_2ndBackPos[i].x, m_2ndBackPos[i].y, 0);
	}
}

float GameScene::GetHp()
{
	return m_enemy[0]->GetHP();
}

void GameScene::Init()
{
	bool bLoad = false;

	m_player = new Player;
	CreateSlime();
	m_hit = new Hit;
	m_map = new Map;
	m_mapHit = new MapHit;

	m_map->SetMapData(m_mapName[0]);
	m_minScrollX = m_map->GetPos(0, 0).x + SCREEN::width / Half;
	m_maxScrollX = m_map->GetPos(0,(m_map->GetMaxWidth() - 1)).x - SCREEN::width / Half;

	for (int i = 0; i < backNum; i++)
	{
		m_backPos[i] = {};
		m_2ndBackPos[i] = {};
		m_backMat[i] = Math::Matrix::Identity;
		m_2ndBackMat[i] = Math::Matrix::Identity;
		bLoad = m_backTex[i].Load(m_backName[i]);
		_ASSERT_EXPR(bLoad, "ファイル読み取りエラー");
	}

	m_hit->SetOwner(this);
}

void GameScene::Release()
{
	delete m_player;
	std::vector<BaseEnemy*>::iterator it = m_enemy.begin();
	while (it != m_enemy.end())
	{
		delete *it;
		it = m_enemy.erase(it);
	}
	delete m_hit;
	delete m_map;
	delete m_mapHit;
}

void GameScene::CreateSlime()
{
	Slime* s = new Slime;
	s->SetOwner(this);
	m_enemy.push_back(s);
}

void GameScene::CreateWolf()
{
}

void GameScene::CreateOrc()
{
}