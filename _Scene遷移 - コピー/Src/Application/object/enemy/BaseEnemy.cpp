#include "BaseEnemy.h"
#include "enemypattern/EnemyPattern.h"
#include "enemypattern/EnemyDeath.h"
#include "enemypattern/EnemyRun.h"
#include "../../utility/utility.h"

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
}