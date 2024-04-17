#pragma once

#include "../BaseScene.h"

class Result :public BaseScene
{
public:
	Result(int _fps) { m_maxFps = _fps; m_pTex = nullptr;}
	~Result(){}

	int Update();
	void Draw();
	void Init();
	void Release();

private:
};