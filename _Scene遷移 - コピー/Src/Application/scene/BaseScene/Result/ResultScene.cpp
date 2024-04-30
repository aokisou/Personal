#include "ResultScene.h"
#include "../../Scene.h"
#include "../../../Utility/utility.h"

#define BackNum 5			//画像数
#define AlphaAngRange 360	//α値のループ範囲
#define AlphaMin 0.3f		//α値の最小値
#define AlphaRange 0.7f		//α値の範囲
#define ContinuePos -100.0f	//continueの座標
#define TitlePos -200.0f	//titleの座標
#define MainPos	200.0f		//メイン文字
#define ImgHeight 80		//画像幅
#define ImgWidthShort 210	//画像幅
#define ImgWidthMiddle 300	//画像幅
#define ImgWidthLong 340	//画像幅

void ResultScene::Update()
{
	m_alphaAng += 5;
	if (m_alphaAng > AlphaAngRange)
	{
		m_alphaAng -= AlphaAngRange;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_posY = ContinuePos;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_posY = TitlePos;
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (!(*m_pOwner->GetKeyFlg()))
		{
			if (m_posY == ContinuePos)
			{
				m_pOwner->SetTrueKeyFlg();
				m_pOwner->SetTrueChangeScene();
				m_pOwner->ChangeGame();//こいつは最後
			}
			if (m_posY == TitlePos)
			{
				m_pOwner->SetTrueKeyFlg();
				m_pOwner->SetTrueChangeScene();
				m_pOwner->ChangeTitle();//こいつは最後
				return;
			}
		}
	}
	else { m_pOwner->SetFalseKeyFlg(); }

	m_charMat[0] = Math::Matrix::CreateTranslation(0.0f, ContinuePos, 0.0f);
	m_charMat[1] = Math::Matrix::CreateTranslation(0.0f, TitlePos, 0.0f);
	m_charMat[2] = Math::Matrix::CreateTranslation(0.0f, MainPos, 0.0f);
	m_mat = Math::Matrix::CreateScale(Back::Scale, Back::Scale, 1.0f) * Math::Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);
}

void ResultScene::Draw(KdTexture* _pTex)
{
	Math::Rectangle src = { 0,0,Back::Width,Back::Height };
	Math::Color col = { 1,1,1,1 };
	if (!m_bClear) { col = { 1,0,0,1 }; }
	for (int i = 0; i < BackNum; i++)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(&m_backTex[i], 0, 0, &src, &col);
	}

	for (int i = 0; i < CharType::num; i++)
	{
		if (i == CharType::Continue)
		{ 
			src = { 0,0,ImgWidthMiddle,ImgHeight };
			if (m_posY == ContinuePos) { col = { 1.0f,1.0f,1.0f,abs(sin(DirectX::XMConvertToRadians((float)m_alphaAng))) * AlphaRange + AlphaMin }; }
			else { col = { 1, 1, 1, 1 }; }
		}
		if (i == CharType::Title)
		{
			src = { 0,0,ImgWidthShort,ImgHeight };
			if (m_posY == TitlePos) { col = { 1.0f,1.0f,1.0f,abs(sin(DirectX::XMConvertToRadians((float)m_alphaAng))) * AlphaRange + AlphaMin }; }
			else { col = { 1, 1, 1, 1 }; }
		}
		if(i == CharType::Main)
		{
			col = { 1,1,1,1 };
			if(m_bClear)src = { 0,0,ImgWidthShort,ImgHeight };
			if(!m_bClear)src = { 0,0,ImgWidthLong,ImgHeight };
		}
		SHADER.m_spriteShader.SetMatrix(m_charMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_charTex[i], 0, 0, &src, &col);
	}
}

void ResultScene::DynamicDraw2D()
{
}

void ResultScene::Init()
{
	m_posY = ContinuePos;
	m_alphaAng = 0;

	for (int i = 0; i < Back::Num; i++)
	{
		m_backTex[i].Load(m_backName[i]);
	}
	m_charTex[CharType::Continue].Load("Texture/Result/continue.png");
	m_charTex[CharType::Title].Load("Texture/Result/title.png");
	if (m_bClear) { m_charTex[CharType::Main].Load("Texture/Result/clear.png"); }
	else{ m_charTex[CharType::Main].Load("Texture/Result/gameover.png"); }
}

void ResultScene::Release()
{
}