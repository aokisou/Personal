#include "Slime.h"
#include "../../../Scene/BaseSCene/Game/GameScene.h"
#include "../../Player/Player.h"
#include "../EnemyPattern/EnemyPattern.h"
#include "../EnemyPattern/Death/EnemyDeath.h"
#include "../EnemyPattern/Run/EnemyRun.h"
#include "../EnemyPattern/Attack/EnemyAttack.h"
#include "../../../Utility/Utility.h"

#define WalkSpeed 0.5f	//放浪してるとき
#define RunSpeed 1.5f	//攻撃状態の時
#define Dmg 1 //攻撃時のダメージ

void Slime::Init(Math::Vector2 _pos)
{
	const int ImgSize = 48;			//キャラ画像サイズ
	const float Scale = 2.0f;				//キャラ拡大率
	m_pos = { _pos };
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
	m_attackRange = m_moveRange * 2;
	
	SetRunState();

	m_startPos = m_pos;
}

void Slime::Action()
{
	if (!m_bAlive || m_pState->GetStateType() == enemyDeath) { return; }

	m_move = { 0,m_move.y - Gravity };

	if (Attack()) { return; }

	m_move.x = WalkSpeed * -m_dir;

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
			const float EmyMaxDmgEfcCnt = 10.0f;	//赤く光る時間

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
	
	m_mat = Math::Matrix::CreateScale(m_scale * m_dir, m_scale, 0) * Math::Matrix::CreateTranslation(m_pos.x - _scrollX, m_pos.y, 0);
}

bool Slime::Attack()
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
			float a = GetAngleDeg(GetFuturePos(), ply->GetFuturePos());
			m_move.x = cos(DirectX::XMConvertToRadians(a)) * RunSpeed;
			if (m_move.x > 0) { m_dir = DefaultDir; }
			else { m_dir = DefaultDir * Reverse; }
			Math::Vector2 v = ply->GetFuturePos() - GetFuturePos();
			if (v.Length() < ply->GetHalfSize() - ply->GetSpaceWidthImg() + GetHalfSize() - GetSpaceWidthImg())
			{
				ply->SetDmg(Dmg, m_move.x * 2);
			}
			return true;
		}
	}
	return false;
}

void Slime::SetRunState()
{
	m_pState = std::make_shared<EnemyRun>();
	m_pState->Init(this, m_fileName[enemyRun]);
}

void Slime::SetDeathState()
{
	m_pState = std::make_shared<EnemyDeath>();
	m_pState->Init(this, m_fileName[enemyDeath]);
}

void Slime::Release()
{
}