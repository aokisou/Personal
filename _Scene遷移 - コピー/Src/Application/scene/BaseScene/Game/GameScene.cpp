#include "GameScene.h"
#include "../../Scene.h"
#include "../../../Object/Player/Player.h"
#include "../../../Object/Enemy/Slime/Slime.h"
#include "../../../Object/Enemy/Wolf/Wolf.h"
#include "../../../Object/Enemy/Orc/Orc.h"
#include "../../../Hit//Object/Hit.h"
#include "../../../Map/Map.h"
#include "../../../Hit/Map/MapHit.h"
#include "../../../Object/Enemy/EnemyPattern/EnemyPattern.h"
#include "../../../Object/Enemy/EnemyPattern/Death/EnemyDeath.h"
#include "../../../Object/Enemy/EnemyPattern/Run/EnemyRun.h"
#include "../../../Object/Enemy/EnemyPattern/Attack/EnemyAttack.h"
#include<vector>
#include "../../../Utility/utility.h"

#define BackWidth 576		//”wŒi‰¡•
#define BackHeight 324		//”wŒic•
#define BackScale 2.3f		//”wŒiŠg‘å—¦
#define MaxShakeCnt 10		//—h‚ê‚éŽžŠÔ
#define BigShakePow 20		//‘å‚«‚¢—h‚ê
#define SmallShakePow 20	//¬‚³‚¢—h‚ê
#define OnePunch 2			//ˆê”­‚Å“|‚³‚ê‚½‚ç
#define ScreenRange 22		//‰æ–Ê‚É“ü‚éƒ}ƒbƒvƒ`ƒbƒv‚Ì”ÍˆÍ
#define Clear true			//ƒNƒŠƒA

void GameScene::PreUpdate()
{
	UpdateBack();
	MapRange();
	DeadEnemy();
	DeadEnemyErase();
}

void GameScene::Update()
{
	PreUpdate();

	m_player->Action();

	for (auto& i : m_enemy)
	{
		i->Action();
	}

	m_hit->ArrEmyHit();

	m_mapHit->MapObjHit(m_mapRangeStart, m_mapRangeEnd, m_map, m_player);
	for (auto& i : m_enemy)
	{
		m_mapHit->MapObjHit(0, m_map->GetMaxWidth(), m_map, i);
	}

	std::vector<Arrow*>* b = m_player->GetArrow();
	std::vector<Arrow*>::iterator it = b->begin();
	while (it != b->end())
	{
		m_mapHit->MapObjHit(m_mapRangeStart, m_mapRangeEnd, m_map, (BaseObject*)*it);
		it++;
	}

	m_player->Update(m_scrollX);

	for (auto& i : m_enemy)
	{
		i->Update(m_scrollX);
	}
	m_map->Update(m_mapRangeStart, m_mapRangeEnd, m_scrollX);

	m_scrollX = m_player->GetPos().x;

	if (m_scrollX < m_minScrollX)
	{
		m_scrollX = m_minScrollX;
		if (m_player->GetPos().x - m_player->GetHalfSize() + m_player->GetSpaceWidthImg() < m_minScrollX - SCREEN::width / Half)
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

	float r = 0.0f;
	if (m_BigShake)
	{
		m_shakeCnt++;
		r = (float)(rand() % BigShakePow - BigShakePow / Half);
		if (m_shakeCnt > MaxShakeCnt) { ShakeReset(m_BigShake); }
	}
	if (m_smallShake)
	{
		m_shakeCnt++;
		r = (float)(rand() % SmallShakePow - SmallShakePow / Half);
		if (m_shakeCnt > MaxShakeCnt) { ShakeReset(m_smallShake); }
	}
	m_mat = Math::Matrix::CreateScale(SCREEN::scale, SCREEN::scale, 1.0f) *
		Math::Matrix::CreateTranslation(r + m_player->GetHalfSize() - m_player->GetSpaceWidthImg(), 320.0f, 0.0f);

	if (!m_player->GetAlive()) 
	{
		m_pOwner->ChangeResult(!Clear);
		return;
	}
}

void GameScene::MapRange()
{
	m_mapRangeStart = (int)(m_scrollX / m_map->GetHalfSize() * 2);
	if (m_mapRangeStart < 0) { m_mapRangeStart = 0; }
	m_mapRangeEnd = m_mapRangeStart + ScreenRange;
	if (m_mapRangeEnd > m_map->GetMaxWidth())
	{
		m_mapRangeStart = m_map->GetMaxWidth() - 1 - ScreenRange;
		m_mapRangeEnd = m_map->GetMaxWidth() - 1;
	}
}

void GameScene::ShakeReset(bool& _b)
{
	_b = false;
	m_shakeCnt = 0;
}

void GameScene::DeadEnemy()
{
	std::vector<BaseEnemy*>::iterator it = m_enemy.begin();
	while (it != m_enemy.end())
	{
		if ((*it)->GetEnemyState()->GetStateType() == enemyDeath)
		{
			if ((*it)->GetAttackHitCnt() < OnePunch) { m_BigShake = true; }
			else { m_smallShake = true; }
		}
		it++;
	}
}

void GameScene::DeadEnemyErase()
{
	std::vector<BaseEnemy*>::iterator it = m_enemy.begin();
	while (it != m_enemy.end())
	{
		if (!(*it)->GetAlive())
		{
			delete* it;
			it = m_enemy.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void GameScene::EnemyErase()
{
	std::vector<BaseEnemy*>::iterator it = m_enemy.begin();
	while (it != m_enemy.end())
	{
		delete* it;
		it = m_enemy.erase(it);
	}
}

void GameScene::UpdateBack()
{
	for (int i = 0; i < BackNum; i++)
	{
		m_backPos[i].x = -(m_scrollX * m_backScrollSpeed[i]);
		if (m_backPos[i].x < -BackWidth * BackScale)
		{
			while (m_backPos[i].x < -BackWidth * BackScale)
			{
				m_backPos[i].x += BackWidth * BackScale;
			}
		}
		m_2ndBackPos[i].x = m_backPos[i].x + 576 * BackScale;
		m_backMat[i] = Math::Matrix::CreateScale(BackScale, BackScale, 1.0f) * Math::Matrix::CreateTranslation(m_backPos[i].x, m_backPos[i].y, 0.0f);
		m_2ndBackMat[i] = Math::Matrix::CreateScale(BackScale, BackScale, 1.0f) * Math::Matrix::CreateTranslation(m_2ndBackPos[i].x, m_2ndBackPos[i].y, 0.0f);
	}
}


void GameScene::Draw(KdTexture* _pTex)
{
	for (int i = 0; i < BackNum; i++)
	{
		Math::Rectangle src = { 0,0,BackWidth,BackHeight };
		SHADER.m_spriteShader.SetMatrix(m_backMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_backTex[i], 0, 0, &src);
		SHADER.m_spriteShader.SetMatrix(m_2ndBackMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_backTex[i], 0, 0, &src);
	}
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(_pTex, 0, 0, &Math::Rectangle(0, 0, SCREEN::width, SCREEN::width));
}

void GameScene::DynamicDraw2D()
{
	m_map->Draw(m_mapRangeStart,m_mapRangeEnd);
	for (auto& i : m_enemy)
	{
		i->Draw();
	}
	m_player->Draw();
}

void GameScene::Init()
{
	bool bLoad = false;

	m_mapRangeStart = 0;
	m_mapRangeEnd = 0;

	m_shakeCnt = 0;
	m_BigShake = false;
	m_smallShake = false;

	m_player = new Player;
	m_hit = new Hit;
	m_map = new Map;
	m_mapHit = new MapHit;

	m_map->SetOwner(this);

	m_map->SetMapData(m_mapName[0]);
	m_minScrollX = m_map->GetPos(0, 0).x + SCREEN::width / Half;
	m_maxScrollX = m_map->GetPos(0,(m_map->GetMaxWidth() - 1)).x - SCREEN::width / Half;

	for (int i = 0; i < BackNum; i++)
	{
		m_backPos[i] = {};
		m_2ndBackPos[i] = {};
		m_backMat[i] = Math::Matrix::Identity;
		m_2ndBackMat[i] = Math::Matrix::Identity;
		bLoad = m_backTex[i].Load(m_backName[i]);
		_ASSERT_EXPR(bLoad, "ƒtƒ@ƒCƒ‹“Ç‚ÝŽæ‚èƒGƒ‰[");
	}

	m_hit->SetOwner(this);
}

void GameScene::Release()
{
	delete m_player;
	EnemyErase();
	delete m_hit;
	delete m_map;
	delete m_mapHit;
}

void GameScene::CreateSlime(Math::Vector2 _pos)
{
	Slime* s = new Slime(_pos);
	s->SetOwner(this);
	m_enemy.push_back(s);
}

void GameScene::CreateWolf(Math::Vector2 _pos)
{
	Wolf* w = new Wolf(_pos);
	w->SetOwner(this);
	m_enemy.push_back(w);
}

void GameScene::CreateOrc(Math::Vector2 _pos)
{
	Orc* o = new Orc(_pos);
	o->SetOwner(this);
	m_enemy.push_back(o);
}

void GameScene::CreateBee(Math::Vector2 _pos)
{

}