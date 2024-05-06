#include "TitleScene.h"
#include "../../../main.h"
#include "../../Scene.h"
#include "../../../Utility/utility.h"

#define STARTPOS -100.f		//���W
#define EXITPOS -250.f      //���W
#define ALPHANGRANGE 360	//���l�̃��[�v�͈�
#define ALPHAMIN 0.3f		//���l�̍ŏ��l
#define ALPHARANGE 0.7f		//���l�͈̔�
#define	TITLEWIDTH 848		//�摜�T�C�Y
#define	TITLEHEIGHT 109		//�摜�T�C�Y
#define STARTWIDTH 318		//�摜�T�C�Y
#define STARTHEIGHT 109		//�摜�T�C�Y
#define EXITWIDTH 246		//�摜�T�C�Y
#define EXITHEIGHT 108		//�摜�T�C�Y
#define ENTERWIDTH 30		//�摜�T�C�Y
#define ENTERHEIGHT 14		//�摜�T�C�Y
#define ENTERSCALE 3.0f		//�G���^�[�̊g�嗦
#define RIVER 3				//��̉摜�̔z��ԍ�

void TitleScene::Update()
{
	m_alphaAng += 5;
	if (m_alphaAng > ALPHANGRANGE)
	{
		m_alphaAng -= ALPHANGRANGE;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (!(*m_pOwner->GetKeyFlg()))
		{
			m_posY = STARTPOS;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		if (!(*m_pOwner->GetKeyFlg()))
		{
			m_posY = EXITPOS;
		}
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (!(*m_pOwner->GetKeyFlg()))
		{
			if (m_posY == STARTPOS)
			{
				m_pOwner->SetTrueKeyFlg();
				m_pOwner->SetTrueChangeScene();
				m_pOwner->ChangeGame();//�����͍Ō�
				return;
			}
			else
			{
				APP.End();
				return;
			}
		}
	}
	else { m_pOwner->SetFalseKeyFlg(); }

	m_backPos[RIVER].x -= 0.1f;
	m_2ndBackPos[RIVER].x = m_backPos[RIVER].x + Back::width * Back::scale;
	if (m_backPos[RIVER].x < -Back::width * Back::scale)m_backPos[RIVER].x = 0;
	m_backMat[RIVER] = Math::Matrix::CreateScale(Back::scale, Back::scale, 1.0f) * Math::Matrix::CreateTranslation(m_backPos[RIVER].x, m_backPos[RIVER].y, 0.0f);
	m_2ndBackMat[RIVER] = Math::Matrix::CreateScale(Back::scale, Back::scale, 1.0f) * Math::Matrix::CreateTranslation(m_2ndBackPos[RIVER].x, m_2ndBackPos[RIVER].y, 0.0f);
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
	Math::Color col = { 1.0f,1.0f,1.0f,1.0f };
	if (m_posY == STARTPOS) { col = { 1.0f,1.0f,1.0f,abs(sin(DirectX::XMConvertToRadians((float)m_alphaAng))) * ALPHARANGE + ALPHAMIN }; }
	SHADER.m_spriteShader.SetMatrix(m_startMat);
	SHADER.m_spriteShader.DrawTex(&m_startTex, 0, 0, &src,&col);

	src = { 0,0,EXITWIDTH,EXITHEIGHT };
	col = { 1.0f,1.0f,1.0f,1.0f };
	if (m_posY == EXITPOS) { col = { 1.0f,1.0f,1.0f,abs(sin(DirectX::XMConvertToRadians((float)m_alphaAng))) * ALPHARANGE + ALPHAMIN }; }
	SHADER.m_spriteShader.SetMatrix(m_exitMat);
	SHADER.m_spriteShader.DrawTex(&m_exitTex, 0, 0, &src, &col);

	src = { 0,0,TITLEWIDTH,TITLEHEIGHT };
	SHADER.m_spriteShader.SetMatrix(m_titleMat);
	SHADER.m_spriteShader.DrawTex(&m_titleTex, 0, 0, &src);

	src = { 0,0,ENTERWIDTH,ENTERHEIGHT };
	SHADER.m_spriteShader.SetMatrix(m_enterMat);
	SHADER.m_spriteShader.DrawTex(&m_enterTex, 0, 0, &src);
}

void TitleScene::DynamicDraw2D()
{
}

void TitleScene::Init()
{
	m_posY = STARTPOS;
	m_alphaAng = 0;
	for (int i = 0; i < Back::num; i++)
	{
		m_backTex[i].Load(m_backName[i]);
		m_backPos[i] = {};
		m_2ndBackPos[i] = { m_backPos[i].x + Back::width * Back::scale,0.0f };
		m_backMat[i] = Math::Matrix::CreateScale(Back::scale) * Math::Matrix::CreateTranslation(m_backPos[i].x, m_backPos[i].y, 0.0f);
		m_2ndBackMat[i] = Math::Matrix::CreateScale(Back::scale) * Math::Matrix::CreateTranslation(m_2ndBackPos[i].x, m_2ndBackPos[i].y, 0.0f);
	}
	m_startTex.Load("Texture/Title/start.png");
	m_titleTex.Load("Texture/Title/title.png");
	m_exitTex.Load("Texture/Title/exit.png");

	m_enterMat = Math::Matrix::CreateScale(ENTERSCALE,ENTERSCALE,1.0f) * Math::Matrix::CreateTranslation(SCREEN::width / HALF - ENTERWIDTH * ENTERSCALE / HALF, -SCREEN::height / HALF + ENTERHEIGHT * ENTERSCALE / HALF, 0.0f);
	m_enterTex.Load("Texture/UI/enter.png");

	m_titleMat = Math::Matrix::CreateTranslation(0.0f, 200.0f, 0.0f);
	m_startMat = Math::Matrix::CreateScale(1.f) * Math::Matrix::CreateTranslation(0.0f, STARTPOS, 0.0f);
	m_exitMat = Math::Matrix::CreateScale(1.f) * Math::Matrix::CreateTranslation(0.0f, EXITPOS, 0.0f);
	m_mat = Math::Matrix::CreateScale(Back::scale) * Math::Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);
}

void TitleScene::Release()
{
}