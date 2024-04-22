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

	return ChangeScene::no;
}

void TitleScene::Draw()
{
}

void TitleScene::Init()
{
	m_titleTex.Load("Texture/enemy.png");
}

void TitleScene::Release()
{
}