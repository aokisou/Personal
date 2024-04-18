#pragma once

#include "../../../utility/utility.h"

class BaseEnemy;

//デフォルトはスタンド状態にする(エラーが起きても立っている状態にするため)
class EnemyPattern
{
public:
	EnemyPattern() { }
	virtual ~EnemyPattern() { Release(); }

	virtual void Init(BaseEnemy* _enemy)final;
	virtual void Update();

	void Release() { m_enemy = nullptr; }

	virtual int GetAnimeCnt() { return m_AnimeCnt; }
	virtual int GetStateType() { return enemyStand; }

protected:
	BaseEnemy* m_enemy;

	int m_AnimeCnt;
	int m_CoolCnt;
};