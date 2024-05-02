#pragma once

class BaseScene;

class Scene
{
private:
	std::shared_ptr<BaseScene> m_pNowScene = nullptr;
	std::shared_ptr<BaseScene> m_pNextScene = nullptr;//一時保存
	
	bool m_bkeyFlg = false;

	bool m_bChangeScene = false;
	int m_sceneChageAlpha = 0;
	Math::Matrix m_sceneChangeMat = Math::Matrix::Identity;

	KdTexture m_tmpTex;
	KdTexture m_sceneChangeTex;

public:

	// 初期設定
	void Init();

	// 解放
	void Release();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

	// GUI処理
	void ImGuiUpdate();

	void UpdateChangeScene();
	void DrawChangeScene();

	void SetTrueChangeScene() { m_bChangeScene = true; }
	
	void ChangeTitle();
	void ChangeGame();
	void ChangeResult(bool _b);

	void ChangePreUpdate();//更新前の行列作成などのため一回Update

	bool* GetKeyFlg() { return &m_bkeyFlg; }
	void SetTrueKeyFlg() { m_bkeyFlg = true; }
	void SetFalseKeyFlg() { m_bkeyFlg = false; }

private:

	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
