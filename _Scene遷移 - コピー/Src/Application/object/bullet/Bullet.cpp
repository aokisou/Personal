#include "bullet.h"
#include "../../utility/utility.h"

void Bullet::Init()
{
	m_pos = { };
	m_move = { };
	m_mat = Math::Matrix::Identity;
	m_bAlive = true;
	m_Size = BltSize;
	m_Scale = BltScale;
}

void Bullet::Action()
{
	if (!m_bAlive) { return; }
	m_move.x = BltSpeed * m_dir;
}

void Bullet::Update()
{
	if (!m_bAlive) { return; }
	m_pos += m_move;
	if (m_pos.y - m_Size * m_Scale > (SCREEN::height / Half))m_bAlive = false;
	m_mat = Math::Matrix::CreateScale(m_Scale * m_dir, m_Scale, 0) * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void Bullet::Draw()
{
	if (!m_bAlive) { return; }
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTex, Math::Rectangle(288, 25, m_Size, 1));
}