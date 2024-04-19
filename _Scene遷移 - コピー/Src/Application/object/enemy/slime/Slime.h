#pragma once

#include "../BaseEnemy.h"

class Slime :public BaseEnemy
{
public:
	Slime() { Init(); }
	~Slime() { Release(); }

	void Action()override;
	void Update(float _scrollX)override;
	void Draw()override;

	void SetRunState()override;
	void SetDeathState()override;

	int GetSpaceWidthImg() { return 40; }
	int GetSpaceHeightImg() { return 20; }

	float GetHP() { return m_hp; }
private:
	void Init()override;
	void Release()override;

	const int EmyMaxDmgEfcCnt = 10;	//赤く光る時間
	const int ImgSize = 48;		//キャラ画像サイズ
	const int Scale = 2;		//キャラ拡大率
};