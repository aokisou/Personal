#include "Arrow.h"
#include "../../Utility/Utility.h"

#define ArrowSpeed 20			//矢の速度
#define ArrowSize 24			//矢画像サイズ
#define ArrowScale 1			//矢拡大率
#define ArrowAccelelation 0.97f	//減速率
#define ArrowDown 0.6f			//加速度がこの値まで来たら落ちる

float Arrow::GetDmg()
{
	if (m_accelerlation > 0.9f) { return abs(m_move.x) * 2; }
	else { return abs(m_move.x); }
}

void Arrow::Init()
{
	m_pos = {  };
	m_move = {  };
	m_mat = Math::Matrix::Identity;
	m_bAlive = true;
	m_size = ArrowSize;
	m_scale = ArrowScale;
	m_accelerlation = 1.f;
	m_angle = 0;
}

void Arrow::Action()
{
	if (!m_bAlive) { return; }

	m_move.x = ArrowSpeed * m_accelerlation * m_dir;

	m_accelerlation *= ArrowAccelelation;
	if (m_accelerlation < ArrowDown)
	{
		m_move.y = -cos(m_accelerlation) * 2.f;
		m_angle-= 0.01f;
		if (m_angle < -1.0f)
		{
			m_angle = -1.0f;
		}
		if (m_accelerlation < 0.01f)
		{
			m_accelerlation = 0.0f;
		}
	}
}

void Arrow::Update(float _scrollX)
{
	if (!m_bAlive) { return; }
	m_pos += m_move;
	if (m_pos.y - m_size * m_scale < -(SCREEN::height / Half))m_bAlive = false;
	m_mat = Math::Matrix::CreateScale(m_scale * m_dir, m_scale, 0) * Math::Matrix::CreateRotationZ(m_angle * m_dir) 
		* Math::Matrix::CreateTranslation(m_pos.x - _scrollX, m_pos.y, 0);
}

void Arrow::Draw()
{
	if (!m_bAlive) { return; }
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTex, Math::Rectangle(0, 0, m_size, 5));
}