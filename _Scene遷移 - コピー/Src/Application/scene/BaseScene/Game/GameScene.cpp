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
#include "../../../Utility/utility.h"
#include<vector>

#define MAXMAP 3			//最大ステージ
#define MAXSHAKECNT 10		//揺れる時間
#define BIGSHAKEPOW 20		//大きい揺れ
#define SMALLSHAKEPOW 10	//小さい揺れ
#define SCREENRANGE 22		//画面に入るマップチップの範囲
#define CLEAR true			//クリア
#define TUTORIALWIDTH 580	//チュートリアルの文字幅
#define TUTORIALHEIGHT 78	//チュートリアルの文字幅
#define ARROWWIDTH 256		//矢印の文字幅
#define ARROWHEIGHT 128		//矢印の文字幅
#define ENTERSCALE 2.3f		//エンターキーの拡大率
#define ENTERWIDTH 30		//エンターキーの文字幅
#define ENTERHEIGHT 14		//エンターキーの文字幅
#define STARTALPHA 90.0f	//α値の初期値
#define CUTRANGEX 450		//ボス登場シーンの切取幅
#define CUTRANGEY 400		//ボス登場シーンの切取幅
#define CUTSCALE 3.0f		//ボス登場シーンの拡大率
#define KEYPOSX 220			//画像の真ん中
#define PLAYERCRX 40		//画面端のプレイヤーの補正

static bool m_bTutorialSkip = false;//実行1回目のみチュートリアル
static int m_nowMap = 0;

void GameScene::PreUpdate()
{
	UpdateBack();
	MapRange();
	Enemy();
	SetMap();
}

void GameScene::Update()
{
	PreUpdate();

	if (m_shakeCnt < 1)
	{
		if (!m_bEntry)
		{
			m_player->Action();

			for (auto& i : m_enemy)
			{
				i->Action();
			}
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
	}

	m_scrollX = m_player->GetPos().x;

	if (m_scrollX < m_minScrollX)
	{
		m_scrollX = m_minScrollX;
		if (m_player->GetPos().x - m_player->GetHalfSize() + m_player->GetSpaceWidthImg() < m_minScrollX - SCREEN::width / Half + PLAYERCRX)
		{
			m_player->MapHitX(m_minScrollX - SCREEN::width / Half + m_player->GetHalfSize() - m_player->GetSpaceWidthImg() + PLAYERCRX, 0);
		}
	}
	if (m_scrollX > m_maxScrollX)
	{
		m_scrollX = m_maxScrollX;
		int cr = 0;
		if (m_nowMap >= MAXMAP - 1) { cr = PLAYERCRX; }
		if (m_player->GetPos().x + m_player->GetHalfSize() - m_player->GetSpaceWidthImg() > m_maxScrollX + SCREEN::width / Half - cr)
		{
			m_player->MapHitX(m_maxScrollX + SCREEN::width / Half - m_player->GetHalfSize() + m_player->GetSpaceWidthImg() - cr, 0);
			if (m_nowMap + 1 < MAXMAP && (int)m_enemy.size() <= 0)
			{
				m_bTutorialSkip = true;
				m_pOwner->SetTrueChangeScene();
				m_nowMap++;
				return;
			}
		}
	}

	TutorialUpdate();

	float r = 0.0f;
	if (m_bigShake)
	{
		m_shakeCnt++;
		r = (float)(rand() % BIGSHAKEPOW - BIGSHAKEPOW / Half);
		if (m_shakeCnt > MAXSHAKECNT) { ShakeReset(m_bigShake); }
	}
	if (m_smallShake)
	{
		m_shakeCnt++;
		r = (float)(rand() % SMALLSHAKEPOW - SMALLSHAKEPOW / Half);
		if (m_shakeCnt > MAXSHAKECNT) { ShakeReset(m_smallShake); }
	}

	m_mat = Math::Matrix::CreateScale(m_scale, m_scale, 1.0f) *
		Math::Matrix::CreateTranslation(r + 0.0f, 0.0f, 0.0f);

	if (m_enemy.size() <= 0)
	{
		m_arrowSizeAng += 3.0f;
		m_arrowMat = Math::Matrix::CreateScale(1.0f + (float)sin(DirectX::XMConvertToRadians(m_arrowSizeAng)) * 0.2f, 1.0f + (float)sin(DirectX::XMConvertToRadians(m_arrowSizeAng)) * 0.2f, 1.0f) *
			Math::Matrix::CreateTranslation(SCREEN::width / Half - ARROWWIDTH / Half, 0.0f, 0.0f);
	}

	if (m_bEnter)
	{
		m_enterMat = Math::Matrix::CreateScale(ENTERSCALE, ENTERSCALE, 1.0f) *
			Math::Matrix::CreateTranslation(SCREEN::width / Half - ENTERWIDTH * ENTERSCALE, -SCREEN::height / Half + ENTERHEIGHT * ENTERSCALE, 0.0f);
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		std::vector<BaseEnemy*>::iterator it = m_enemy.begin();
		while (it != m_enemy.end())
		{
			if (typeid(**it) == typeid(Minotaur))
			{
				if (!(*it)->GetAlive())
				{
					m_pOwner->SetTrueChangeScene();
					m_pOwner->ChangeResult(CLEAR,m_minuets,m_seconds);
					break;
				}
				else
				{
					it++;
				}
			}
			else
			{
				it++;
			}
		}
	}
	if (!m_player->GetAlive())
	{
		m_pOwner->SetTrueChangeScene();
		m_pOwner->ChangeResult(!CLEAR, m_minuets, m_seconds);
		return;
	}

	if (m_bTutorialSkip && !m_bEnter)
	{
		m_frame++;
		if (m_frame / *m_maxFps == 1)
		{
			m_frame -= *m_maxFps;
			m_seconds++;
			if (m_seconds / 60 == 1)
			{
				m_seconds -= 60;
				m_minuets++;
			}
		}
	}
}

void GameScene::MapRange()
{
	m_mapRangeStart = (int)(m_scrollX / (m_map->GetHalfSize() * 2));
	if (m_mapRangeStart < 0) { m_mapRangeStart = 0; }
	m_mapRangeEnd = m_mapRangeStart + SCREENRANGE;
	if (m_mapRangeEnd > m_map->GetMaxWidth())
	{
		m_mapRangeStart = m_map->GetMaxWidth() - 1 - SCREENRANGE;
		if (m_mapRangeStart < 0) { m_mapRangeStart = 0; }
		m_mapRangeEnd = m_map->GetMaxWidth();
	}
}

void GameScene::ShakeReset(bool& _b)
{
	_b = false;
	m_shakeCnt = 0;
}

void GameScene::Enemy()
{
	std::vector<BaseEnemy*>::iterator it = m_enemy.begin();
	while (it != m_enemy.end())
	{
		if (!(*it)->GetAlive())
		{
			if (typeid(**it) != typeid(Minotaur))
			{
				delete* it;
				it = m_enemy.erase(it);
			}
			else
			{
				m_bEnter = true;
				it++;
			}
		}
		else
		{
			if ((*it)->GetEnemyState()->GetStateType() == enemyBossEntry)
			{
				m_scale = CUTSCALE;
				m_bEntry = true;
				m_startCut = { ((*it)->GetPos().x - m_scrollX) - CUTRANGEX / Half, (*it)->GetPos().y + (*it)->GetHalfSize() + CUTRANGEY / Half};
			}
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
	for (int i = 0; i < Back::num; i++)
	{
		m_backPos[i].x = -(m_scrollX * m_backScrollSpeed[i]);
		if (m_backPos[i].x < -Back::width * Back::scale)
		{
			while (m_backPos[i].x < -Back::width * Back::scale)
			{
				m_backPos[i].x += Back::width * Back::scale;
			}
		}
		m_2ndBackPos[i].x = m_backPos[i].x + Back::width * Back::scale;
		m_backMat[i] = Math::Matrix::CreateScale(Back::scale, Back::scale, 1.0f) * Math::Matrix::CreateTranslation(m_backPos[i].x, m_backPos[i].y, 0.0f);
		m_2ndBackMat[i] = Math::Matrix::CreateScale(Back::scale, Back::scale, 1.0f) * Math::Matrix::CreateTranslation(m_2ndBackPos[i].x, m_2ndBackPos[i].y, 0.0f);
	}
}

void GameScene::Draw(KdTexture* _pTex)
{
	Math::Rectangle src = { 0,0,Back::width,Back::height };
	for (int i = 0; i < Back::num; i++)
	{
		SHADER.m_spriteShader.SetMatrix(m_backMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_backTex[i], 0, 0, &src);
		SHADER.m_spriteShader.SetMatrix(m_2ndBackMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_backTex[i], 0, 0, &src);
	}

	if (m_enemy.size() <= 0)
	{
		src = { 0,0,ARROWWIDTH,ARROWHEIGHT };
		SHADER.m_spriteShader.SetMatrix(m_arrowMat);
		SHADER.m_spriteShader.DrawTex(&m_arrowTex, 0, 0, &src);
	}

	if (m_bEntry) { src = { (int)m_startCut.x + SCREEN::width / Half,(int)m_startCut.y,CUTRANGEX,CUTRANGEY }; }
	else { src = { 0,0, SCREEN::width, SCREEN::height }; }
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(_pTex, 0, 0, &src);

	TutorialDraw();

	if (m_bEnter)
	{
		src = { 0,0,ENTERWIDTH,ENTERHEIGHT };
		SHADER.m_spriteShader.SetMatrix(m_enterMat);
		SHADER.m_spriteShader.DrawTex(&m_enterTex, 0, 0, &src);
	}

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
	bool bLoad = false;

	if (!m_bTutorialSkip)
	{ 
		m_nowMap = 0;
		m_tutorialTex.Load("Texture/UI/tutorial.png");
		m_keyTex.Load("Texture/UI/key.png");
	}
	else { m_nowMap = 1; }

	for (int i = 0; i < Back::num; i++)
	{
		m_backPos[i] = {};
		m_2ndBackPos[i] = {};
		m_backMat[i] = Math::Matrix::Identity;
		m_2ndBackMat[i] = Math::Matrix::Identity;
		bLoad = m_backTex[i].Load(m_backName[i]);
		_ASSERT_EXPR(bLoad, "ファイル読み取りエラー");
	}

	m_arrowTex.Load("Texture/UI/arrow.png");

	m_enterTex.Load("Texture/UI/enter.png");

	m_player = new Player;
	m_hit = new Hit;
	m_map = new Map;
	m_mapHit = new MapHit;

	m_map->SetOwner(this);

	m_map->SetOwner(this);
	m_hit->SetOwner(this);
	m_tutorialMat = Math::Matrix::CreateTranslation(SCREEN::width / Half - TUTORIALWIDTH / Half, SCREEN::height / Half - TUTORIALHEIGHT, 0.0f);
	m_keyMat = Math::Matrix::CreateScale(5.0f,5.0f,1.0f) * 
		Math::Matrix::CreateTranslation(KEYPOSX, SCREEN::height / Half - TUTORIALHEIGHT, 0.0f);

	Reset();
}

void GameScene::Reset()
{
	m_scale = SCREEN::scale;
	m_bEntry = false;
	m_startCut = {};
	m_bAction = true;
	EnemyErase();

	m_arrowSizeAng = 0;

	m_player->Reset();

	m_mapRangeStart = 0;
	m_mapRangeEnd = 0;

	m_shakeCnt = 0;
	m_bigShake = false;
	m_smallShake = false;

	m_map->SetMapData(m_mapName[m_nowMap]);
	m_scrollX = 0;
	m_minScrollX = m_map->GetPos(0, 0).x + SCREEN::width / Half;
	m_maxScrollX = m_map->GetPos(0, (m_map->GetMaxWidth() - 1)).x - SCREEN::width / Half;

	Update();
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
	m_tutorialCutY = (_data - MapTile::Tutorial) * TUTORIALHEIGHT;
	m_bAction = false;
	m_tutorialAlpha = STARTALPHA;
}

void GameScene::TutorialUpdate()
{
	if (m_nowMap != 0) { return; }
	switch (m_tutorialCutY)
	{
	case TUTORIALHEIGHT * 0://1つ目
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_bAction = true;
		}
		break;
	case TUTORIALHEIGHT://2つ目
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			m_bAction = true;
		}
		break;
	case TUTORIALHEIGHT * 2://3つ目
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
	Math::Rectangle src = { 0,m_tutorialCutY, TUTORIALWIDTH, TUTORIALHEIGHT };
	Math::Color col = { 1.0f,1.0f,1.0f,sin(DirectX::XMConvertToRadians(m_tutorialAlpha)) };
	SHADER.m_spriteShader.SetMatrix(m_tutorialMat);
	SHADER.m_spriteShader.DrawTex(&m_tutorialTex, 0, 0, &src, &col);
	src = { 0,m_tutorialCutY / TUTORIALHEIGHT * 16,48,16 };
	SHADER.m_spriteShader.SetMatrix(m_keyMat);
	SHADER.m_spriteShader.DrawTex(&m_keyTex, 0, 0, &src, &col);
}

void GameScene::ResetScreenScale()
{
	m_scale = SCREEN::scale;
}

void GameScene::SetMap()
{
	if (GetAsyncKeyState('1') & 0x8000)
	{
		m_nowMap = 0;
		m_bTutorialSkip = false;
		m_pOwner->SetTrueChangeScene();
	}
	if (GetAsyncKeyState('2') & 0x8000)
	{
		m_nowMap = 1;
		m_bTutorialSkip = true;
		m_pOwner->SetTrueChangeScene();
	}
	if (GetAsyncKeyState('3') & 0x8000)
	{
		m_nowMap = 2;
		m_bTutorialSkip = true;
		m_pOwner->SetTrueChangeScene();
	}
}