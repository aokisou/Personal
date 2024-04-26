#pragma once

#include "../BaseScene.h"

class ResultScene :public BaseScene
{
public:
	ResultScene(int* _fps, bool _b) { m_maxFps = _fps; m_bClear = _b; Init(); }
	~ResultScene() { Release(); }

	void Update()override;
	void Draw(KdTexture* _pTex)override;
	void DynamicDraw2D()override;

private:
	void Init()override;
	void Release()override;

	bool m_bClear;
};