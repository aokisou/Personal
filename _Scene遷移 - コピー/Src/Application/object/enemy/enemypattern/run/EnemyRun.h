#pragma once

#include "../EnemyPattern.h"

class EnemyRun :public EnemyPattern
{
public:
	EnemyRun() {}
	~EnemyRun(){ Release(); }

	void Update()override;

	int GetStateType()override { return enemyRun; }
};