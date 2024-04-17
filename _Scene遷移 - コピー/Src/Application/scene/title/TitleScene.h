#pragma once

#include "../BaseScene.h"

class Title: public BaseScene
{
public:
	Title(int _fps) { m_maxFps = _fps; m_pTex = nullptr; }
	~Title(){}

	int Update();
	void Draw();
	void Init();
private:
	void Release();
};