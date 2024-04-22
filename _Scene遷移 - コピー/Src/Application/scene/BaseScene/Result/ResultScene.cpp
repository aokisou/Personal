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

	return ChangeScene::no;
}

void ResultScene::Draw()
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