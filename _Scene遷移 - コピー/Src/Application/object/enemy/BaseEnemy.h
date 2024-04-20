#pragma once

#include "../BaseObject.h"

class EnemyPattern;
class GameScene;

class BaseEnemy :public BaseObject
{
public:
	BaseEnemy() { Init(); }
	virtual ~BaseEnemy() {}

	virtual void Init()override = 0;
	virtual void Action()override = 0;
	virtual void Update(float _scrollX)override = 0;
	virtual void Draw()override;
	virtual void Release()override = 0 {}

	virtual void Attack() = 0{}

	virtual void SetOwner(GameScene* _pOwner)final { m_pOwner = _pOwner; }

	virtual void SetStandState(){}
	virtual void SetRunState(){}
	virtual void SetDeathState(){}
	virtual void SetAttackState(){}

	virtual int GetSpaceWidthImg() { return 40; }
	virtual int GetSpaceHeightImg() { return 20; }

	void ApplyDamage(float _dmg) { m_bDmg = true; m_hp -= _dmg; }

	bool GetbDead() { return m_bDead; }

	virtual float GetAngleDeg(Math::Vector2 src, Math::Vector2 dest)final;

	virtual float GetHP() { return m_hp; }
protected:
	Math::Vector2 m_startPos = {};

	int m_moveRange = 0;
	int m_attackRange = 0;

	float m_hp = 0;
	bool m_bDead = false;

	bool m_bDmg = false;
	int DmgEfcCnt = 0;

	EnemyPattern* m_pState = nullptr;

	GameScene* m_pOwner = nullptr;
};