#pragma once

#include "Pattern.h"

class EnemyDeath :public EnemyPattern
{
public:
	EnemyDeath() {}
	~EnemyDeath() { Release(); }

	void Update()override;

	int GetStateType() override{ return death; }
};