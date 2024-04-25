#include "ResultScene.h"
#include "../../Scene.h"
#include "../../../Utility/utility.h"

int ResultScene::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (!(*m_pOwner->GetKeyFlg()))
		{
			m_pOwner->SetTrueKeyFlg();
			return ChangeScene::title;
		}
	}
	else { m_pOwner->SetFalseKeyFlg(); }

	m_mat = Math::Matrix::CreateScale(1.05, 1.05, 1) * Math::Matrix::CreateTranslation(0, 0, 0);

	return ChangeScene::no;
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