#include "Arrow.h"
#include "../../Utility/Utility.h"

#define ARROWSPEED 20			//矢の速度
#define ARROWSIZE 24			//矢画像サイズ
#define ARROWSCALE 1			//矢拡大率
#define ARROWACCELERATION 0.97f	//減速率
#define ARROWDOWN 0.6f			//加速度がこの値まで来たら落ちる
#define DMG 2					//速度 * この値がダメージになる

float Arrow::GetDmg()
{
	if (m_acceleration > 0.9f) { return abs(m_move.x) * DMG; }
	else { return abs(m_move.x); }
}

void Arrow::Init()
{
	m_pos = {  };
	m_move = {  };
	m_mat = Math::Matrix::Identity;
	m_bAlive = true;
	m_size = ARROWSIZE;
	m_scale = ARROWSCALE;
	m_acceleration = 1.f;
	m_angle = 0;
}

void Arrow::Action()
{
	if (!m_bAlive) { return; }

	m_move.x = ARROWSPEED * m_acceleration * m_dir;

	m_acceleration *= ARROWACCELERATION;
	if (m_acceleration < ARROWDOWN)
	{
		m_move.y = -cos(m_acceleration) * 3.f;
		m_angle-= 0.01f;
		if (m_angle < -1.0f)
		{
			m_angle = -1.0f;
		}
		if (m_acceleration < 0.01f)
		{
			m_acceleration = 0.0f;
		}
	}
}

void Arrow::Update(float _scrollX)
{
	if (!m_bAlive) { return; }
	m_pos += m_move;
	if (m_pos.y - m_size * m_scale < -(SCREEN::height / HALF))m_bAlive = false;
	m_mat = Math::Matrix::CreateScale(m_scale * m_dir, m_scale, 0) * Math::Matrix::CreateRotationZ(m_angle * m_dir) 
		* Math::Matrix::CreateTranslation(m_pos.x - _scrollX, m_pos.y, 0);
}

void Arrow::Draw()
{
	if (!m_bAlive) { return; }
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTex, Math::Rectangle(0, 0, m_size, 5));
}