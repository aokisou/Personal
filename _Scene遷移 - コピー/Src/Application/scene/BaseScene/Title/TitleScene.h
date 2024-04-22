#pragma once

#include "../BaseScene.h"

class TitleScene: public BaseScene
{
public:
	TitleScene(int* _fps) { m_maxFps = _fps; Init(); }
	~TitleScene(){}

	int Update()override;
	void Draw()override;
	void DynamicDraw2D()override;

private:
	void Init()override;
	void Release()override;

	KdTexture m_titleTex;
};