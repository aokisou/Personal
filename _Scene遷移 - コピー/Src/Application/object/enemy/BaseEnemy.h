#pragma once

#include "../BaseObject.h"

class EnemyPattern;

class BaseEnemy :public BaseObject
{
public:
	BaseEnemy() { Init(); }
	virtual ~BaseEnemy() {}

	virtual void Init()override = 0;
	virtual void Action()override = 0;
	virtual void Update(float _scrollX)override = 0;
	virtual void Draw()override = 0;
	virtual void Release()override = 0 {}

	virtual void SetStandState(){}
	virtual void SetRunState(){}
	virtual void SetDeathState(){}
	virtual void SetAttackState(){}

	virtual int GetSpaceWidthImg() { return 40; }
	virtual int GetSpaceHeightImg() { return 20; }

	void ApplyDamage(float _dmg) { m_bDmg = true; m_hp -= _dmg; }

	bool GetbDead() { return m_bDead; }

	virtual float GetHP() { return m_hp; }
protected:

	float m_hp;
	bool m_bDead;

	bool m_bDmg;
	int DmgEfcCnt;

	EnemyPattern* m_pState;
};