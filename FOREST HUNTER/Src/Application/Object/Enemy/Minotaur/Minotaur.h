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
	void SetAttack2State();
	void SetEntryState();

	int GetSpaceWidthImg() { return (int)(20 * m_scale); }
	int GetSpaceHeightImg() { return (int)(32 * m_scale); }

	int GetDmg() { return m_dmg; }

private:
	void Init(Math::Vector2 _pos)override;
	void Release()override;
	int GetDeadSpaceRightImg() { return int(56 * m_scale); }
	int GetDeadSpaceLeftImg() { return int(28 * m_scale); }
	int GetDeadSpaceTopImg() { return int(45 * m_scale); }
	int GetDeadSpaceBottomImg() { return int(20 * m_scale); }
	int GetUISpaceTop() { return int(20 * m_scale); }

	int m_dmg = 0;

	const std::string m_fileName[4] = { "Texture/Enemy/Boss/run.png","Texture/Enemy/Boss/attack.png"
		,"Texture/Enemy/Boss/death.png","Texture/Enemy/Boss/entry.png"};
};