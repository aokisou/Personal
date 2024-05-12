#include "Walk.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/BaseEnemy.h"

void Walk::Update(float _scrollX)
{
	m_pos += m_move;
	m_size *= 0.98f;
	m_cnt--;
	if (m_cnt < 0) 
	{
		m_bAlive = false; 
		return;
	}
	m_mat = Math::Matrix::CreateScale(-m_pOwner->GetDir() * m_size,m_size,1.0f) * 
		Math::Matrix::CreateTranslation(m_pos.x - _scrollX - (m_pOwner->GetHalfSize() - m_pOwner->GetSpaceWidthImg()) * m_pOwner->GetDir(),
			m_pos.y - m_pOwner->GetHalfSize() + m_pOwner->GetSpaceHeightImg(), 0.0f);
}

void Walk::Draw()
{
	Math::Rectangle src = { 0,0,10,10 };
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &src);
}