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

#define WalkSpeed 0.5f	//•ú˜Q‚µ‚Ä‚é‚Æ‚«
#define RunSpeed 1.5f	//UŒ‚ó‘Ô‚ÌŽž
#define Dmg 1			//UŒ‚Žž‚Ìƒ_ƒ[ƒW
#define MaxHP 15		//‰ŠúHP

void Slime::Init(Math::Vector2 _pos)
{
	const int ImgSize = 48;			//ƒLƒƒƒ‰‰æ‘œƒTƒCƒY
	const float Scale = 2.0f;		//ƒLƒƒƒ‰Šg‘å—¦
	m_pos = { _pos };
	m_move = { 0 };
	m_mat = Math::Matrix::Identity;
	m_bAlive = true;
	m_size = ImgSize;
	m_scale = Scale;
	m_dir = DefaultDir;
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

	m_move = { 0,m_move.y - Gravity };

	if (Attack()) { return; }

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
	UpdateUI(_scrollX);
	ParticleUpdate(_scrollX);

	m_mat = Math::Matrix::CreateScale(m_scale * m_dir, m_scale, 0) * Math::Matrix::CreateTranslation(m_pos.x - _scrollX, m_pos.y, 0);
}

bool Slime::Attack()
{
	Player* ply = m_pOwner->GetPlayer();

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
			if (m_move.x > 0) { m_dir = DefaultDir * Reverse; }
			else { m_dir = DefaultDir; }
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
	if (GetAttackHitCnt() <= 1) { m_pOwner->SetTrueBigShake(); }
	else { m_pOwner->SetTrueSmallShake(); }
}

void Slime::Release()
{
}