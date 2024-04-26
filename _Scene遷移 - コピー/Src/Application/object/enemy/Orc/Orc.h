#pragma once

#include "../BaseEnemy.h"

class Orc :public BaseEnemy
{
public:
	Orc(Math::Vector2 _pos) { Init(_pos); }
	~Orc() { Release(); }

	void Action()override;
	void Update(float _scrollX)override;
	bool Attack()override;

	void SetRunState()override;
	void SetDeathState()override;
	void SetAttackState()override;

	int GetSpaceWidthImg() { return (int)(15* m_scale); }
	int GetSpaceHeightImg() { return (int)(10 * m_scale); }

	int GetDmg();

private:
	void Init(Math::Vector2 _pos)override;
	void Release()override;

	int m_lookRange = 0;	//Ž‹”F”ÍˆÍ

	const std::string m_fileName[3] = { "Texture/Enemy/2/S_Walk.png","Texture/Enemy/2/S_Death.png","Texture/Enemy/2/S_Attack.png" };
};