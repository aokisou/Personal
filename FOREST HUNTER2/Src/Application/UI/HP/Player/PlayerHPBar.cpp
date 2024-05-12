#include "PlayerHPBar.h"
#include "../../../Utility/Utility.h"

#define ImgWidth 256
#define ImgHeight 48
#define Middle 0.6
#define Low 0.3

void PlayerHPBar::Update(int* _hp, int _maxHP)
{
	if (m_hp == (*_hp))return;
	m_hp = *_hp;
	
	m_gaugeMat = Math::Matrix::CreateTranslation(-SCREEN::width / HALF + ImgWidth / HALF, SCREEN::height / HALF - ImgHeight / HALF, 0.0f);
	m_barMat = Math::Matrix::CreateTranslation(-SCREEN::width / HALF + ImgWidth / HALF - (ImgWidth - (m_hp * ((float)ImgWidth / _maxHP))) / HALF,
		SCREEN::height / HALF - ImgHeight / HALF, 0.0f);
}

void PlayerHPBar::Draw(int _maxHP)
{
	Math::Rectangle src = { 0,0,ImgWidth,ImgHeight};
	SHADER.m_spriteShader.SetMatrix(m_gaugeMat);
	SHADER.m_spriteShader.DrawTex(&m_gaugeTex, 0, 0, &src);

	Math::Color col = { 0,1,0,1 };
	if (m_hp < _maxHP * Middle) { col = { 1,1,0,1 }; }
	if (m_hp < _maxHP * Low) { col = { 1,0,0,1 }; }
	src = { 0,0,(long)(m_hp * ((float)ImgWidth / _maxHP)),ImgHeight };
	SHADER.m_spriteShader.SetMatrix(m_barMat);
	SHADER.m_spriteShader.DrawTex(&m_barTex, 0, 0, &src,&col);
}

void PlayerHPBar::Init()
{
	m_gaugeTex.Load("Texture/UI/bg.png");
	m_barTex.Load("Texture/UI/base.png");
}

void PlayerHPBar::Release()
{
}
