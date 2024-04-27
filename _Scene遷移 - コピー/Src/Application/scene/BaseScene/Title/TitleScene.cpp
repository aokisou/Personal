#include "TitleScene.h"
#include "../../Scene.h"
#include "../../../Utility/utility.h"

#define BackNum 5			//画像数
#define AlphaAngRange 360	//α値のループ範囲
#define AlphaMin 0.3f		//α値の最小値
#define AlphaRange 0.7f		//α値の範囲

void TitleScene::Update()
{
	m_alphaAng += 5;
	if (m_alphaAng > AlphaAngRange)
	{
		m_alphaAng -= AlphaAngRange;
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (!(*m_pOwner->GetKeyFlg()))
		{
			m_pOwner->SetTrueKeyFlg();
			m_pOwner->SetTrueChangeScene();
			m_pOwner->ChangeGame();//こいつは最後
			return;
		}
	}
	else { m_pOwner->SetFalseKeyFlg(); }

	m_startMat = Math::Matrix::CreateTranslation(0.0f, -160.0f, 0.0f);
	m_mat = Math::Matrix::CreateScale(Back::Scale, Back::Scale, 1.0f) * Math::Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);
}

void TitleScene::Draw(KdTexture* _pTex)
{
	Math::Rectangle src = { 0,0,Back::Width,Back::Height };
	for (int i = 0; i < BackNum; i++)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(&m_backTex[i], 0, 0, &src);
	}

	src = { 0,0,210,80 };
	Math::Color col = { 1.0f,1.0f,1.0f,abs(sin(DirectX::XMConvertToRadians((float)m_alphaAng))) * AlphaRange + AlphaMin };
	SHADER.m_spriteShader.SetMatrix(m_startMat);
	SHADER.m_spriteShader.DrawTex(&m_startTex, 0, 0, &src,&col);
}

void TitleScene::DynamicDraw2D()
{
}

void TitleScene::Init()
{
	m_alphaAng = 0;
	for (int i = 0; i < Back::Num; i++)
	{
		m_backTex[i].Load(m_backName[i]);
	}
	m_startTex.Load("Texture/Title/start.png");
}

void TitleScene::Release()
{
}