#include "GameScene.h"
#include "../../Scene.h"
#include "../../../Object/Player/Player.h"
#include "../../../Object/arrow/Arrow.h"
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
#define GOALWIDTH 276		//ゴールの文字幅
#define GOALHEIGHT 108		//ゴールの文字幅
#define STARTALPHA 90.0f	//α値の初期値
#define CUTRANGEX 450		//ボス登場シーンの切取幅
#define CUTRANGEY 400		//ボス登場シーンの切取幅
#define CUTSCALE 3.0f		//ボス登場シーンの拡大率
#define KEYPOSX 220			//画像の真ん中
#define PLAYERCRX 40		//画面端のプレイヤーの補正
#define COLON 10			//コロンの場所
#define NUMSLIDEPOS 55.0f	//どれだけずらすか
#define STAGENAMEWIDTH 500	//画像サイズ
#define STAGENAMEHEIGHT 100	//画像サイズ

static bool m_bTutorialSkip = false;//実行1回目のみチュートリアル

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

		for (int i = 0; i < 99; i++)
		{
			std::shared_ptr<Arrow>* a = m_player->GetArrow(i);
			if ((*a)->GetAlive())
			{
				m_mapHit->MapObjHit(m_mapRangeStart, m_mapRangeEnd, m_map, *a);
			}
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
		if (m_player->GetPos().x - m_player->GetHalfSize() + m_player->GetSpaceWidthImg() < m_minScrollX - SCREEN::width / HALF + PLAYERCRX)
		{
			m_player->MapHitX(m_minScrollX - SCREEN::width / HALF + m_player->GetHalfSize() - m_player->GetSpaceWidthImg() + PLAYERCRX, 0);
		}
	}
	if (m_scrollX > m_maxScrollX)
	{
		m_scrollX = m_maxScrollX;
		int cr = 0;
		if (m_nowMap >= MAXMAP - 1 || m_bGoal) { cr = PLAYERCRX; }
		if (m_player->GetPos().x + m_player->GetHalfSize() - m_player->GetSpaceWidthImg() > m_maxScrollX + SCREEN::width / HALF - cr)
		{
			m_player->MapHitX(m_maxScrollX + SCREEN::width / HALF - m_player->GetHalfSize() + m_player->GetSpaceWidthImg() - cr, 0);
			if (m_nowMap + 1 < MAXMAP && (int)m_enemy.size() <= 0)
			{
				m_bTutorialSkip = true;
				m_pOwner->SetTrueChangeScene();
				m_nextMap = m_nowMap + 1;
				return;
			}
			if (m_bGoal)
			{
				m_pOwner->SetTrueChangeScene();
				m_pOwner->ChangeResult(CLEAR, m_minuets, m_seconds);
			}
		}
	}

	TutorialUpdate();

	float r = 0.0f;
	if (m_shake)
	{
		m_shakeCnt++;
		r = (float)(rand() % BIGSHAKEPOW - BIGSHAKEPOW / HALF);
		if (m_shakeCnt > MAXSHAKECNT) { ShakeReset(m_shake); }
	}

	m_mat = Math::Matrix::CreateScale(m_scale) *
		Math::Matrix::CreateTranslation(r + 0.0f, 0.0f, 0.0f);

	if (m_enemy.size() <= 0)
	{
		ArrowUpdate();
	}

	if (m_bGoal)
	{
		m_goalMat = Math::Matrix::CreateScale(0.8f) * 
			Math::Matrix::CreateTranslation(SCREEN::width / HALF - GOALWIDTH / HALF, GOALHEIGHT, 0.0f);
		ArrowUpdate();
	}

	if (!m_player->GetAlive())
	{
		m_pOwner->SetTrueChangeScene();
		m_pOwner->ChangeResult(!CLEAR);
		return;
	}

	if (m_bStart)
	{
		if (!m_bEntry)
		{
			if (m_nowMap + 1 == MAXMAP)
			{
				m_bStart = false;
			}
			else
			{
				m_stageNameAlpha--;
				if (m_stageNameAlpha < 0)
				{
					m_bStart = false;
				}
			}
		}
	}

	if (m_bTutorialSkip && !m_bGoal && !m_bEntry)
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
	std::vector<std::shared_ptr<BaseEnemy>>::iterator it = m_enemy.begin();
	while (it != m_enemy.end())
	{
		if (!(*it)->GetAlive())
		{
			if (typeid(**it) != typeid(Minotaur))
			{
				it = m_enemy.erase(it);
			}
			else
			{
				m_bGoal = true;
				it++;
			}
		}
		else
		{
			if ((*it)->GetEnemyState()->GetStateType() == enemyBossEntry)
			{
				m_scale = CUTSCALE;
				m_bEntry = true;
				m_startCut = { ((*it)->GetPos().x - m_scrollX) - CUTRANGEX / HALF, (*it)->GetPos().y + (*it)->GetHalfSize() + CUTRANGEY / HALF};
			}
			it++;
		} 
	}
}

void GameScene::EnemyErase()
{
	std::vector<std::shared_ptr<BaseEnemy>>::iterator it = m_enemy.begin();
	while (it != m_enemy.end())
	{
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
		m_backMat[i] = Math::Matrix::CreateScale(Back::scale) * Math::Matrix::CreateTranslation(m_backPos[i].x, m_backPos[i].y, 0.0f);
		m_2ndBackMat[i] = Math::Matrix::CreateScale(Back::scale) * Math::Matrix::CreateTranslation(m_2ndBackPos[i].x, m_2ndBackPos[i].y, 0.0f);
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
		ArrowDraw();
	}

	if (m_bGoal)
	{
		ArrowDraw();
		src = { 0,0,GOALWIDTH,GOALHEIGHT };
		SHADER.m_spriteShader.SetMatrix(m_goalMat);
		SHADER.m_spriteShader.DrawTex(&m_goalTex, 0, 0, &src);
	}

	if (m_bEntry) { src = { (int)m_startCut.x + SCREEN::width / HALF,(int)m_startCut.y,CUTRANGEX,CUTRANGEY }; }
	else { src = { 0,0, SCREEN::width, SCREEN::height }; }
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(_pTex, 0, 0, &src);

	if (m_nowMap > 0)
	{
		int m_num[5];
		int tenm = 0, onem = 0, tens = 0, ones = 0;

		m_num[0] = m_minuets / 10;
		m_num[1] = m_minuets % 10;
		m_num[2] = COLON;
		m_num[3] = m_seconds / 10;
		m_num[4] = m_seconds % 10;

		src = { 0,0,100,100 };
		for (int i = 0; i < PlayTime::ptnum; i++)
		{
			SHADER.m_spriteShader.SetMatrix(m_numMat[i]);
			SHADER.m_spriteShader.DrawTex(&m_numTex[m_num[i]], 0, 0, &src);
		}
	}

	TutorialDraw();

	m_player->DrawUI();

	if (m_bStart)
	{
		src = { 0,0,STAGENAMEWIDTH,STAGENAMEHEIGHT };
		Math::Color col = { 1,1,1,sin(DirectX::XMConvertToRadians((float)m_stageNameAlpha)) };
		SHADER.m_spriteShader.SetMatrix(m_stageMat);
		SHADER.m_spriteShader.DrawTex(&m_stageNameTex, 0, 0, &src, &col);
	}
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
		m_nextMap = 0;
		m_tutorialTex.Load("Texture/UI/tutorial.png");
		m_keyTex.Load("Texture/UI/key.png");
	}
	else { m_nextMap = 1; }

	for (int i = 0; i < Back::num; i++)
	{
		m_backPos[i] = {};
		m_2ndBackPos[i] = {};
		m_backMat[i] = Math::Matrix::Identity;
		m_2ndBackMat[i] = Math::Matrix::Identity;
		bLoad = m_backTex[i].Load(m_backName[i]);
		_ASSERT_EXPR(bLoad, "ファイル読み取りエラー");
	}

	for (int i = 0; i < 10; i++)
	{
		m_numTex[i].Load(m_numFileName[i]);
	}

	m_numTex[COLON].Load("Texture/time/minuet.png");

	m_arrowTex.Load("Texture/UI/arrow.png");

	m_goalTex.Load("Texture/UI/goal.png");

	m_player = std::make_shared<Player>();
	m_hit = new Hit;
	m_map = new Map;
	m_mapHit = new MapHit;

	m_map->SetOwner(this);

	m_map->SetOwner(this);
	m_hit->SetOwner(this);
	m_tutorialMat = Math::Matrix::CreateTranslation(SCREEN::width / HALF - TUTORIALWIDTH / HALF, SCREEN::height / HALF - TUTORIALHEIGHT, 0.0f);
	m_keyMat = Math::Matrix::CreateScale(5.0f) * 
		Math::Matrix::CreateTranslation(KEYPOSX, SCREEN::height / HALF - TUTORIALHEIGHT, 0.0f);

	for (int i = 0; i < PlayTime::ptnum; i++)
	{
		m_numMat[i] = Math::Matrix::CreateScale(0.8f) * Math::Matrix::CreateTranslation(SCREEN::width / HALF - 300.0f + NUMSLIDEPOS * i,SCREEN::height / HALF - 50.0f, 0.0f);
	}

	Reset();
}

void GameScene::Reset()
{
	m_bStart = true;
	m_stageNameAlpha = 90;
	m_stageMat = Math::Matrix::CreateTranslation(0.0f, ((m_nextMap + 1) / MAXMAP) * 300.0f, 0.0f);
	m_nowMap = m_nextMap;
	m_stageNameTex.Load(m_stageFileName[m_nowMap]);
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
	m_shake = false;

	m_map->SetMapData(m_mapName[m_nowMap]);
	m_scrollX = 0;
	m_minScrollX = m_map->GetPos(0, 0).x + SCREEN::width / HALF;
	m_maxScrollX = m_map->GetPos(0, (m_map->GetMaxWidth() - 1)).x - SCREEN::width / HALF;

	Update();
}


void GameScene::Release()
{
	delete m_hit;
	delete m_map;
	delete m_mapHit;
}

void GameScene::CreateSlime(Math::Vector2 _pos)
{
	std::shared_ptr<Slime> s = std::make_shared<Slime>(_pos);
	s->SetOwner(this);
	m_enemy.push_back(s);
}

void GameScene::CreateWolf(Math::Vector2 _pos)
{
	std::shared_ptr<Wolf> w = std::make_shared<Wolf>(_pos);
	w->SetOwner(this);
	m_enemy.push_back(w);
}

void GameScene::CreateOrc(Math::Vector2 _pos)
{
	std::shared_ptr<Orc> o = std::make_shared<Orc>(_pos);
	o->SetOwner(this);
	m_enemy.push_back(o);
}

void GameScene::CreateBee(Math::Vector2 _pos)
{

}

void GameScene::CreateMinotaur(Math::Vector2 _pos)
{
	std::shared_ptr<Minotaur> m = std::make_shared<Minotaur>(_pos);
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
				m_bAction = true;
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

void GameScene::ArrowUpdate()
{
	m_arrowSizeAng += 3.0f;
	m_arrowMat = Math::Matrix::CreateScale(1.0f + (float)sin(DirectX::XMConvertToRadians(m_arrowSizeAng)) * 0.2f, 1.0f + (float)sin(DirectX::XMConvertToRadians(m_arrowSizeAng)) * 0.2f, 1.0f) *
		Math::Matrix::CreateTranslation(SCREEN::width / HALF - ARROWWIDTH / HALF, 0.0f, 0.0f);
}

void GameScene::ArrowDraw()
{
	Math::Rectangle src = { 0,0,ARROWWIDTH,ARROWHEIGHT };
	SHADER.m_spriteShader.SetMatrix(m_arrowMat);
	SHADER.m_spriteShader.DrawTex(&m_arrowTex, 0, 0, &src);
}

void GameScene::ResetScreenScale()
{
	m_scale = SCREEN::scale;
}

void GameScene::SetMap()
{
	if (GetAsyncKeyState('1') & 0x8000)
	{
		m_nextMap = 0;
		m_bTutorialSkip = false;
		m_pOwner->SetTrueChangeScene();
	}
	if (GetAsyncKeyState('2') & 0x8000)
	{
		m_nextMap = 1;
		m_bTutorialSkip = true;
		m_pOwner->SetTrueChangeScene();
	}
	if (GetAsyncKeyState('3') & 0x8000)
	{
		m_nextMap = 2;
		m_bTutorialSkip = true;
		m_pOwner->SetTrueChangeScene();
	}
	if (GetAsyncKeyState('0') & 0x8000)
	{
		std::vector<std::shared_ptr<BaseEnemy>>::iterator it = m_enemy.begin();
		while (it != m_enemy.end())
		{
			(*it)->SetDmg(10000);
			it++;
		}
	}
}