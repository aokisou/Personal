#include "Walk.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/BaseEnemy.h"

void Walk::Update()
{
	Math::Vector2 _p = m_pOwner->GetPos();
	m_mat = Math::Matrix::CreateScale(1.0f,1.0f,1.0f) * Math::Matrix::CreateTranslation(_p.x, _p.y, 0.0f);
}

void Walk::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0);
}