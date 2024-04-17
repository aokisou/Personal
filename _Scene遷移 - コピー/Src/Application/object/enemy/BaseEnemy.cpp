#include "BaseEnemy.h"
#include "../../utility/utility.h"

void BaseEnemy::Init()
{
	m_pos = { 0 };
	m_move = { 0,-3 };
	m_mat = Math::Matrix::Identity;
	m_bAlive = true;
	m_Size = ChrImgSize;
	m_Scale = ChrScale;
	m_hp = 5;
	m_bDead = false;
	m_ExpNum = 0;
	m_ExpCnt = 0;
	m_bDmg = false;
	DmgEfcCnt = 0;
}

void BaseEnemy::Action()
{
	if (m_bDead || !m_bAlive) { return; }
}

void BaseEnemy::Update()
{
	if (!m_bAlive) { return; }
	if (m_bDmg)
	{
		DmgEfcCnt++;
		if (DmgEfcCnt > EmyMaxDmgEfcCnt)
		{
			m_bDmg = false;
			DmgEfcCnt = 0;
			if (m_hp <= 0) { m_bDead = true; }
		}
	}

	if (m_bDead)
	{
		m_ExpCnt++;
		if (m_ExpCnt > ExpOneTime)
		{
			m_ExpNum++;
			m_ExpCnt -= ExpOneTime;
			if (m_ExpNum > ExpNum)
			{
				DisableAlive();
				m_ExpNum = 0;
			}
		}
	}

	if (m_pos.y < -SCREEN::height / Half)m_pos.y = 0;

	m_pos += m_move;
	m_mat = Math::Matrix::CreateScale(m_Scale, m_Scale, 0) * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void BaseEnemy::Draw()
{
	if (!m_bAlive) { return; }
	Math::Color col = { 1,1,1,1 };
	if (m_bDmg)col = { 1,0,0,1 };
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_tex, 0, 0, &Math::Rectangle(0, 0, m_Size, m_Size), &col);
}