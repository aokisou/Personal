#pragma once

#include "../EnemyPattern.h"

class EnemyDeath :public EnemyPattern
{
public:
	EnemyDeath() {}
	~EnemyDeath() { Release(); }

	void Update()override;

	int GetStateType() override{ return enemyDeath; }

	int GetMaxAnimeNum() { return 5; }
};