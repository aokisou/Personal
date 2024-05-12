#include "Arrow.h"
#include "../../Utility/Utility.h"

#define ARROWSPEED 20			//��̑��x
#define ARROWSIZE 24			//��摜�T�C�Y
#define ARROWSCALE 1			//��g�嗦
#define ARROWACCELERATION 0.99f	//������
#define ARROWDOWN 0.0f			//�����x�����̒l�܂ŗ����痎����
#define DMG 2					//�_���[�W

float Arrow::GetDmg()
{
	return DMG;
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
	m_bFirst = true;
}

void Arrow::Action()
{
	if (!m_bAlive) { return; }

	m_move.x = ARROWSPEED * m_acceleration * m_dir;

	m_acceleration *= ARROWACCELERATION;
	if (m_acceleration < 0.1f)
	{
		SetFalseAlive();
	}
}

void Arrow::Update(float _scrollX)
{
	if (!m_bAlive) { return; }
	m_pos += m_move;
	if (m_pos.y - m_size * m_scale < -(SCREEN::height / HALF))m_bAlive = false;
	m_mat = Math::Matrix::CreateScale(m_scale * m_dir, m_scale, 0)
		* Math::Matrix::CreateTranslation(m_pos.x - _scrollX, m_pos.y, 0);
}

void Arrow::Draw()
{
	if (!m_bAlive) { return; }
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTex, Math::Rectangle(0, 0, m_size, 5));
}