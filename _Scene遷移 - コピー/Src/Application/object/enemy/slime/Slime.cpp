#include "Slime.h"
#include "../../../Scene/BaseSCene/Game/GameScene.h"
#include "../../Player/Player.h"
#include "../EnemyPattern/EnemyPattern.h"
#include "../EnemyPattern/Death/EnemyDeath.h"
#include "../EnemyPattern/Run/EnemyRun.h"
#include "../EnemyPattern/Attack/EnemyAttack.h"
#include "../../../Utility/Utility.h"

#define WalkSpeed 1	//•ú˜Q‚µ‚Ä‚é‚Æ‚«
#define RunSpeed 2	//UŒ‚ó‘Ô‚ÌŽž

void Slime::Init()
{
	m_pos = { 0 };
	m_move = { 0 };
	m_mat = Math::Matrix::Identity;
	m_bAlive = true;
	m_Size = ImgSize;
	m_Scale = Scale;
	m_dir = DefaultDir;
	m_hp = 15;
	m_bDead = false;
	m_bDmg = false;
	DmgEfcCnt = 0;
	m_moveRange = 100;
	m_attackRange = m_moveRange * 2;
	m_bAttack = false;
	m_pState = new EnemyRun;
	m_pState->Init(this, m_fileName[enemyRun]);

	m_startPos = m_pos;
}

void Slime::Action()
{
	if (!m_bAlive || m_pState->GetStateType() == enemyDeath) { return; }

	m_move = { 0,m_move.y - Gravity };

	Attack();

	if (m_bAttack)return;
	m_move.x = WalkSpeed * m_dir;

	if (m_pos.x > m_startPos.x + m_moveRange && m_move.x > 0) { m_dir *= Reverse; }
	if (m_pos.x < m_startPos.x - m_moveRange && m_move.x < 0) { m_dir *= Reverse; }
}

void Slime::Update(float _scrollX)
{
	if (!m_bAlive) { return; }

	if (m_pState->GetStateType() != enemyDeath)
	{
		if (m_bDmg)
		{
			DmgEfcCnt++;
			if (DmgEfcCnt > EmyMaxDmgEfcCnt)
			{
				m_bDmg = false;
				DmgEfcCnt = 0;
				if (m_hp <= 0)
				{
					m_hp = 0.f;
					SetDeathState();
				}
			}
		}

		m_pos += m_move;
	}

	m_pState->Update();
	
	m_mat = Math::Matrix::CreateScale(m_Scale * m_dir, m_Scale, 0) * Math::Matrix::CreateTranslation(m_pos.x - _scrollX, m_pos.y, 0);
	return;
}

void Slime::Attack()
{
	Player* ply = m_pOwner->GetPlayer();

	const float plyTop		= ply->GetPos().y + ply->GetHalfSize() - ply->GetSpaceHeightImg();
	const float plyBottom	= ply->GetPos().y - ply->GetHalfSize() + ply->GetSpaceHeightImg();

	const float emyTop		= GetPos().y + GetHalfSize();
	const float emyBottom	= GetPos().y - GetHalfSize() + GetSpaceHeightImg();

	if (plyTop > emyBottom && plyTop < emyTop)
	{
		if (abs(ply->GetFuturePos().x - GetFuturePos().x) < m_attackRange)
		{
			float a = GetAngleDeg(GetPos(), ply->GetPos());
			m_move = { cos(DirectX::XMConvertToRadians(a)) * RunSpeed,sin(DirectX::XMConvertToRadians(a)) };
			if (m_move.x > 0) { m_dir = DefaultDir; }
			else { m_dir = DefaultDir * Reverse; }
			m_bAttack = true;
			return;
		}
	}
	m_bAttack = false;
	return;
}

void Slime::SetRunState()
{
	delete m_pState;
	m_pState = new EnemyRun;
	m_pState->Init(this,m_fileName[enemyRun]);
}

void Slime::SetDeathState()
{
	delete m_pState;
	m_pState = new EnemyDeath;
	m_pState->Init(this,m_fileName[enemyDeath]);
}

void Slime::Release()
{
	delete m_pState;
}