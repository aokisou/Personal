#pragma once

#include "../BaseScene.h"

class ResultScene :public BaseScene
{
public:
	ResultScene(int* _fps) { m_maxFps = _fps; Init(); }
	~ResultScene() { Release(); }

	int Update()override;
	void Draw(KdTexture* _pTex)override;
	void DynamicDraw2D()override;

private:
	void Init()override;
	void Release()override;
};