#pragma once

#include "../EnemyPattern.h"

class EnemyEntry:public EnemyPattern
{
public:
	EnemyEntry() {}
	~EnemyEntry() { Release(); }

	void Update()override;

	int GetStateType()override { return enemyBossEntry; }
private:
	bool m_bFirst = false;
};