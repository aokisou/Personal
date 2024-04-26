#include "TitleScene.h"
#include "../../Scene.h"
#include "../../../Utility/utility.h"

void TitleScene::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (!(*m_pOwner->GetKeyFlg()))
		{
			m_pOwner->SetTrueKeyFlg();
			m_pOwner->ChangeGame();
			return;
		}
	}
	else { m_pOwner->SetFalseKeyFlg(); }

	m_mat = Math::Matrix::CreateScale(SCREEN::scale, SCREEN::scale, 1.0f) * Math::Matrix::CreateTranslation(0.0f, 320.0f, 0.0f);
}

void TitleScene::Draw(KdTexture* _pTex)
{
}

void TitleScene::DynamicDraw2D()
{
}

void TitleScene::Init()
{
	m_titleTex.Load("Texture/enemy.png");
}

void TitleScene::Release()
{
}