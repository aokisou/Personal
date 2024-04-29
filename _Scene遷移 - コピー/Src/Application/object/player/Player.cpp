#include "player.h"
#include "../../Scene/BaseScene/Game/GameScene.h"
#include "../Arrow/Arrow.h"
#include "PlayerPattern/Run/PlayerRun.h"
#include "PlayerPattern/Death/PlayerDeath.h"
#include "PlayerPattern/Jump/PlayerJump.h"
#include "PlayerPattern/Attack/PlayerAttack.h"
#include "PlayerPattern/GetHit/PlayerGetHit.h"
#include "PlayerPattern/Stand/PlayerStand.h"
#include "PlayerPattern/Fall/PlayerFall.h"
#include "../../UI/HP/Player/PlayerHPBar.h"
#include "../../utility/Utility.h"

//プレイヤー
#define MovePow 5			//速度
#define JumpPow 15			//ジャンプ力
#define ShotInterval 6		//弾を打つ感覚(Maxfps/この数値)
#define MoveRange -150.0f	//移動範囲
#define StartPosX -600.0f	//開始X座標
#define StartPosY -100.0f		//開始Y座標
#define MaxHP 1			//開始HP
#define MaxDmgEfcCnt 20		//赤く光る時間
#define ArrowCRX 30			//弾の出る位置を銃まで補正X座標
#define ArrowCRY 6			//弾の出る位置を銃まで補正Y座標
#define ImgSize 100			//キャラ画像サイズ
#define Scale 1.0f			//キャラ拡大率

void Player::Init()
{
	m_pos = { StartPosX,StartPosY };
	m_move = {};
	m_mat = Math::Matrix::Identity;
	m_bAlive = true;
	m_dir = DefaultDir;
	m_size = ImgSize;
	m_scale = Scale;
	m_moveKnockBack = 0.f;
	m_hp = MaxHP;
	m_bJump = false;
	m_bDmg = false;
	SetStandState();
	m_arrowTex.Load("Texture/Arrow/static.png");
	m_hpBar = std::make_shared<PlayerHPBar>();
}

void Player::Action()
{
	if (m_pState->GetStateType() == playerDeath || m_bDmg)//矢の処理と移動速度をリセットして帰る
	{
		m_move = { 0,m_move.y - Gravity };
		for (Arrow* i : m_arrow)
		{
			i->Action();
		}
		return;
	}

	bool bAct = false;
	const float a = -1.f;//この値まで行ったらFall状態にする

	m_move = { 0,m_move.y - Gravity };//リセットと重力をかける

	bAct = ArrowShot();

	if (m_pState->GetStateType() != playerAttack)//攻撃時は移動できない
	{
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_move.x = -MovePow;
			m_dir = -DefaultDir;
			if (m_pState->GetStateType() != playerRun)
			{
				SetRunState();
			}
			bAct = true;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_move.x = MovePow;
			m_dir = DefaultDir;
			if (m_pState->GetStateType() != playerRun)
			{
				SetRunState();
			}
			bAct = true;
		}
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (!m_bJump)
		{
			m_move.y += JumpPow;
			if (m_pState->GetStateType() != playerAttack)
			{
				SetJumpState();
			}
			m_bJump = true;
			bAct = true;
		}
	}

	if (m_bJump && m_move.y < a)
	{
		if (m_pState->GetStateType() < playerAttack)
		{
			SetFallState();
		}
		bAct = true;
	}

	for (Arrow* i : m_arrow)
	{
		i->Action();
	}

	if (!bAct)
	{
		if (m_pState->GetStateType() > playerDeath)
		{
			SetStandState();
		}
	}
}

void Player::Update(float _scrollX)
{
	if (!m_bAlive) { return; }

	m_pState->Update();

	ArrowActivate(_scrollX);

	m_move.x += m_moveKnockBack;
	m_pos += m_move;

	if (m_pos.y - GetHalfSize() < -(SCREEN::height / Half))
	{
		m_bAlive = false;
	}

	UpdateUI();

	m_mat = Math::Matrix::CreateScale(m_scale * m_dir, m_scale, 0.0f) * Math::Matrix::CreateTranslation(m_pos.x - _scrollX, m_pos.y, 0.0f);
}

void Player::Draw()
{
	if (!m_bAlive) { return; }

	for (Arrow* i : m_arrow)
	{
		i->Draw();
	}

	Math::Color col = { 1,1,1,1 };
	if (m_bDmg)col = { 1,0,0,(float)m_pState->GetAnimeNum() / m_pState->GetMaxAnimeNum() * 0.7f + 0.3f };

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pState->GetTex(), 0, 0,
		&Math::Rectangle(m_size * m_pState->GetAnimeNum(), 0, m_size, m_size), &col);
}

void Player::Reset()
{
	m_pos = { StartPosX,StartPosY };
	m_move = {};
	m_mat = Math::Matrix::Identity;
	m_bAlive = true;
	m_dir = DefaultDir;
	m_size = ImgSize;
	m_scale = Scale;
	m_moveKnockBack = 0.f;
	m_hp = MaxHP;
	m_bJump = false;
	m_bDmg = false;
	SetStandState();
	ArrowDel();
}

void Player::UpdateUI()
{
	m_hpBar->Update(&m_hp,MaxHP);
}

void Player::DrawUI()
{
	m_hpBar->Draw(MaxHP);
}

void Player::SetStandState()
{
	m_pState = std::make_shared<PlayerStand>();
	m_pState->Init(this, m_fileName[playerStand]);
}

void Player::SetJumpState()
{
	m_pState = std::make_shared<PlayerJump>();
	m_pState->Init(this, m_fileName[playerJump]);
}

void Player::SetRunState()
{
	m_pState = std::make_shared<PlayerRun>();
	m_pState->Init(this, m_fileName[playerRun]);
}

void Player::SetDeathState()
{
	m_pState = std::make_shared<PlayerDeath>();
	m_pState->Init(this, m_fileName[playerDeath]);
}

void Player::SetAttackState()
{
	m_pState = std::make_shared<PlayerAttack>();
	m_pState->Init(this, m_fileName[playerAttack]);
}

void Player::SetFallState()
{
	m_pState = std::make_shared<PlayerFall>();
	m_pState->Init(this, m_fileName[playerFall]);
}

void Player::SetGetHitState()
{
	m_pState = std::make_shared<PlayerGetHit>();
	m_pState->Init(this, m_fileName[playerGetHit]);
}

void Player::EndDamageEfc()
{
	m_bDmg = false;
	m_moveKnockBack = 0;
	if (m_hp <= 0)
	{
		m_hp = 0;
		SetDeathState();
	}
	else { SetStandState(); }
}

void Player::SetDmg(int _hp,float _enemyMove)
{
	m_bDmg = true;
	m_hp -= _hp;
	m_moveKnockBack = _enemyMove;
	SetGetHitState();
}

void Player::MapHitX(float _posX, float _moveX)
{
	m_pos.x = _posX;
	m_move.x = _moveX;
	m_moveKnockBack = _moveX;
}

void Player::MapHitY(float _posY, float _moveY, bool _b)
{
	m_pos.y = _posY;
	m_move.y = _moveY;
	m_bJump = _b;
}

bool Player::ArrowShot()
{
	bool a = false;			//アクションしているか
	static bool b = false;	//矢を1フレームだけ放つ

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		a = true;
		const int c = 4;//矢を打つアニメーションのタイミング

		if (m_pState->GetStateType() != playerAttack)
		{
			SetAttackState();
		}
		if (m_pState->GetAnimeNum() == c && !b)
		{
			Arrow* tmpArrow = new Arrow;

			tmpArrow->SetPos({ m_pos.x + ArrowCRX * m_scale * m_dir, m_pos.y + ArrowCRY * m_scale });
			tmpArrow->SetScale(m_scale);
			tmpArrow->SetDir(m_dir);
			tmpArrow->SetTex(&m_arrowTex);

			m_arrow.push_back(tmpArrow);
			b = true;
		}
	}

	if (m_pState->GetAnimeNum() == m_pState->GetMaxAnimeNum())
	{
		a = false; 
		b = false;
	}

	return a;
}

void Player::ArrowActivate(float _scrollX)
{
	for (Arrow* i : m_arrow)
	{
		i->Update(_scrollX);
	}

	std::vector<Arrow*>::iterator it = m_arrow.begin();
	while (it != m_arrow.end())
	{
		if (!(*it)->GetAlive())
		{
			delete* it;
			it = m_arrow.erase(it);
		}
		else { it++; }
	}
}

void Player::ArrowDel()
{
	std::vector<Arrow*>::iterator it = m_arrow.begin();
	while (it != m_arrow.end())
	{
		delete* it;
		it = m_arrow.erase(it);
	}
}

void Player::Release()
{
	//実行終了時
	ArrowDel();
}