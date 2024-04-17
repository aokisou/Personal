#pragma once

class Scene;

class BaseScene
{
public:
	BaseScene() {}
	virtual ~BaseScene() {}

	virtual int Update();
	virtual void Draw();
	virtual void Init();
	virtual void SetTexture(KdTexture* _pTex) { m_pTex = _pTex; }
	virtual int GetMAXfps() { return m_maxFps; }

	void GetOwner(Scene* _pOwner) { m_pOwner = _pOwner; }
protected:
	virtual void Release();

	int m_maxFps;

	Scene* m_pOwner;

	KdTexture* m_pTex;
};