#pragma once

#include "../BaseScene.h"

class Title: public BaseScene
{
public:
	Title(int _fps) { m_maxFps = _fps; }
	~Title(){}

	int Update()override;
	void Draw()override;
	void Init()override;
private:
	void Release()override;

	KdTexture m_titleTex;
};