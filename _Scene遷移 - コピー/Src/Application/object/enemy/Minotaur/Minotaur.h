#pragma once

#include "../BaseEnemy.h"

class Minotaur :public BaseEnemy
{
public:
	Minotaur(Math::Vector2 _pos) { Init(_pos); }
	~Minotaur() { Release(); }

	void Action()override;
	void Update(float _scrollX)override;
	bool Attack()override;

	void UpdateUI(float _scrollX)override;
	void DrawUI()override;

	void SetRunState()override;
	void SetDeathState()override;
	void SetAttackState()override;

	int GetSpaceWidthImg() { return (int)(32 * m_scale); }
	int GetSpaceHeightImg() { return (int)(32 * m_scale); }

	int GetDmg();

private:
	void Init(Math::Vector2 _pos)override;
	void Release()override;

	const std::string m_fileName[3] = { "Texture/Enemy/Boss/run.png","Texture/Enemy/Boss/death.png","Texture/Enemy/Boss/attack.png" };
};