#pragma once

#include "../BaseObject.h"

class EnemyPattern;

class BaseEnemy :public BaseObject
{
public:
	BaseEnemy() { Init(); }
	~BaseEnemy(){}

	void Action()override;
	void Update(float _scrollX)override;
	void Draw()override;

	void SetStandState();
	void SetRunState();
	void SetDeathState();

	int GetSpaceWidthImg();

	void ApplyDamage() { m_bDmg = true; m_hp--; }

	bool GetbDead() { return m_bDead; }
private:
	void Init()override;

	int m_hp;
	bool m_bDead;
	int m_ExpNum;
	int m_ExpCnt;

	bool m_bDmg;
	int DmgEfcCnt;

	EnemyPattern* m_pState;
};