#pragma once

class BaseScene;

class Scene
{
private:
	std::shared_ptr<BaseScene> m_pNowScene = nullptr;
	
	bool m_bkeyFlg = false;

	KdTexture m_tmpTex;

public:

	// 初期設定
	void Init();

	// 解放
	void Release();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();
	void DynamicDraw2D();

	// GUI処理
	void ImGuiUpdate();

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
