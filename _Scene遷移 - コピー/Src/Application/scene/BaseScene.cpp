#include "BaseScene.h"
#include "../utility/utility.h"

int BaseScene::Update()
{
	return ChangeScene::no;
}

void BaseScene::Draw()
{
}

void BaseScene::Init()
{
}

void BaseScene::Release()
{
}

float BaseScene::GetHp()
{
	return 0.0f;
}
