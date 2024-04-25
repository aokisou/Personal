#pragma once

#include "../BaseEnemy.h"

class Wolf :public BaseEnemy
{
public:
	Wolf() { Init(); }
	~Wolf() { Release(); }

	void Action()override;
	void Update(float _scrollX)override;
	bool Attack()override;

	void SetRunState()override;
	void SetDeathState()override;
	void SetAttackState()override;

	int GetSpaceWidthImg()override { return (int)(12 * m_scale); }
	int GetSpaceHeightImg()override { return (int)(11 * m_scale); }

	int GetDmg() { return 3; }
private:
	void Init()override;
	void Release()override;

	int m_lookRange = 0;					//Ž‹”F”ÍˆÍ

	const std::string m_fileName[3] = { "Texture/enemy/3/S_Walk.png","Texture/enemy/3/S_Death.png","Texture/enemy/3/S_Attack.png" };
};