#include "Slime.h"
#include "../../../Scene/BaseSCene/Game/GameScene.h"
#include "../../Player/Player.h"
#include "../../Player/PlayerPattern/PlayerPattern.h"
#include "../EnemyPattern/EnemyPattern.h"
#include "../EnemyPattern/Death/EnemyDeath.h"
#include "../EnemyPattern/Run/EnemyRun.h"
#include "../EnemyPattern/Attack/EnemyAttack.h"
#include "../../../UI/HP/Enemy/EnemyHPBar.h"
#include "../../../Utility/Utility.h"

#define WalkSpeed 0.5f	//放浪してるとき
#define RunSpeed 1.5f	//攻撃状態の時
#define Dmg 1			//攻撃時のダメージ
#define MaxHP 2		//初期HP

void Slime::Init(Math::Vector2 _pos)
{
	const int ImgSize = 48;			//キャラ画像サイズ
	const float Scale = 2.0f;		//キャラ拡大率
	m_pos = { _pos };
	m_move = { 0 };
	m_mat = Math::Matrix::Identity;
	m_bAlive = true;
	m_size = ImgSize;
	m_scale = Scale;
	m_dir = DEFAULTDIR;
	m_hp = MaxHP;
	m_bDmg = false;
	DmgEfcCnt = 0;
	m_moveRange = 100;
	m_attackRange = m_moveRange * 2;
	SetRunState();
	InitUI();
	m_startPos = m_pos;
}

void Slime::Action()
{
	if (!m_bAlive || m_pState->GetStateType() == enemyDeath) { return; }

	m_move = { 0,m_move.y - GRAVITY };

	if (Attack()) { return; }

	m_move.x = WalkSpeed * m_dir;

	if (m_pos.x > m_startPos.x + m_moveRange && m_move.x > 0) { m_dir *= REVERSE; }
	if (m_pos.x < m_startPos.x - m_moveRange && m_move.x < 0) { m_dir *= REVERSE; }
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
	UpdateUI(_scrollX);
	ParticleUpdate(_scrollX);

	m_mat = Math::Matrix::CreateScale(m_scale * m_dir, m_scale, 0) * Math::Matrix::CreateTranslation(m_pos.x - _scrollX, m_pos.y, 0);
}

bool Slime::Attack()
{
	std::shared_ptr<Player> ply = m_pOwner->GetPlayer();

	if (ply->GetPlayerState()->GetStateType() == playerDeath || ply->GetPlayerState()->GetStateType() == playerGetHit) { return false; }

	const float plyTop		= ply->GetPos().y + ply->GetHalfSize() - ply->GetSpaceHeightImg();
	const float plyBottom	= ply->GetPos().y - ply->GetHalfSize() + ply->GetSpaceHeightImg();

	const float emyTop		= GetPos().y + GetHalfSize();
	const float emyBottom	= GetPos().y - GetHalfSize() + GetSpaceHeightImg();

	if (plyTop > emyBottom && plyTop < emyTop)
	{
		if (abs(ply->GetFuturePos().x - GetFuturePos().x) < m_attackRange || m_hp < MaxHP)
		{
			float a = GetAngleDeg(GetFuturePos(), ply->GetFuturePos());
			m_move.x = cos(DirectX::XMConvertToRadians(a)) * RunSpeed;
			if (m_move.x > 0) { m_dir = DEFAULTDIR * REVERSE; }
			else { m_dir = DEFAULTDIR; }
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

void Slime::UpdateUI(float _scrollX)
{
	m_pHPBar->Update(&m_hp, MaxHP, { m_pos.x - _scrollX, m_pos.y + GetHalfSize() - GetSpaceHeightImg() });
}

void Slime::DrawUI()
{
	m_pHPBar->Draw(MaxHP);
}

void Slime::SetRunState()
{
	m_pState = std::make_shared<EnemyRun>();
	m_pState->Init(this, m_fileName[enemyRun]);
}

void Slime::SetDeathState()
{
	m_pState = std::make_shared<EnemyDeath>();
	m_pState->Init(this, m_fileName[slimeDeath]);
}

void Slime::Release()
{
}