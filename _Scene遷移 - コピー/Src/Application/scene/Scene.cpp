#include "../main.h"
#include "Scene.h"
#include "BaseScene/BaseScene.h"
#include "BaseScene/Title/TitleScene.h"
#include "BaseScene/Game/GameScene.h"
#include "BaseScene/Result/ResultScene.h"
#include "../Utility/Utility.h"

void Scene::Draw2D()
{
	D3D.SetBackBuffer();
	m_pNowScene->Draw();
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tmpTex, 0, 0, &Math::Rectangle(0, 0, SCREEN::width, SCREEN::width));
}

void Scene::DynamicDraw2D()
{
	m_tmpTex.ClearRenerTarget(Math::Color{ 0,0,0,0 });
	m_tmpTex.SetRenderTarget();

	m_pNowScene->DynamicDraw2D();
}

void Scene::Update()
{
	switch (m_pNowScene->Update())
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

	m_mat = Math::Matrix::CreateTranslation(0, -320, 0);
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
	delete m_pNowScene;
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
		//ImGui::Text("%f", m_nowScene->GetHp());
	}
	ImGui::End();
}

void Scene::ChangeTitle()
{
	delete m_pNowScene;
	m_pNowScene = new TitleScene(&APP.m_maxFps);
	m_pNowScene->SetOwner(this);
	m_pNowScene->Update();
}

void Scene::ChangeGame()
{
	delete m_pNowScene;
	m_pNowScene = new GameScene(&APP.m_maxFps);
	m_pNowScene->SetOwner(this);
	m_pNowScene->Update();
}

void Scene::ChangeResult()
{
	delete m_pNowScene;
	m_pNowScene = new ResultScene(&APP.m_maxFps);
	m_pNowScene->SetOwner(this);
	m_pNowScene->Update();
}