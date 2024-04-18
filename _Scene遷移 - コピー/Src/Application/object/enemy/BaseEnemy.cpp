#include "BaseEnemy.h"
#include "enemypattern/EnemyPattern.h"
#include "enemypattern/EnemyDeath.h"
#include "enemypattern/EnemyRun.h"
#include "../../utility/utility.h"

#define EmyMaxDmgEfcCnt 10	//赤く光る時間
#define ImgSize 64		//キャラ画像サイズ
#define Scale 2			//キャラ拡大率

void BaseEnemy::Init()
{
	m_pos = { 0 };
	m_move = { 0,-3 };
	m_mat = Math::Matrix::Identity;
	m_bAlive = true;
	m_Size = ImgSize;
	m_Scale = Scale;
	m_hp = 5;
	m_bDead = false;
	m_ExpNum = 0;
	m_ExpCnt = 0;
	m_bDmg = false;
	DmgEfcCnt = 0;
	m_pState = new EnemyPattern;
	m_pState->Init(this);
}

void BaseEnemy::Action()
{
	if (m_bDead || !m_bAlive) { return; }
	bool bAct = false;

	if (bAct)
	{
		if (m_pState->GetStateType() != enemyStand)
		{
			SetStandState();
		}
	}
}

void BaseEnemy::Update()
{
	if (!m_bAlive) { return; }
	if (m_bDmg)
	{
		DmgEfcCnt++;
		if (DmgEfcCnt > EmyMaxDmgEfcCnt)
		{
			m_bDmg = false;
			DmgEfcCnt = 0;
			if (m_hp <= 0) 
			{
				m_bDead = true;
				SetDeathState(); 
			}
		}
	}

	m_pState->Update();

	if (m_pos.y < -SCREEN::height / Half)m_pos.y = 0;

	m_pos += m_move;
	m_mat = Math::Matrix::CreateScale(m_Scale, m_Scale, 0) * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void BaseEnemy::Draw()
{
	if (!m_bAlive) { return; }
	Math::Color col = { 1,1,1,1 };
	if (m_bDmg)col = { 1,0,0,1 };
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTex, 0, 0, &Math::Rectangle(m_pState->GetAnimeCnt() * m_Size, m_pState->GetStateType() * m_Size, m_Size, m_Size), &col);
}

void BaseEnemy::SetStandState()
{
	delete m_pState;
	m_pState = new EnemyPattern;
	m_pState->Init(this);
}

void BaseEnemy::SetRunState()
{
	delete m_pState;
	m_pState = new EnemyRun;
	m_pState->Init(this);
}

void BaseEnemy::SetDeathState()
{
	delete m_pState;
	m_pState = new EnemyDeath;
	m_pState->Init(this);
}