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

	enum PlayTime
	{
		tm,
		om,
		colon,
		ts,
		os,
		ptnum,
	};

	bool m_bClear;

	float m_posY = 0.0f;

	int m_alphaAng = 0;
	KdTexture m_charTex[CharType::num];
	Math::Matrix m_charMat[CharType::num];

	Math::Matrix m_backMat = Math::Matrix::Identity;
	KdTexture m_backTex[5];
	std::string m_backName[5] = { "Texture/BackGround/1.png","Texture/BackGround/2.png","Texture/BackGround/3.png","Texture/BackGround/4.png",
								  "Texture/BackGround/5.png" };

	Math::Matrix m_clearTimeMat = Math::Matrix::Identity;
	KdTexture m_clearTimeTex;

	int m_moveInteerval;
	int m_angle[PlayTime::ptnum];
	Math::Matrix m_timeMat[PlayTime::ptnum];
	KdTexture m_timeTex[PlayTime::ptnum];
	const std::string m_numFileName[10] = { "Texture/Result/0.png","Texture/Result/1.png", "Texture/Result/2.png", "Texture/Result/3.png",
	"Texture/Result/4.png", "Texture/Result/5.png", "Texture/Result/6.png", "Texture/Result/7.png",
	"Texture/Result/9.png", "Texture/Result/8.png", };
};