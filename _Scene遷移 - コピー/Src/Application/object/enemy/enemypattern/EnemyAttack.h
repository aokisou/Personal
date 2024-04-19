#pragma once

#include "EnemyPattern.h"

class EnemyAttack :public EnemyPattern
{
public:
	EnemyAttack() {}
	~EnemyAttack() { Release(); }

	void Update()override;

	int GetStateType()override { return enemyRun; }
};