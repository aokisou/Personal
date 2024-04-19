#include "player.h"
#include "../../scene/game/GameScene.h"
#include "../arrow/Arrow.h"
#include "playerpattern/PlayerPattern.h"
#include "playerpattern/PlayerRun.h"
#include "playerpattern/PlayerDeath.h"
#include "playerpattern/PlayerJump.h"
#include "playerpattern/PlayerAttack.h"
#include "../../utility/utility.h"

//プレイヤー
#define PlySpeed 5			//プレイヤー速度
#define PlyJumpPow 15		//プレイヤーのジャンプ力
#define PlyShotInterval 6	//プレイヤーの弾を打つ感覚(Maxfps/この数値)
#define PlyMoveRange -150	//プレイヤーの移動範囲
#define PlyStartPosX -600	//プレイヤーの開始X座標
#define PlyStartPosY 0	//プレイヤーの開始Y座標
#define PlyStartHP 5		//プレイヤーの開始HP
#define PlyMaxDmgEfcCnt 20	//赤く光る時間
#define PlyBltCRX 30		//弾の出る位置を銃まで補正X座標
#define PlyBltCRY 6			//弾の出る位置を銃まで補正Y座標
#define ImgSize 100		//キャラ画像サイズ
#define Scale 1			//キャラ拡大率

void Player::Init()
{
	m_pos = { PlyStartPosX,PlyStartPosY };
	m_move = { 0 };
	m_mat = Math::Matrix::Identity;
	m_bAlive = true;
	m_dir = DefaultDir;
	m_Size = ImgSize;
	m_Scale = Scale;
	m_hp = PlyStartHP;
	m_bJump = false;
	m_bShot = false;
	m_shotInterval = 0;
	m_bDmg = false;
	m_DmgEfcCnt = 0;
	m_pState = new PlayerPattern;
	m_pState->Init(this, "Texture/player/Idle.png");
}

void Player::Action()
{
	if (!m_bAlive) { return; }
	bool bAct = false;

	m_move = { 0,m_move.y - Gravity };

	//ジャンプしてたらスタンドにならないように
	bAct = m_bJump;
	bAct = ArrowShot();

	if (m_pState->GetStateType() != playerAttack)//攻撃時は移動できない
	{
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_move.x = -PlySpeed;
			m_dir = -DefaultDir;
			if (m_pState->GetStateType() != playerRun)
			{
				SetRunState();
			}
			bAct = true;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_move.x = PlySpeed;
			m_dir = DefaultDir;
			if (m_pState->GetStateType() != playerRun)
			{
				SetRunState();
			}
			bAct = true;
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			if (!m_bJump)
			{
				m_move.y += PlyJumpPow;
				SetJumpState();
				m_bJump = true;
				bAct = true;
			}
		}
	}

	for (Arrow* i : m_arrow)
	{
		i->Action();
	}

	if (!bAct)
	{
		if (m_pState->GetStateType() != playerStand)
		{
			SetStandState();
		}
	}
}

void Player::Update(float _scrollX)
{
	if (!m_bAlive) { return; }

	if (m_bDmg)
	{
		m_DmgEfcCnt++;
		if (m_DmgEfcCnt > PlyMaxDmgEfcCnt)
		{
			m_bDmg = false;
			m_DmgEfcCnt = 0;
			if (m_hp <= 0) 
			{ 
				m_bDmg = false;
				SetDeathState();
			}
		}
	}

	m_pState->Update();

	ArrowActivate(_scrollX);

	m_pos += m_move;

	if (m_pos.y - (m_Size / Half * m_Scale) < -(SCREEN::height / Half))
	{
		m_bAlive = false;
	}

	m_mat = Math::Matrix::CreateScale(m_Scale * m_dir, m_Scale, 0) * Math::Matrix::CreateTranslation(m_pos.x - _scrollX, m_pos.y, 0);
}

void Player::Draw()
{
	if (!m_bAlive) { return; }

	for (Arrow* i : m_arrow)
	{
		i->Draw();
	}

	Math::Color col = { 1,1,1,1 };
	if (m_bDmg)col = { 1,0,0,1 };

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pState->GetTex(), 0, 0,
		&Math::Rectangle(m_Size * m_pState->GetAnimeCnt(), 0, m_Size, m_Size), &col);
}

void Player::SetStandState()
{
	delete m_pState;
	m_pState = new PlayerPattern;
	m_pState->Init(this, "Texture/player/Idle.png");
}

void Player::SetJumpState()
{
	delete m_pState;
	m_pState = new PlayerJump;
	m_pState->Init(this, "Texture/player/Jump.png");
}

void Player::SetRunState()
{
	delete m_pState;
	m_pState = new PlayerRun;
	m_pState->Init(this, "Texture/player/Run.png");
}

void Player::SetDeathState()
{
	delete m_pState;
	m_pState = new PlayerDeath;
	m_pState->Init(this, "Texture/player/Death.png");
}

void Player::SetAttackState()
{
	delete m_pState;
	m_pState = new PlayerAttack;
	m_pState->Init(this, "Texture/player/Attack.png");
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
		const int c = 4;//矢を打つアニメーションのタイミング

		if (!m_bShot)
		{
			SetAttackState();
		}
		m_bShot = true;
		a = true;
		if (m_pState->GetAnimeCnt() == c && !b)
		{
			Arrow* tmpArrow = new Arrow;

			tmpArrow->SetPos({ m_pos.x + PlyBltCRX * m_dir, m_pos.y + PlyBltCRY });
			tmpArrow->SetDir(m_dir);

			m_arrow.push_back(tmpArrow);
			b = true;
		}
	}
	else
	{
		m_bShot = false;
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
		if (!(*it)->GetbAlive())
		{
			delete* it;
			it = m_arrow.erase(it);
		}
		else { it++; }
	}
}

void Player::Release()
{
	//実行終了時
	std::vector<Arrow*>::iterator it = m_arrow.begin();
	while (it != m_arrow.end())
	{
		delete* it;
		it = m_arrow.erase(it);
	}
	delete m_pState;
}