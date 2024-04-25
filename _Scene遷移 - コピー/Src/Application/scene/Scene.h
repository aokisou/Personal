#pragma once

class BaseScene;

class Scene
{
private:
	std::shared_ptr<BaseScene> m_pNowScene = nullptr;
	
	bool m_bkeyFlg = false;

	KdTexture m_tmpTex;

public:

	// �����ݒ�
	void Init();

	// ���
	void Release();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw2D();
	void DynamicDraw2D();

	// GUI����
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
