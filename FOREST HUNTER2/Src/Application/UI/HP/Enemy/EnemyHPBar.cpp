#include "EnemyHPBar.h"
#include "../../../Utility/Utility.h"

#define ImgWidth 256
#define ImgHeight 48
#define Scale 0.2f

void EnemyHPBar::Update(float* _hp, int _maxHP, Math::Vector2 _pos)
{
	m_hp = *_hp;

	if (m_hp < 0)
	{
		m_hp = 0;
	}

	m_gaugeMat = Math::Matrix::CreateScale(Scale, Scale, 1.0f) *
		Math::Matrix::CreateTranslation(_pos.x, _pos.y, 0);
	m_barMat = Math::Matrix::CreateScale(Scale, Scale, 1.0f) *
		Math::Matrix::CreateTranslation(_pos.x - (ImgWidth * Scale - (m_hp * (ImgWidth * Scale / _maxHP))) / HALF, _pos.y, 0.0f);
}

void EnemyHPBar::Draw(int _maxHP)
{
	Math::Rectangle src = { 0,0,ImgWidth,ImgHeight };
	SHADER.m_spriteShader.SetMatrix(m_gaugeMat);
	SHADER.m_spriteShader.DrawTex(m_pGaugeTex, 0, 0, &src);
	src = { 0,0,(long)(m_hp * ((float)ImgWidth / _maxHP)),ImgHeight };
	SHADER.m_spriteShader.SetMatrix(m_barMat);
	SHADER.m_spriteShader.DrawTex(m_pBarTex, 0, 0, &src);
}

void EnemyHPBar::Init(KdTexture* _gaugeTex, KdTexture* _barTex)
{
	m_pGaugeTex = _gaugeTex;
	m_pBarTex = _barTex;
}

void EnemyHPBar::Release()
{
}
