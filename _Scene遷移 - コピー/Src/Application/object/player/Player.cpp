#include "player.h"
#include "../../scene/game/GameScene.h"
#include "../bullet/Bullet.h"
#include "pattern/Run.h"
#include "pattern/Death.h"
#include "pattern/Jump.h"
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
	m_State = new Pattern;
	m_State->Init(this);
}

void Player::Action()
{
	if (!m_bAlive) { return; }
	bool bAct = false;

	m_move = { 0,-Gravity };

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (m_pos.x + (m_Size / Half * m_Scale) + PlySpeed > (SCREEN::width / Half))
		{
			m_pos.x = SCREEN::width / Half - (m_Size / Half * m_Scale);
			m_State = new Pattern;
			m_State->Init(this);
			bAct = true;
		}
		else
		{
			m_move.x = PlySpeed;
			if (m_State->GetStateType() != run)
			{
				m_State = new Run;
				m_State->Init(this);
			}
			bAct = true;
		}
		m_dir = DefaultDir;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (m_pos.x - (m_Size / Half * m_Scale) - PlySpeed < -(SCREEN::width / Half))
		{
			m_pos.x = -SCREEN::width / Half + (m_Size / Half * m_Scale);
			m_State = new Pattern;
			m_State->Init(this);
			bAct = true;
		}
		else
		{
			m_move.x = -PlySpeed;
			if (m_State->GetStateType() != run)
			{
				m_State = new Run;
				m_State->Init(this);
			}
			bAct = true;
		}
		m_dir = -DefaultDir;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (!m_bJump)
		{
			m_move.y += PlyJumpPow;
			m_State = new Jump;
			m_State->Init(this);
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
		delete m_State;
		m_State = new Pattern;
		m_State->Init(this);
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
				m_State = new Death;
				m_State->Init(this);
			}
		}
	}

	m_State->Update();

	BulletActivate();

	m_pos += m_move;

	m_mat = Math::Matrix::CreateScale(m_Scale * m_dir, m_Scale, 0) * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
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
	SHADER.m_spriteShader.DrawTex(m_tex, 0,0,
		&Math::Rectangle(m_Size * m_State->GetAnimeCnt(), m_Size * m_State->GetStateType(), m_Size, m_Size), &col);
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
			tmpbullet->SetPos({ m_pos.x, m_pos.y + PlyBltCR});
			tmpbullet->SetTexture(m_tex);

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