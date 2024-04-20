#include "../main.h"
#include "Scene.h"
#include "BaseScene.h"
#include "title/TitleScene.h"
#include "game/GameScene.h"
#include "result/ResultScene.h"
#include "../utility/utility.h"

void Scene::Draw2D()
{
	m_nowScene->Draw();
}

void Scene::Update()
{
	switch (m_nowScene->Update())
	{
	case ChangeScene::title:
	{
		ChangeTitle();
		break;
	}
	case ChangeScene::game:
	{
		ChangeGame();
		break;
	}
	case ChangeScene::result:
	{
		ChangeResult();
		break;
	}
	default:
		break;
	}
}

void Scene::Init()
{
	bool bLoad;
	m_bkeyFlg = false;

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
		ImGui::Text("%f", m_nowScene->GetHp());
	}
	ImGui::End();
}

void Scene::ChangeTitle()
{
	delete m_nowScene;
	m_nowScene = new TitleScene(&APP.m_maxFps);
	m_nowScene->SetOwner(this);
}

void Scene::ChangeGame()
{
	delete m_nowScene;
	m_nowScene = new GameScene(&APP.m_maxFps);
	m_nowScene->SetOwner(this);
}

void Scene::ChangeResult()
{
	delete m_nowScene;
	m_nowScene = new ResultScene(&APP.m_maxFps);
	m_nowScene->SetOwner(this);
}