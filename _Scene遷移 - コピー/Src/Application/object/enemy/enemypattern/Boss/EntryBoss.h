#pragma once

#include "../EnemyPattern.h"

class EntryEnemy:public EnemyPattern
{
public:
	EntryEnemy() {}
	~EntryEnemy() { Release(); }

	void Update()override;

	int GetStateType()override { return enemyBossEntry; }

	int GetMaxAnimeNum() { return 9; }
};