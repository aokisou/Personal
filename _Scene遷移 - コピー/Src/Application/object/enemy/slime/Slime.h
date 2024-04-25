#pragma once

#include "../BaseEnemy.h"

class Slime :public BaseEnemy
{
public:
	Slime() { Init(); }
	~Slime() { Release(); }

	void Action()override;
	void Update(float _scrollX)override;
	bool Attack()override;

	void SetRunState()override;
	void SetDeathState()override;

	int GetSpaceWidthImg()override { return (int)(20 * m_scale); }
	int GetSpaceHeightImg()override { return (int)(10 * m_scale); }

private:
	void Init()override;
	void Release()override;

	const std::string m_fileName[2] = { "Texture/enemy/1/S_Walk.png","Texture/enemy/1/S_Death.png" };
};