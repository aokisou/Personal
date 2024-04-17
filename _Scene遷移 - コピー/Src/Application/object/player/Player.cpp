#include "player.h"
#include "../../scene/game/GameScene.h"
#include "../bullet/Bullet.h"
#include "playerpattern/Run.h"
#include "playerpattern/Death.h"
#include "playerpattern/Jump.h"
#include "../../utility/utility.h"

void Player::Init()
{
	m_pos = { 0,PlyStartPos };
	m_move = { 0 };
	m_mat = Math::Matrix::Identity;
	m_bAlive = true;
	m_shotinterval = 0;
	m_dir = DefaultDir;
	m_Size = ChrImgSize;
	m_Scale = ChrScale;
	m_hp = PlyStartHP;
	m_bJump = false;
	m_bshot = false;
	m_shotinterval = 0;
	m_bDmg = false;
	m_DmgEfcCnt = 0;
	m_pState = new PlayerPattern;
	m_pState->Init(this);
}

void Player::Action()
{
	if (!m_bAlive) { return; }
	bool bAct = false;

	m_move = { 0,-Gravity };

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_move.x = -PlySpeed;
		m_dir = -DefaultDir;
		if (m_pState->GetStateType() != run)
		{
			SetRunState();
		}
		bAct = true;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_move.x = PlySpeed;
		m_dir = DefaultDir;
		if (m_pState->GetStateType() != run)
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

	BulletShot();

	for (Bullet* i : m_bullet)
	{
		i->Action();
	}

	if (!bAct)
	{
		if (m_pState->GetStateType() != stand && !m_bJump)
		{
			SetStandState();
		}
	}
}

void Player::Update()
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
				SetDeadState();
			}
		}
	}

	if (m_pos.x - (m_Size / Half * m_Scale) + m_move.x < -(SCREEN::width / Half))
	{
		m_pos.x = -SCREEN::width / Half + (m_Size / Half * m_Scale);
		m_move.x = 0;
	}
	if (m_pos.x + (m_Size / Half * m_Scale) + m_move.x > (SCREEN::width / Half))
	{
		m_pos.x = SCREEN::width / Half - (m_Size / Half * m_Scale);
		m_move.x = 0;
	}

	m_pState->Update();

	BulletActivate();

	m_pos += m_move;

	m_mat = Math::Matrix::CreateScale(m_Scale * m_dir, m_Scale, 0) * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_shadowMat = Math::Matrix::CreateScale(m_Scale, m_Scale, 0) * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y - 30, 0);
}

void Player::Draw()
{
	if (!m_bAlive) { return; }

	for (Bullet* i : m_bullet)
	{
		i->Draw();
	}

	Math::Color col = { 1,1,1,1 };
	if (m_bDmg)col = { 1,0,0,1 };

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTex, 0,0,
		&Math::Rectangle(m_Size * m_pState->GetAnimeCnt(), m_Size * m_pState->GetStateType(), m_Size, m_Size), &col);

	if (m_bJump) { col = { 1,1,1,1 - (abs(m_move.y) / PlyJumpPow) }; }
	else{ col = { 1,1,1,1 }; }

	SHADER.m_spriteShader.SetMatrix(m_shadowMat);
	SHADER.m_spriteShader.DrawTex(m_pTex, 0, 0, &Math::Rectangle(288, 0, 16, 16),&col);
}

void Player::SetStandState()
{
	delete m_pState;
	m_pState = new PlayerPattern;
	m_pState->Init(this);
}

void Player::SetJumpState()
{
	delete m_pState;
	m_pState = new PlayerJump;
	m_pState->Init(this);
}

void Player::SetRunState()
{
	delete m_pState;
	m_pState = new PlayerRun;
	m_pState->Init(this);
}

void Player::SetDeadState()
{
	delete m_pState;
	m_pState = new PlayerDeath;
	m_pState->Init(this);
}

void Player::MapHitY(float _posY, float _moveY, bool _b)
{
	m_pos.y = _posY;
	m_move.y = _moveY;
	m_bJump = _b;
}

void Player::BulletShot()
{
	if (m_bshot) { m_shotinterval++; }

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (!m_bshot)
		{
			Bullet* tmpbullet = new Bullet;

			tmpbullet->Init();
			tmpbullet->SetPos({ m_pos.x + PlyBltCRX * m_dir, m_pos.y + PlyBltCRY});
			tmpbullet->SetDir(m_dir);
			tmpbullet->SetTexture(m_pTex);

			m_bullet.push_back(tmpbullet);
		}
		m_bshot = true;
	}

	if ((m_pOwner->GetMAXfps() / PlyShotInterval) < m_shotinterval)
	{
		m_bshot = false;
		m_shotinterval -= (m_pOwner->GetMAXfps() / PlyShotInterval);
	}
}

void Player::BulletActivate()
{
	for (Bullet* i : m_bullet)
	{
		i->Update();
	}

	std::vector<Bullet*>::iterator it = m_bullet.begin();
	while (it != m_bullet.end())
	{
		if (!(*it)->GetbAlive())
		{
			delete* it;
			it = m_bullet.erase(it);
		}
		else { it++; }
	}
}

void Player::Release()
{
	//é¿çsèIóπéû
	std::vector<Bullet*>::iterator it = m_bullet.begin();
	while (it != m_bullet.end())
	{
		delete* it;
		it = m_bullet.erase(it);
	}
}