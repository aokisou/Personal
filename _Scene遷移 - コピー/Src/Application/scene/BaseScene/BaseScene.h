#pragma once

class Scene;

class BaseScene
{
public:
	BaseScene() { m_pOwner = nullptr; m_maxFps = nullptr; }
	virtual ~BaseScene() { m_pOwner = nullptr; m_maxFps = nullptr; }

	virtual int Update() = 0;
	virtual void Draw() = 0;
	virtual void DynamicDraw2D() = 0;
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual int* GetMAXfps() { return m_maxFps; }

	virtual void SetOwner(Scene* _pOwner)final { m_pOwner = _pOwner; }

	virtual float GetHp();
protected:
	int* m_maxFps = nullptr;

	Scene* m_pOwner = nullptr;
};