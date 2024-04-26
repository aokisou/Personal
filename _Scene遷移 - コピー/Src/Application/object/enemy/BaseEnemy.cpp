#include "BaseEnemy.h"
#include "EnemyPattern/Death/EnemyDeath.h"
#include "EnemyPattern/Run/EnemyRun.h"
#include "EnemyPattern/Attack/EnemyAttack.h"
#include "../../Utility/Utility.h"

void BaseEnemy::Init()
{
}

void BaseEnemy::Action()
{
	if (m_pState->GetStateType() == enemyDeath || !m_bAlive) { return; }
}

void BaseEnemy::Update(float _scrollX)
{
	if (!m_bAlive) { return; }
	m_pos += m_move;
	m_mat = Math::Matrix::CreateScale(m_scale, m_scale, 0) * Math::Matrix::CreateTranslation(m_pos.x - _scrollX, m_pos.y, 0);
}

void BaseEnemy::Draw()
{
	if (!m_bAlive) { return; }
	Math::Color col = { 1,1,1,1 };
	if (m_bDmg)col = { 1,0,0,1 };
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pState->GetTex(), 0, 0, 
		&Math::Rectangle(m_pState->GetAnimeCnt() * m_size, m_pState->GetStateType() * m_size, m_size, m_size), &col);
}

void BaseEnemy::SetDamage(float _dmg)
{
	m_bDmg = true;
	m_hp -= _dmg;
	m_attackHitCnt++;
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