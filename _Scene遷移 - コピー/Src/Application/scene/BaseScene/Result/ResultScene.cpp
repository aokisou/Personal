#include "ResultScene.h"
#include "../../Scene.h"
#include "../../../Utility/utility.h"

#define BackNum 5			//�摜��
#define AlphaAngRange 360	//���l�̃��[�v�͈�
#define AlphaMin 0.3f		//���l�̍ŏ��l
#define AlphaRange 0.7f		//���l�͈̔�
#define ContinuePos -100.0f	//continue�̍��W
#define TitlePos -250.0f	//title�̍��W
#define MainPos	200.0f		//���C������
#define	GAMEOVERWIDTH 615	//�摜�T�C�Y
#define	GAMEOVERHEIGHT 157	//�摜�T�C�Y
#define CLEARWIDTH 318		//�摜�T�C�Y
#define CLEARHEIGHT 109		//�摜�T�C�Y
#define TITLEWIDTH 277		//�摜�T�C�Y
#define TITLEHEIGHT 108		//�摜�T�C�Y
#define CONTINUEWIDTH 544	//�摜�T�C�Y
#define CONTINUEHEIGHT 109	//�摜�T�C�Y

void ResultScene::Update()
{
	m_alphaAng += 5;
	if (m_alphaAng > AlphaAngRange)
	{
		m_alphaAng -= AlphaAngRange;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000 && !m_bClear)
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
				m_pOwner->ChangeGame();//�����͍Ō�
			}
			if (m_posY == TitlePos)
			{
				m_pOwner->SetTrueKeyFlg();
				m_pOwner->SetTrueChangeScene();
				m_pOwner->ChangeTitle();//�����͍Ō�
				return;
			}
		}
	}
	else { m_pOwner->SetFalseKeyFlg(); }

	m_backMat = Math::Matrix::CreateScale(Back::scale, Back::scale, 1.0f) * Math::Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);
	m_mat = Math::Matrix::CreateScale(SCREEN::scale, SCREEN::scale, 1.0f) * Math::Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);
}

void ResultScene::Draw(KdTexture* _pTex)
{
	Math::Rectangle src = { 0,0,Back::width,Back::height };
	Math::Color col = { 1,1,1,1 };
	if (!m_bClear) { col = { 1,0,0,1 }; }
	for (int i = 0; i < BackNum; i++)
	{
		SHADER.m_spriteShader.SetMatrix(m_backMat);
		SHADER.m_spriteShader.DrawTex(&m_backTex[i], 0, 0, &src, &col);
	}

	src = { 0,0,1280,720 };
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
			if (m_posY == ContinuePos) { col = { 1.0f,1.0f,1.0f,abs(sin(DirectX::XMConvertToRadians((float)m_alphaAng))) * AlphaRange + AlphaMin }; }
			else { col = { 1, 1, 1, 1 }; }
			break;
		}
		case CharType::Title:
		{
			src = { 0,0,TITLEWIDTH,TITLEHEIGHT };
			if (m_posY == TitlePos) { col = { 1.0f,1.0f,1.0f,abs(sin(DirectX::XMConvertToRadians((float)m_alphaAng))) * AlphaRange + AlphaMin }; }
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
}

void ResultScene::Init()
{
	if (!m_bClear) { m_posY = ContinuePos; }
	else { m_posY = TitlePos; }
	m_alphaAng = 0;

	for (int i = 0; i < Back::num; i++)
	{
		m_backTex[i].Load(m_backName[i]);
	}
	m_charTex[CharType::Continue].Load("Texture/Result/continue.png");
	m_charTex[CharType::Title].Load("Texture/Result/title.png");
	if (m_bClear) { m_charTex[CharType::Main].Load("Texture/Result/clear2.png"); }
	else{ m_charTex[CharType::Main].Load("Texture/Result/gameover.png"); }

	m_charMat[0] = Math::Matrix::CreateTranslation(0.0f, ContinuePos, 0.0f);
	m_charMat[1] = Math::Matrix::CreateTranslation(0.0f, TitlePos, 0.0f);
	m_charMat[2] = Math::Matrix::CreateTranslation(0.0f, MainPos, 0.0f);
}

void ResultScene::Release()
{
}