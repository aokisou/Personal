#pragma once

#include "../BaseEnemy.h"

class Orc :public BaseEnemy
{
public:
	Orc() { Init(); }
	~Orc() { Release(); }

	void Action()override;
	void Update(float _scrollX)override;
	bool Attack()override;

	void SetRunState()override;
	void SetDeathState()override;
	void SetAttackState()override;

	int GetSpaceWidthImg() { return (int)(15* m_scale); }
	int GetSpaceHeightImg() { return (int)(10 * m_scale); }

	int GetDmg() { return 5; }
private:
	void Init()override;
	void Release()override;

	int m_lookRange = 0;					//Ž‹”F”ÍˆÍ

	const std::string m_fileName[3] = { "Texture/enemy/2/S_Walk.png","Texture/enemy/2/S_Death.png","Texture/enemy/2/S_Attack.png" };
};