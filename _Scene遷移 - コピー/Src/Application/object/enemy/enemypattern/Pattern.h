#pragma once

#include "../../../utility/utility.h"

class BaseEnemy;

//デフォルトはスタンド状態にする(エラーが起きても立っている状態にするため)
class EnemyPattern
{
public:
	EnemyPattern() { m_enemy = 0; m_AnimeCnt = 0; m_CoolCnt = 0; }
	~EnemyPattern() { Release(); }

	virtual void Init(BaseEnemy* _enemy)final;
	virtual void Update();

	void Release() { m_enemy = nullptr; }

	virtual int GetAnimeCnt() { return m_AnimeCnt; }
	virtual int GetStateType() { return stand; }

protected:
	BaseEnemy* m_enemy;

	int m_AnimeCnt;
	int m_CoolCnt;
};