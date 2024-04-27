#pragma once

class BaseScene;

class Scene
{
private:
	std::shared_ptr<BaseScene> m_pNowScene = nullptr;
	std::shared_ptr<BaseScene> m_pNextScene = nullptr;//ˆê•Û‘¶
	
	bool m_bkeyFlg = false;

	bool m_bChangeScene = false;
	int m_sceneChageAlpha = 0;
	Math::Matrix m_sceneChangeMat = Math::Matrix::Identity;

	KdTexture m_tmpTex;
	KdTexture m_sceneChangeTex;

public:

	// ‰Šúİ’è
	void Init();

	// ‰ğ•ú
	void Release();

	// XVˆ—
	void Update();

	// •`‰æˆ—
	void Draw2D();

	// GUIˆ—
	void ImGuiUpdate();

	void UpdateChangeScene();
	void DrawChangeScene();

	void SetTrueChangeScene() { m_bChangeScene = true; }

	void ChangeTitle();
	void ChangeGame();
	void ChangeResult(bool _b);

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
