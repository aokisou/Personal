#pragma once

#include "../BaseObject.h"

class EnemyPattern;

class BaseEnemy :public BaseObject
{
public:
	BaseEnemy(){}
	~BaseEnemy(){}

	void Init()override;
	void Action()override;
	void Update()override;
	void Draw()override;

	void ApplyDamage() { m_bDmg = true; m_hp--; }

	bool GetbDead() { return m_bDead; }
private:
	int m_hp;
	bool m_bDead;
	int m_ExpNum;
	int m_ExpCnt;

	bool m_bDmg;
	int DmgEfcCnt;

	EnemyPattern* m_pState;
};