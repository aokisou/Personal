#pragma once

#include "Pattern.h"

class EnemyRun :public EnemyPattern
{
public:
	EnemyRun() {}
	~EnemyRun(){ Release(); }

	void Update()override;

	int GetStateType()override { return run; }
};