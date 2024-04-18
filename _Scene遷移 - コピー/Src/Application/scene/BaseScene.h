#pragma once

class Scene;

class BaseScene
{
public:
	BaseScene() {}
	virtual ~BaseScene() {}

	virtual int Update() = 0;
	virtual void Draw() = 0;
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual int* GetMAXfps() { return m_maxFps; }

	void GetOwner(Scene* _pOwner) { m_pOwner = _pOwner; }
protected:
	int* m_maxFps;

	Scene* m_pOwner;
};