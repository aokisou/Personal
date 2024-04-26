#include "../main.h"
#include "Scene.h"
#include "BaseScene/BaseScene.h"
#include "BaseScene/Title/TitleScene.h"
#include "BaseScene/Game/GameScene.h"
#include "BaseScene/Result/ResultScene.h"
#include "../Utility/Utility.h"

void Scene::Draw2D()
{
	m_tmpTex.ClearRenerTarget(Math::Color{ 0,0,0,0 });
	m_tmpTex.SetRenderTarget();

	m_pNowScene->DynamicDraw2D();

	D3D.SetBackBuffer();
	m_pNowScene->Draw(&m_tmpTex);
}

void Scene::Update()
{
	m_pNowScene->Update();
}

void Scene::Init()
{
	bool bLoad;
	m_bkeyFlg = false;

	bLoad = m_tmpTex.CreateRenderTarget(SCREEN::width, SCREEN::height);
	_ASSERT_EXPR(bLoad, "ターゲット読み取りエラー");

	ChangeTitle();
}

void Scene::Release()
{
}

void Scene::ImGuiUpdate()
{
	//return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}

void Scene::ChangeTitle()
{
	m_pNowScene = std::make_shared<TitleScene>(&APP.m_maxFps);
	m_pNowScene->SetOwner(this);
	m_pNowScene->Update();
}

void Scene::ChangeGame()
{
	m_pNowScene = std::make_shared<GameScene>(&APP.m_maxFps);
	m_pNowScene->SetOwner(this);
	m_pNowScene->Update();
}

void Scene::ChangeResult(bool _b)
{
	m_pNowScene = std::make_shared<ResultScene>(&APP.m_maxFps,_b);
	m_pNowScene->SetOwner(this);
	m_pNowScene->Update();
}