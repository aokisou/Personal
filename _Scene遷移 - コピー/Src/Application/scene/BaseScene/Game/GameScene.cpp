#include "GameScene.h"
#include "../../Scene.h"
#include "../../../Object/Player/Player.h"
#include "../../../Object/Enemy/Slime/Slime.h"
#include "../../../Object/Enemy/Wolf/Wolf.h"
#include "../../../Object/Enemy/Orc/Orc.h"
#include "../../../Object/Enemy/Minotaur/Minotaur.h"
#include "../../../Hit//Object/Hit.h"
#include "../../../Map/Map.h"
#include "../../../Hit/Map/MapHit.h"
#include "../../../Object/Enemy/EnemyPattern/Death/EnemyDeath.h"
#include "../../../Object/Enemy/EnemyPattern/Run/EnemyRun.h"
#include "../../../Object/Enemy/EnemyPattern/Attack/EnemyAttack.h"
#include<vector>
#include "../../../Utility/utility.h"

#define MaxMap 3			//最大ステージ
#define MaxShakeCnt 10		//揺れる時間
#define BigShakePow 20		//大きい揺れ
#define SmallShakePow 10	//小さい揺れ
#define OnePunch 2			//一発で倒されたら
#define ScreenRange 22		//画面に入るマップチップの範囲
#define Clear true			//クリア
#define TutorialWidth 580	//チュートリアルの文字幅
#define TutorialHeight 78	//チュートリアルの文字幅

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

	if (!m_BigShake || !m_smallShake)
	{
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
				if (m_nowMap + 1 < MaxMap)
				{
					//m_bTutorialSkip = true;
					m_pOwner->SetTrueChangeScene();
					m_nowMap++;
					return;
				}
			}
		}
	}

	TutorialUpdate();

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
		Math::Matrix::CreateTranslation(r + m_player->GetHalfSize() - m_player->GetSpaceWidthImg(), 0.0f, 0.0f);

	if (!m_player->GetAlive()) 
	{
		m_pOwner->SetTrueChangeScene();
		m_pOwner->ChangeResult(!Clear);
		return;
	}
}

void GameScene::MapRange()
{
	m_mapRangeStart = (int)(m_scrollX / (m_map->GetHalfSize() * 2));
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
	for (int i = 0; i < Back::Num; i++)
	{
		m_backPos[i].x = -(m_scrollX * m_backScrollSpeed[i]);
		if (m_backPos[i].x < -Back::Width * Back::Scale)
		{
			while (m_backPos[i].x < -Back::Width * Back::Scale)
			{
				m_backPos[i].x += Back::Width * Back::Scale;
			}
		}
		m_2ndBackPos[i].x = m_backPos[i].x + 576 * Back::Scale;
		m_backMat[i] = Math::Matrix::CreateScale(Back::Scale, Back::Scale, 1.0f) * Math::Matrix::CreateTranslation(m_backPos[i].x, m_backPos[i].y, 0.0f);
		m_2ndBackMat[i] = Math::Matrix::CreateScale(Back::Scale, Back::Scale, 1.0f) * Math::Matrix::CreateTranslation(m_2ndBackPos[i].x, m_2ndBackPos[i].y, 0.0f);
	}
}

void GameScene::Reset()
{
	m_bAction = true;
	EnemyErase();

	m_player->Reset();

	m_mapRangeStart = 0;
	m_mapRangeEnd = 0;

	m_shakeCnt = 0;
	m_BigShake = false;
	m_smallShake = false;

	m_map->SetMapData(m_mapName[m_nowMap]);
	m_scrollX = 0;
	m_minScrollX = m_map->GetPos(0, 0).x + SCREEN::width / Half;
	m_maxScrollX = m_map->GetPos(0, (m_map->GetMaxWidth() - 1)).x - SCREEN::width / Half;

	Update();
}

void GameScene::Draw(KdTexture* _pTex)
{
	Math::Rectangle src = { 0,0,Back::Width,Back::Height };
	for (int i = 0; i < Back::Num; i++)
	{
		SHADER.m_spriteShader.SetMatrix(m_backMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_backTex[i], 0, 0, &src);
		SHADER.m_spriteShader.SetMatrix(m_2ndBackMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_backTex[i], 0, 0, &src);
	}
	src = { 0,0, SCREEN::width, SCREEN::height };
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(_pTex, 0, 0, &src);

	TutorialDraw();

	m_player->DrawUI();
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
	static bool m_bTutorialSkip = false;//実行1回目のみチュートリアル
	bool bLoad = false;

	if (!m_bTutorialSkip)
	{ 
		m_nowMap = 0;
		m_tutorialTex.Load("Texture/UI/tutorial.png");
	}
	else { m_nowMap = 1; }

	m_player = new Player;
	m_hit = new Hit;
	m_map = new Map;
	m_mapHit = new MapHit;

	m_map->SetOwner(this);

	for (int i = 0; i < Back::Num; i++)
	{
		m_backPos[i] = {};
		m_2ndBackPos[i] = {};
		m_backMat[i] = Math::Matrix::Identity;
		m_2ndBackMat[i] = Math::Matrix::Identity;
		bLoad = m_backTex[i].Load(m_backName[i]);
		_ASSERT_EXPR(bLoad, "ファイル読み取りエラー");
	}

	m_map->SetOwner(this);
	m_hit->SetOwner(this);
	m_tutorialMat = Math::Matrix::CreateTranslation(SCREEN::width / Half - TutorialWidth / Half, SCREEN::height / Half - TutorialHeight, 0.0f);

	Reset();
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

void GameScene::CreateMinotaur(Math::Vector2 _pos)
{
	Minotaur* m = new Minotaur(_pos);
	m->SetOwner(this);
	m_enemy.push_back(m);
}

void GameScene::SetDrawTutorial(int _data)
{
	m_tutorialCutY = (_data - MapTile::Tutorial) * TutorialHeight;
	m_bAction = false;
	m_tutorialAlpha = 90.0f;
}

void GameScene::TutorialUpdate()
{
	if (m_nowMap != 0) { return; }
	switch (m_tutorialCutY)
	{
	case TutorialHeight * 0:
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_bAction = true;
		}
		break;
	case TutorialHeight:
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			m_bAction = true;
		}
		break;
	case TutorialHeight * 2:
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (m_player->GetArrow()->size() > 0)
			{
				m_bAction = true;
			}
		}
		break;
	}

	if (m_bAction)
	{
		m_tutorialAlpha -= 1.0f;
		if (m_tutorialAlpha < 0.0f)
		{
			m_tutorialAlpha = 0.0f;
		}
	}
}

void GameScene::TutorialDraw()
{
	if (m_nowMap != 0) { return; }
	Math::Rectangle src = { 0,m_tutorialCutY, TutorialWidth, TutorialHeight };
	Math::Color col = { 1.0f,1.0f,1.0f,sin(DirectX::XMConvertToRadians(m_tutorialAlpha)) };
	SHADER.m_spriteShader.SetMatrix(m_tutorialMat);
	SHADER.m_spriteShader.DrawTex(&m_tutorialTex, 0, 0, &src, &col);
}