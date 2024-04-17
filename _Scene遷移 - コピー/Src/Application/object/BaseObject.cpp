#include "BaseObject.h"
#include "../utility/utility.h"

void BaseObject::Init()
{
	m_pos = { 0 };
	m_move = { 0 };
	m_mat = Math::Matrix::Identity;
}

void BaseObject::Action()
{
	if (!m_bAlive) { return; }
}

void BaseObject::Update()
{
	if (!m_bAlive) { return; }
	m_pos += m_move;
	m_mat = Math::Matrix::CreateScale(2, 2, 0) * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void BaseObject::Draw()
{
	if (!m_bAlive) { return; }
	//overrideされていなかったら時機表示
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_tex, Math::Rectangle(1, 1, 30, 30));
}

int BaseObject::GetHalfSize()
{
	return (m_Size * m_Scale) / Half;
}

void BaseObject::MapHitX(float _posX, float _moveX)
{
	m_pos.x = _posX;
	m_move.x = _moveX;
}

void BaseObject::MapHitY(float _posY, float _moveY, bool _b)
{
	m_pos.y = _posY;
	m_move.y = _moveY;
}

void BaseObject::Release()
{

}