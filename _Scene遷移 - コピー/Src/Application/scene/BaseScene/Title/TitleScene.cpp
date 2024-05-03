#include "TitleScene.h"
#include "../../Scene.h"
#include "../../../Utility/utility.h"

#define ALPHANGRANGE 360	//α値のループ範囲
#define ALPHAMIN 0.3f		//α値の最小値
#define ALPHARANGE 0.7f		//α値の範囲
#define	TITLEWIDTH 848		//画像サイズ
#define	TITLEHEIGHT 109		//画像サイズ
#define STARTWIDTH 318		//画像サイズ
#define STARTHEIGHT 109		//画像サイズ
#define RIVER 3				//川の画像の配列番号

void TitleScene::Update()
{
	m_alphaAng += 5;
	if (m_alphaAng > ALPHANGRANGE)
	{
		m_alphaAng -= ALPHANGRANGE;
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

	m_titleMat = Math::Matrix::CreateTranslation(0.0f, 200.0f, 0.0f);
	m_startMat = Math::Matrix::CreateTranslation(0.0f, -160.0f, 0.0f);
	m_mat = Math::Matrix::CreateScale(Back::scale, Back::scale, 1.0f) * Math::Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);

	for (int i = RIVER; i < Back::num; i++)
	{
		m_backPos[i].x--;
		m_2ndBackPos[i].x = m_backPos[i].x + Back::width * Back::scale;
		if (m_backPos[i].x < -Back::width * Back::scale)m_backPos[i].x = 0;
		m_backMat[i] = Math::Matrix::CreateScale(Back::scale, Back::scale, 1.0f) * Math::Matrix::CreateTranslation(m_backPos[i].x, m_backPos[i].y, 0.0f);
		m_2ndBackMat[i] = Math::Matrix::CreateScale(Back::scale, Back::scale, 1.0f) * Math::Matrix::CreateTranslation(m_2ndBackPos[i].x, m_2ndBackPos[i].y, 0.0f);
	}
}

void TitleScene::Draw(KdTexture* _pTex)
{
	Math::Rectangle src = { 0,0,Back::width,Back::height };
	for (int i = 0; i < Back::num; i++)
	{
		SHADER.m_spriteShader.SetMatrix(m_backMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_backTex[i], 0, 0, &src);
		SHADER.m_spriteShader.SetMatrix(m_2ndBackMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_backTex[i], 0, 0, &src);
	}

	src = { 0,0,STARTWIDTH,STARTHEIGHT };
	Math::Color col = { 1.0f,1.0f,1.0f,abs(sin(DirectX::XMConvertToRadians((float)m_alphaAng))) * ALPHARANGE + ALPHAMIN };
	SHADER.m_spriteShader.SetMatrix(m_startMat);
	SHADER.m_spriteShader.DrawTex(&m_startTex, 0, 0, &src,&col);

	src = { 0,0,TITLEWIDTH,TITLEHEIGHT };
	SHADER.m_spriteShader.SetMatrix(m_titleMat);
	SHADER.m_spriteShader.DrawTex(&m_titleTex, 0, 0, &src);
}

void TitleScene::DynamicDraw2D()
{
}

void TitleScene::Init()
{
	m_alphaAng = 0;
	for (int i = 0; i < Back::num; i++)
	{
		m_backTex[i].Load(m_backName[i]);
	}
	m_startTex.Load("Texture/Title/start.png");
	m_titleTex.Load("Texture/Title/title.png");

	for (int i = 0; i < Back::num; i++)
	{
		m_backPos[i] = {};
		m_2ndBackPos[i] = { m_backPos[i].x + Back::width * Back::scale,0.0f };
		m_backMat[i] = Math::Matrix::CreateScale(Back::scale, Back::scale, 1.0f) * Math::Matrix::CreateTranslation(m_backPos[i].x, m_backPos[i].y, 0.0f);
		m_2ndBackMat[i] = Math::Matrix::CreateScale(Back::scale, Back::scale, 1.0f) * Math::Matrix::CreateTranslation(m_2ndBackPos[i].x, m_2ndBackPos[i].y, 0.0f);
	}
}

void TitleScene::Release()
{
}