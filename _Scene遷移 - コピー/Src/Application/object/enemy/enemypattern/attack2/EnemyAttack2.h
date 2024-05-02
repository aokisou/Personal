#pragma once

#include "../EnemyPattern.h"

class EnemyAttack2 :public EnemyPattern
{
public:
	EnemyAttack2() {}
	~EnemyAttack2() { Release(); }

	void Update()override;

	int GetStateType()override { return enemyAttack; }

private:
	void Attack();

	bool m_bAttack = false;
};