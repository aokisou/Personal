#pragma once

#include "../BaseScene.h"

class TitleScene: public BaseScene
{
public:
	TitleScene(int* _fps) { m_maxFps = _fps; Init(); }
	~TitleScene(){}

	void Update()override;
	void Draw(KdTexture* _pTex)override;
	void DynamicDraw2D()override;

private:
	void Init()override;
	void Release()override;
	
	int m_alphaAng;
	KdTexture m_startTex;
	Math::Matrix m_startMat = Math::Matrix::Identity;

	KdTexture m_backTex[5];
	std::string m_backName[5] = { "Texture/BackGround/1.png","Texture/BackGround/2.png","Texture/BackGround/3.png","Texture/BackGround/4.png",
										"Texture/BackGround/5.png" };

	Math::Matrix m_titleMat = Math::Matrix::Identity;
	KdTexture m_titleTex;
};