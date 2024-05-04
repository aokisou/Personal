#pragma once

#include "../BaseScene.h"

class ResultScene :public BaseScene
{
public:
	ResultScene(int* _fps, bool _b,const int _minuets,const int _seconds) { m_maxFps = _fps; m_bClear = _b; Init(_minuets,_seconds); }
	~ResultScene() { Release(); }

	void Update()override;
	void Draw(KdTexture* _pTex)override;
	void DynamicDraw2D()override;

private:
	void Init(const int _minuets, const int _seconds);
	void Init()override {}
	void Release()override;
	void ResetNumPos();

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

	Math::Vector2 m_backPos[5];
	Math::Vector2 m_2ndBackPos[5];
	Math::Matrix m_backMat[5];
	Math::Matrix m_2ndBackMat[5];
	KdTexture m_backTex[5];
	std::string m_backName[5] = { "Texture/BackGround/1.png","Texture/BackGround/2.png","Texture/BackGround/3.png","Texture/BackGround/4.png",
								  "Texture/BackGround/5.png" };

	Math::Matrix m_clearTimeMat = Math::Matrix::Identity;
	KdTexture m_clearTimeTex;

	int m_moveInteerval;
	int m_angle[5];
	Math::Matrix m_timeMat[5];
	KdTexture m_timeTex[5];
};