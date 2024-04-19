#include "Arrow.h"
#include "../../utility/utility.h"

#define ArrowSpeed 10			//�e�̑��x
#define ArrowSize 24			//�e�摜�T�C�Y
#define ArrowScale 1			//�e�g�嗦
#define ArrowAccelelation 0.99	//������
#define ArrowDown 0.6			//�����x�����̒l�܂ŗ����痎����

void Arrow::Init()
{
	m_pos = {  };
	m_move = {  };
	m_mat = Math::Matrix::Identity;
	m_bAlive = true;
	m_Size = ArrowSize;
	m_Scale = ArrowScale;
	m_accelerlation = 1.0f;
	m_angle = 0;
	m_tex.Load("Texture/Arrow/Move.png");
}

void Arrow::Action()
{
	if (!m_bAlive) { return; }
	m_move.x = ArrowSpeed * m_accelerlation * m_dir;

	m_accelerlation *= ArrowAccelelation;
	if (m_accelerlation < ArrowDown)
	{
		m_move.y = -cos(m_accelerlation);
		m_angle-= .01f;
		if (m_angle < -1.f)
		{
			m_angle = -1.f;
		}
		if (m_accelerlation < .01f)
		{
			m_accelerlation = 0.f;
		}
	}
}

void Arrow::Update(float _scrollX)
{
	if (!m_bAlive) { return; }
	m_pos += m_move;
	if (m_pos.y - m_Size * m_Scale > (SCREEN::height / Half))m_bAlive = false;
	m_mat = Math::Matrix::CreateRotationZ(m_angle) * Math::Matrix::CreateScale(m_Scale * m_dir, m_Scale, 0)
		* Math::Matrix::CreateTranslation(m_pos.x - _scrollX, m_pos.y, 0);
}

void Arrow::Draw()
{
	if (!m_bAlive) { return; }
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, Math::Rectangle(0, 0, m_Size, 5));
}