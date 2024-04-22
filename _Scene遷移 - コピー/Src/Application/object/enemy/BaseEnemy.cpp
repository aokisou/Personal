#include "BaseEnemy.h"
#include "EnemyPattern/Death/EnemyDeath.h"
#include "EnemyPattern/Run/EnemyRun.h"
#include "../../Utility/Utility.h"

void BaseEnemy::Init()
{
}

void BaseEnemy::Action()
{
	if (m_bDead || !m_bAlive) { return; }
}

void BaseEnemy::Update(float _scrollX)
{
	if (!m_bAlive) { return; }
	m_pos += m_move;
	m_mat = Math::Matrix::CreateScale(m_Scale, m_Scale, 0) * Math::Matrix::CreateTranslation(m_pos.x - _scrollX, m_pos.y, 0);
}

void BaseEnemy::Draw()
{
	if (!m_bAlive) { return; }
	Math::Color col = { 1,1,1,1 };
	if (m_bDmg)col = { 1,0,0,1 };
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pState->GetTex(), 0, 0, &Math::Rectangle(m_pState->GetAnimeCnt() * m_Size, m_pState->GetStateType() * m_Size, m_Size, m_Size), &col);
}

float BaseEnemy::GetAngleDeg(Math::Vector2 src, Math::Vector2 dest)
{
	float a, b, rad, deg;

	a = dest.x - src.x;
	b = dest.y - src.y;
	rad = atan2(b, a);

	deg = DirectX::XMConvertToDegrees(rad);

	if (deg < 0)
	{
		deg += 360;
	}
	return deg;
}