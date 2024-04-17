#pragma once

class BaseScene;

class Scene
{
private:
	BaseScene* m_nowScene;

	bool m_bkeyFlg;

	KdTexture m_playertex;
	KdTexture m_enemytex;

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

	void ChangeTitle();
	void ChangeGame();
	void ChangeResult();

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
