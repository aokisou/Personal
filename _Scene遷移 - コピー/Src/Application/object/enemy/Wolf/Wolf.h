#pragma once

#include "../BaseEnemy.h"

class Wolf :public BaseEnemy
{
public:
	Wolf(Math::Vector2 _pos) { Init(_pos); }
	~Wolf() { Release(); }

	void Action()override;
	void Update(float _scrollX)override;
	bool Attack()override;

	void SetRunState()override;
	void SetDeathState()override;
	void SetAttackState()override;

	int GetSpaceWidthImg()override { return (int)(12 * m_scale); }
	int GetSpaceHeightImg()override { return (int)(11 * m_scale); }

	int GetDmg();
private:
	void Init(Math::Vector2 _pos)override;
	void Release()override;

	int m_lookRange = 0;					//Ž‹”F”ÍˆÍ

	const std::string m_fileName[3] = { "Texture/Enemy/3/S_Walk.png","Texture/Enemy/3/S_Death.png","Texture/Enemy/3/S_Attack.png" };
};