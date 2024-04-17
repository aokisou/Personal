#pragma once

#include "Pattern.h"

class EnemyJump :public EnemyPattern
{
public:
	EnemyJump() {}
	~EnemyJump(){ Release(); }

	void Update()override;

	int GetStateType()override { return jump; }
};