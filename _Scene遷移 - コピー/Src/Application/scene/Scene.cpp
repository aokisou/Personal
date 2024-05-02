#include "../main.h"
#include "Scene.h"
#include "BaseScene/BaseScene.h"
#include "BaseScene/Title/TitleScene.h"
#include "BaseScene/Game/GameScene.h"
#include "BaseScene/Result/ResultScene.h"
#include "../Utility/Utility.h"

#define OneTimeChangeScene 180

void Scene::Draw2D()
{
	m_tmpTex.ClearRenerTarget(Math::Color{ 0,0,0,0 });
	m_tmpTex.SetRenderTarget();
	m_pNowScene->DynamicDraw2D();

	D3D.SetBackBuffer();
	m_pNowScene->Draw(&m_tmpTex);
	DrawChangeScene();
}

void Scene::Update()
{
	if (m_bChangeScene) { UpdateChangeScene(); }
	else { m_pNowScene->Update(); }
}

void Scene::DrawChangeScene()
{
	Math::Rectangle src = { 0,0,1280,720 };
	Math::Color col = { 1,1,1,abs(sin(DirectX::XMConvertToRadians((float)m_sceneChageAlpha)))};
	SHADER.m_spriteShader.SetMatrix(m_sceneChangeMat);
	SHADER.m_spriteShader.DrawTex(&m_sceneChangeTex, 0, 0, &src, &col);
}

void Scene::UpdateChangeScene()
{
	m_sceneChageAlpha += 5;
	if (m_sceneChageAlpha == OneTimeChangeScene / Half)
	{
		if (m_pNextScene != nullptr)
		{
			m_pNowScene = m_pNextScene;
			m_pNextScene = nullptr;
		}
		else
		{
			m_pNowScene->Reset();
		}
	}

	if (m_sceneChageAlpha > OneTimeChangeScene)
	{
		m_sceneChageAlpha -= OneTimeChangeScene;
		m_bChangeScene = false;
	}
	m_sceneChangeMat = Math::Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);
}

void Scene::Init()
{
	srand(timeGetTime());
	bool bLoad;
	m_bkeyFlg = false;

	bLoad = m_tmpTex.CreateRenderTarget(SCREEN::width, SCREEN::height);
	_ASSERT_EXPR(bLoad, "ターゲット読み取りエラー");
	bLoad = m_sceneChangeTex.Load("Texture/Screen/white.png");
	_ASSERT_EXPR(bLoad, "画面遷移画像読み取りエラー");

	ChangeTitle();
	m_pNowScene = m_pNextScene;
	m_pNextScene = nullptr;

	m_sceneChageAlpha = 0;
	m_bChangeScene = false;
}

void Scene::Release()
{

}

void Scene::ImGuiUpdate()
{
	return;

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
	m_pNextScene = std::make_shared<TitleScene>(&APP.m_maxFps);
	ChangePreUpdate();
}

void Scene::ChangeGame()
{
	m_pNextScene = std::make_shared<GameScene>(&APP.m_maxFps);
	ChangePreUpdate();
}

void Scene::ChangeResult(bool _b)
{
	m_pNextScene = std::make_shared<ResultScene>(&APP.m_maxFps,_b);
	ChangePreUpdate();
}

void Scene::ChangePreUpdate()
{
	m_pNextScene->SetOwner(this);
	m_pNextScene->Update();
	m_bChangeScene = true;
}