#include "TitleScene.h"
#include "../Scene.h"
#include "../../utility/utility.h"

int Title::Update()
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

	return ChangeScene::no;
}

void Title::Draw()
{
}

void Title::Init()
{
}

void Title::Release()
{
}