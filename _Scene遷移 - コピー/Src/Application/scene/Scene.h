#pragma once

class BaseScene;

class Scene
{
private:
	std::shared_ptr<BaseScene> m_pNowScene = nullptr;
	std::shared_ptr<BaseScene> m_pNextScene = nullptr;//�ꎞ�ۑ�
	
	bool m_bkeyFlg = false;

	bool m_bChangeScene = false;
	int m_sceneChageAlpha = 0;
	Math::Matrix m_sceneChangeMat = Math::Matrix::Identity;

	KdTexture m_tmpTex;
	KdTexture m_sceneChangeTex;

public:

	// �����ݒ�
	void Init();

	// ���
	void Release();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw2D();

	// GUI����
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
