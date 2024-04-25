#include "Wolf.h"
#include "../../../Scene/BaseSCene/Game/GameScene.h"
#include "../../Player/Player.h"
#include "../EnemyPattern/EnemyPattern.h"
#include "../EnemyPattern/Death/EnemyDeath.h"
#include "../EnemyPattern/Run/EnemyRun.h"
#include "../EnemyPattern/Attack/EnemyAttack.h"
#include "../../../Utility/Utility.h"

#define WalkSpeed 1.5f	//•ú˜Q‚µ‚Ä‚é‚Æ‚«
#define RunSpeed 3.f	//UŒ‚ó‘Ô‚ÌŽž

void Wolf::Init()
{
	const int ImgSize = 48;		//ƒLƒƒƒ‰‰æ‘œƒTƒCƒY
	const float Scale = 2.0f;		//ƒLƒƒƒ‰Šg‘å—¦

	m_pos = { 0 };
	m_move = { 0 };
	m_mat = Math::Matrix::Identity;
	m_bAlive = true;
	m_size = ImgSize;
	m_scale = Scale;
	m_dir = DefaultDir;
	m_hp = 15;
	m_bDmg = false;
	DmgEfcCnt = 0;
	m_moveRange = 100;
	m_lookRange = m_moveRange * 2;
	m_attackRange = 30;
	m_attackCoolTime = 0;

	SetRunState();

	m_startPos = m_pos;
}

void Wolf::Action()
{
	if (!m_bAlive || m_pState->GetStateType() == enemyDeath) { return; }

	m_move = { 0,m_move.y - Gravity };

	if (Attack())
	{
		return;
	}

	m_move.x = WalkSpeed * -m_dir;

	if (m_pos.x > m_startPos.x + m_moveRange && m_move.x > 0) { m_dir *= Reverse; }
	if (m_pos.x < m_startPos.x - m_moveRange && m_move.x < 0) { m_dir *= Reverse; }
}

void Wolf::Update(float _scrollX)
{
	if (!m_bAlive) { return; }

	if (m_pState->GetStateType() != enemyDeath)
	{
		if (m_bDmg)
		{
			const float EmyMaxDmgEfcCnt = 10.0f;	//Ô‚­Œõ‚éŽžŠÔ

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

	m_mat = Math::Matrix::CreateScale(m_scale * m_dir, m_scale, 0.0f) * Math::Matrix::CreateTranslation(m_pos.x - _scrollX, m_pos.y, 0);
}

bool Wolf::Attack()
{
	m_attackCoolTime++;
	Player* ply = m_pOwner->GetPlayer();

	const float plyTop = ply->GetPos().y + ply->GetHalfSize() - ply->GetSpaceHeightImg();
	const float plyBottom = ply->GetPos().y - ply->GetHalfSize() + ply->GetSpaceHeightImg();

	const float emyTop = GetPos().y + GetHalfSize();
	const float emyBottom = GetPos().y - GetHalfSize() + GetSpaceHeightImg();

	if (plyTop > emyBottom && plyTop < emyTop)
	{
		if (abs(ply->GetFuturePos().x - GetFuturePos().x) < m_attackRange)
		{
			if (m_attackCoolTime < *m_pOwner->GetMAXfps() * 3)
			{
				SetRunState();
				return true;
			}
			if (ply->GetFuturePos().x - GetFuturePos().x < 0) { m_dir = DefaultDir; }
			else { m_dir = DefaultDir * Reverse; }
			if (m_pState->GetStateType() != enemyAttack)
			{
				SetAttackState();
			}
			return true;
		}
		if (abs(ply->GetFuturePos().x - GetFuturePos().x) < m_lookRange)
		{
			float a = GetAngleDeg(GetFuturePos(), ply->GetFuturePos());
			if (cos(DirectX::XMConvertToRadians(a)) < 0) { m_dir = DefaultDir; }
			else { m_dir = DefaultDir * Reverse; }
			m_move.x = RunSpeed * -m_dir;
			return true;
		}
	}
	return false;
}

void Wolf::SetRunState()
{
	m_pState = std::make_shared<EnemyRun>();
	m_pState->Init(this, m_fileName[enemyRun]);
}

void Wolf::SetDeathState()
{
	m_pState = std::make_shared<EnemyDeath>();
	m_pState->Init(this, m_fileName[enemyDeath]);
}

void Wolf::SetAttackState()
{
	m_pState = std::make_shared<EnemyAttack>();
	m_pState->Init(this, m_fileName[enemyAttack]);
}

void Wolf::Release()
{
}
