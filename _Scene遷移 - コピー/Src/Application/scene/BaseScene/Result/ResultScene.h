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

	enum CharType
	{
		Continue,
		Title,
		Main,
		num
	};

	bool m_bClear;

	float m_posY = 0.0f;

	int m_alphaAng = 0;
	KdTexture m_charTex[CharType::num];
	Math::Matrix m_charMat[CharType::num];

	KdTexture m_backTex[5];
	std::string m_backName[5] = { "Texture/BackGround/1.png","Texture/BackGround/2.png","Texture/BackGround/3.png","Texture/BackGround/4.png",
										"Texture/BackGround/5.png" };
};