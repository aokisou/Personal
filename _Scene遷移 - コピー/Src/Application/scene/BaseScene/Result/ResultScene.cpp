#include "ResultScene.h"
#include "../../Scene.h"
#include "../../../Utility/utility.h"

void ResultScene::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (!(*m_pOwner->GetKeyFlg()))
		{
			m_pOwner->SetTrueKeyFlg();
			m_pOwner->ChangeTitle();
			return;
		}
	}
	else { m_pOwner->SetFalseKeyFlg(); }

	m_mat = Math::Matrix::CreateScale(SCREEN::scale, SCREEN::scale, 1.0f) * Math::Matrix::CreateTranslation(0.0f, 320.0f, 0.0f);
}

void ResultScene::Draw(KdTexture* _pTex)
{
}

void ResultScene::DynamicDraw2D()
{
}

void ResultScene::Init()
{
}

void ResultScene::Release()
{
}