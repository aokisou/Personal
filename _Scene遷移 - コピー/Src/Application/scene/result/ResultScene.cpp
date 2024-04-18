#include "ResultScene.h"
#include "../Scene.h"
#include "../../utility/utility.h"

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

void ResultScene::Init()
{
}

void ResultScene::Release()
{
}