#pragma once

#include "Pattern.h"

class Enemy;

class EnemyRun :public EnemyPattern
{
public:
	EnemyRun() {}
	~EnemyRun(){ Release(); }

	void Update()override;

	int GetStateType()override { return run; }
};