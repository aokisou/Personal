#include "ResultScene.h"
#include "../../Scene.h"
#include "../../../Utility/utility.h"

#define ALPHANGRANGE 360	//α値のループ範囲
#define ALPHAMIN 0.3f		//α値の最小値
#define ALPHARANGE 0.7f		//α値の範囲
#define CONTINUEPOS -100.0f	//continueの座標
#define TITLEPOS -250.0f	//titleの座標
#define MAINPOS	200.0f		//メイン文字
#define	GAMEOVERWIDTH 615	//画像サイズ
#define	GAMEOVERHEIGHT 157	//画像サイズ
#define CLEARWIDTH 318		//画像サイズ
#define CLEARHEIGHT 109		//画像サイズ
#define TITLEWIDTH 277		//画像サイズ
#define TITLEHEIGHT 108		//画像サイズ
#define CONTINUEWIDTH 544	//画像サイズ
#define CONTINUEHEIGHT 109	//画像サイズ
#define NUMWIDTH 100		//画像サイズ
#define NUMHEIGHT 100		//画像サイズ
#define TIMEWIDTH 270		//画像サイズ
#define TIMEHEIGHT 108		//画像サイズ
#define MAXMOVEINTERVALSEC 3	//数字を動かす
#define NUMSTARTPOS 100		//左端の数字の位置

void ResultScene::Update()
{
	m_moveInteerval++;
	m_alphaAng += 5;
	if (m_alphaAng > ALPHANGRANGE)
	{
		m_alphaAng -= ALPHANGRANGE;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000 && !m_bClear)
	{
		m_posY = CONTINUEPOS;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_posY = TITLEPOS;
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (!(*m_pOwner->GetKeyFlg()))
		{
			if (m_posY == CONTINUEPOS)
			{
				m_pOwner->SetTrueKeyFlg();
				m_pOwner->SetTrueChangeScene();
				m_pOwner->ChangeGame();//こいつは最後
			}
			if (m_posY == TITLEPOS)
			{
				m_pOwner->SetTrueKeyFlg();
				m_pOwner->SetTrueChangeScene();
				m_pOwner->ChangeTitle();//こいつは最後
				return;
			}
		}
	}
	else { m_pOwner->SetFalseKeyFlg(); }

	m_backMat = Math::Matrix::CreateScale(Back::scale, Back::scale, 1.0f) * Math::Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);
	m_mat = Math::Matrix::CreateScale(SCREEN::scale, SCREEN::scale, 1.0f) * Math::Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);
	if (m_moveInteerval > *m_maxFps * MAXMOVEINTERVALSEC)
	{
		const int AddAngle = 5;
		m_angle[0] += AddAngle;
		if (m_angle[0] > 180) { m_angle[0] = 180; }
		m_timeMat[0] = Math::Matrix::CreateTranslation(NUMSTARTPOS, sin(DirectX::XMConvertToRadians(m_angle[0])) * 50, 0.0f);
		for (int i = 1; i < PlayTime::ptnum; i++)
		{
			if (m_angle[i - 1] > 90)
			{
				m_angle[i] += AddAngle;
				if (m_angle[i] > 180)
				{
					m_angle[i] = 180;
					if (i == PlayTime::os) 
					{
						m_moveInteerval = 0;
						ResetNumPos();
					}
				}
			}
			m_timeMat[i] = Math::Matrix::CreateTranslation(NUMSTARTPOS + i * 50, sin(DirectX::XMConvertToRadians(m_angle[i])) * 50, 0.0f);
		}
	}
}

void ResultScene::Draw(KdTexture* _pTex)
{
	Math::Rectangle src = { 0,0,Back::width,Back::height };
	Math::Color col = { 1,1,1,1 };
	if (!m_bClear) { col = { 1,0,0,1 }; }
	for (int i = 0; i < Back::num; i++)
	{
		SHADER.m_spriteShader.SetMatrix(m_backMat);
		SHADER.m_spriteShader.DrawTex(&m_backTex[i], 0, 0, &src, &col);
	}

	src = { 0,0,SCREEN::width,SCREEN::height };
	col = { 1,1,1,1 };
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(_pTex, 0, 0, &src, &col);
}

void ResultScene::DynamicDraw2D()
{
	Math::Rectangle src = { 0,0,0,0 };
	Math::Color col = { 1,1,1,1 };
	for (int i = 0; i < CharType::num; i++)
	{
		switch (i)
		{
		case CharType::Continue:
		{
			if (m_bClear) { continue; }
			src = { 0,0,CONTINUEWIDTH,CONTINUEHEIGHT };
			if (m_posY == CONTINUEPOS) { col = { 1.0f,1.0f,1.0f,abs(sin(DirectX::XMConvertToRadians((float)m_alphaAng))) * ALPHARANGE + ALPHAMIN }; }
			else { col = { 1, 1, 1, 1 }; }
			break;
		}
		case CharType::Title:
		{
			src = { 0,0,TITLEWIDTH,TITLEHEIGHT };
			if (m_posY == TITLEPOS) { col = { 1.0f,1.0f,1.0f,abs(sin(DirectX::XMConvertToRadians((float)m_alphaAng))) * ALPHARANGE + ALPHAMIN }; }
			else { col = { 1, 1, 1, 1 }; }
			break;
		}
		case CharType::Main:
		{
			col = { 1,1,1,1 };
			if (m_bClear)src = { 0,0,CLEARWIDTH,CLEARHEIGHT };
			if (!m_bClear)src = { 0,0,GAMEOVERWIDTH,GAMEOVERHEIGHT };
			break;
		}
		}
		SHADER.m_spriteShader.SetMatrix(m_charMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_charTex[i], 0, 0, &src, &col);
	}

	if (m_bClear)
	{
		src = { 0,0,NUMWIDTH,NUMHEIGHT };
		for (int i = 0; i < PlayTime::ptnum;i++)
		{
			SHADER.m_spriteShader.SetMatrix(m_timeMat[i]);
			SHADER.m_spriteShader.DrawTex(&m_timeTex[i], 0, 0, &src);
		}

		src = { 0,0,TIMEWIDTH,TIMEHEIGHT };
		SHADER.m_spriteShader.SetMatrix(m_clearTimeMat);
		SHADER.m_spriteShader.DrawTex(&m_clearTimeTex, 0, 0, &src);
	}
}

void ResultScene::Init(int _minuets, int _seconds)
{
	if (!m_bClear) { m_posY = CONTINUEPOS; }
	else { m_posY = TITLEPOS; }
	m_alphaAng = 0;

	for (int i = 0; i < Back::num; i++)
	{
		m_backTex[i].Load(m_backName[i]);
	}

	m_charTex[CharType::Continue].Load("Texture/Result/continue.png");
	m_charTex[CharType::Title].Load("Texture/Result/title.png");
	if (m_bClear) { m_charTex[CharType::Main].Load("Texture/Result/clear.png"); }
	else { m_charTex[CharType::Main].Load("Texture/Result/gameover.png"); }

	m_charMat[0] = Math::Matrix::CreateTranslation(0.0f, CONTINUEPOS, 0.0f);
	m_charMat[1] = Math::Matrix::CreateTranslation(0.0f, TITLEPOS, 0.0f);
	m_charMat[2] = Math::Matrix::CreateTranslation(0.0f, MAINPOS, 0.0f);

	if (m_bClear)
	{
		m_moveInteerval = 0;
		int tenm = 0, onem = 0, tens = 0, ones = 0;

		tenm = (int)_minuets / 10;
		onem = (int)_minuets % 10;
		tens = (int)_seconds / 10;
		ones = (int)_seconds % 10;

		m_timeTex[0].Load(m_numFileName[tenm]);
		m_timeTex[1].Load(m_numFileName[onem]);
		m_timeTex[2].Load("Texture/Result/minuet.png");
		m_timeTex[3].Load(m_numFileName[tens]);
		m_timeTex[4].Load(m_numFileName[ones]);
		ResetNumPos();

		m_clearTimeTex.Load("Texture/Result/time.png");
		m_clearTimeMat = Math::Matrix::CreateTranslation(-250, 0, 0);
	}
}

void ResultScene::ResetNumPos()
{
	for (int i = 0; i < PlayTime::ptnum; i++)
	{
		m_angle[i] = 0;
		m_timeMat[i] = Math::Matrix::CreateTranslation(NUMSTARTPOS + i * 50, 0.0f, 0.0f);
	}
}

void ResultScene::Release()
{
}
