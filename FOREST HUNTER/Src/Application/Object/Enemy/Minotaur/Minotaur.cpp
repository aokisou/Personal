#include "Minotaur.h"
#include "../../../Scene/BaseSCene/Game/GameScene.h"
#include "../../Player/Player.h"
#include "../../Player/PlayerPattern/PlayerPattern.h"
#include "../EnemyPattern/EnemyPattern.h"
#include "../EnemyPattern/Death/EnemyDeath.h"
#include "../EnemyPattern/Run/EnemyRun.h"
#include "../EnemyPattern/Attack/EnemyAttack.h"
#include "../EnemyPattern/Attack2/EnemyAttack2.h"
#include "../EnemyPattern/Boss/EntryBoss.h"
#include "../../../UI/HP/Enemy/EnemyHPBar.h"
#include "../../../Utility/Utility.h"

#define RunSpeed 3.0f			//攻撃状態の時
#define Dmg 10					//通常攻撃時のダメージ
#define Dmg2 15					//回転攻撃時のダメージ
#define AttackIntervalSec 1		//攻撃間隔
#define MaxHP 100				//初期HP

void Minotaur::Init(Math::Vector2 _pos)
{
	const int ImgSize = 96;		//キャラ画像サイズ
	const float Scale = 2.5f;	//キャラ拡大率

	m_pos = { _pos };
	m_move = { 0 };
	m_mat = Math::Matrix::Identity;
	m_bAlive = true;
	m_size = ImgSize;
	m_scale = Scale;
	m_dir = DEFAULTDIR * REVERSE;
	m_hp = MaxHP;
	m_bDmg = false;
	DmgEfcCnt = 0;
	m_moveRange = 100;
	m_attackRange = 30;
	m_attackCoolTime = 0;
	SetEntryState();
	InitUI();
	m_startPos = m_pos;
}

void Minotaur::Action()
{
	if (m_pState->GetStateType() >= enemyAttack && m_bAlive) { return; }
	if (!m_bAlive) //乗っかれるように当たり判定
	{
		Player* p = m_pOwner->GetPlayer();
		const float plyRight	= p->GetPos().x + p->GetHalfSize() - p->GetSpaceWidthImg();
		const float plyLeft		= p->GetPos().x - p->GetHalfSize() + p->GetSpaceWidthImg();
		const float plyTop		= p->GetPos().y + p->GetHalfSize() - p->GetSpaceHeightImg();
		const float plyBottom	= p->GetPos().y - p->GetHalfSize() + p->GetSpaceHeightImg();

		const float plyNextRight	= p->GetFuturePos().x + p->GetHalfSize() - p->GetSpaceWidthImg();
		const float plyNextLeft		= p->GetFuturePos().x - p->GetHalfSize() + p->GetSpaceWidthImg();
		const float plyNextTop		= p->GetFuturePos().y + p->GetHalfSize() - p->GetSpaceHeightImg();
		const float plyNextBottom	= p->GetFuturePos().y - p->GetHalfSize() + p->GetSpaceHeightImg();

		const float emyRight	= GetPos().x + GetHalfSize() - GetDeadSpaceRightImg() * abs((m_dir - 1) / HALF)
															 - GetDeadSpaceLeftImg() * abs((m_dir + 1) / HALF);
		const float emyLeft		= GetPos().x - GetHalfSize() + GetDeadSpaceRightImg() * abs((m_dir + 1) / HALF)
															 + GetDeadSpaceLeftImg() * abs((m_dir - 1) / HALF);
		const float emyTop		= GetPos().y + GetHalfSize() - GetDeadSpaceTopImg();
		const float emyBottom	= GetPos().y - GetHalfSize() + GetDeadSpaceBottomImg();

		if (plyRight > emyLeft && plyLeft < emyRight)
		{
			if (plyNextBottom < emyTop && plyNextTop > emyTop)
			{
				p->MapHitY(emyTop + p->GetHalfSize() - p->GetSpaceHeightImg(), 0.f, false);
			}
			else if (plyNextTop > emyBottom && plyNextBottom < emyBottom)
			{
				p->MapHitY(emyBottom - p->GetHalfSize() + p->GetSpaceHeightImg(), 0.f, true);
			}
		}
		else if (plyTop > emyBottom && plyBottom < emyTop)
		{
			if (plyNextLeft < emyRight && plyNextRight > emyRight)
			{
				p->MapHitX(emyRight + p->GetHalfSize() - p->GetSpaceWidthImg(), 0.f);
			}
			else if (plyNextRight > emyLeft && plyNextLeft < emyLeft)
			{
				p->MapHitX(emyLeft - p->GetHalfSize() + p->GetSpaceWidthImg(), 0.f);
			}
		}
		return;
	}

	m_move = { 0,m_move.y - GRAVITY };

	if (Attack())
	{
		return;
	}
}

void Minotaur::Update(float _scrollX)
{
	if (!m_bAlive) { return; }

	if (m_pState->GetStateType() <= enemyDeath || m_pState->GetStateType() == enemyBossEntry)
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
					m_hp = 0.0f;
					SetDeathState();
				}
			}
		}

		m_pos += m_move;
	}

	m_pState->Update();
	UpdateUI(_scrollX);
	ParticleUpdate(_scrollX);

	m_mat = Math::Matrix::CreateScale(m_scale * m_dir, m_scale, 0.0f) * Math::Matrix::CreateTranslation(m_pos.x - _scrollX, m_pos.y, 0);
}

bool Minotaur::Attack()
{
	m_attackCoolTime++;
	Player* ply = m_pOwner->GetPlayer();

	if (ply->GetPlayerState()->GetStateType() == playerDeath || ply->GetPlayerState()->GetStateType() == playerGetHit) { return false; }

	const float plyTop = ply->GetPos().y + ply->GetHalfSize() - ply->GetSpaceHeightImg();
	const float plyBottom = ply->GetPos().y - ply->GetHalfSize() + ply->GetSpaceHeightImg();

	const float emyTop = GetPos().y + GetHalfSize();
	const float emyBottom = GetPos().y - GetHalfSize() + GetSpaceHeightImg();

	if (abs(ply->GetFuturePos().x - GetFuturePos().x) < m_attackRange)
	{
		if (m_attackCoolTime < *m_pOwner->GetMAXfps() * AttackIntervalSec)
		{
			return true;
		}

		if (ply->GetFuturePos().x - GetFuturePos().x < 0) { m_dir = DEFAULTDIR * REVERSE; }
		else { m_dir = DEFAULTDIR; }

		if (m_pState->GetStateType() != enemyAttack)
		{
			if (m_hp > MaxHP / HALF) { SetAttackState(); }
			else 
			{
				if (rand() % 4 < 1) { SetAttackState(); }
				else { SetAttack2State(); }
			}
		}
		return true;
	}
	else
	{
		float a = GetAngleDeg(GetFuturePos(), ply->GetFuturePos());
		if (cos(DirectX::XMConvertToRadians(a)) < 0) { m_dir = DEFAULTDIR * REVERSE; }
		else { m_dir = DEFAULTDIR; }
		m_move.x = RunSpeed * m_dir;
		CreateWalk();
		return true;
	}
}

void Minotaur::UpdateUI(float _scrollX)
{
	m_pHPBar->Update(&m_hp, MaxHP, { m_pos.x - _scrollX, m_pos.y + GetHalfSize() - GetUISpaceTop()});
}

void Minotaur::DrawUI()
{
	if (!m_bAlive) { return; }
	m_pHPBar->Draw(MaxHP);
}

void Minotaur::SetRunState()
{
	m_pState = std::make_shared<EnemyRun>();
	m_pState->Init(this, m_fileName[enemyRun]);
}

void Minotaur::SetDeathState()
{
	m_pState = std::make_shared<EnemyDeath>();
	m_pState->Init(this, m_fileName[enemyDeath]);
}

void Minotaur::SetAttackState()
{
	m_dmg = Dmg;
	m_pState = std::make_shared<EnemyAttack>();
	m_pState->Init(this, m_fileName[enemyAttack]);
}

void Minotaur::SetAttack2State()
{
	m_dmg = Dmg2;
	m_pState = std::make_shared<EnemyAttack2>();
	m_pState->Init(this, m_fileName[enemyBossEntry]);
}

void Minotaur::SetEntryState()
{
	m_pState = std::make_shared<EnemyEntry>();
	m_pState->Init(this, m_fileName[enemyBossEntry]);
}

void Minotaur::Release()
{
}