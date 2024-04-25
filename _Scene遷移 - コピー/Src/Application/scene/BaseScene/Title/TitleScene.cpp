#include "TitleScene.h"
#include "../../Scene.h"
#include "../../../Utility/utility.h"

int TitleScene::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (!(*m_pOwner->GetKeyFlg()))
		{
			m_pOwner->SetTrueKeyFlg();
			return ChangeScene::game;
		}
	}
	else { m_pOwner->SetFalseKeyFlg(); }

	m_mat = Math::Matrix::CreateScale(1.05, 1.05, 1) * Math::Matrix::CreateTranslation(0, 0, 0);

	return ChangeScene::no;
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