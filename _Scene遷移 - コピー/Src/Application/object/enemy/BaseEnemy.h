#pragma once

#include "../BaseObject.h"

class EnemyPattern;
class GameScene;
class EnemyHPBar;

class BaseEnemy :public BaseObject
{
public:
	BaseEnemy() { Init(); }
	virtual ~BaseEnemy() {}

	virtual void Init()override;
	virtual void Init(Math::Vector2 _pos) = 0;
	virtual void Action()override = 0;
	virtual void Update(float _scrollX)override = 0;
	virtual void Draw()override;
	virtual void Release()override = 0 {}
	void Reset()override;
	virtual void UpdateUI(float _scrollX) = 0{}
	virtual void DrawUI() = 0{}

	virtual bool Attack() = 0{}

	virtual void SetOwner(GameScene* _pOwner)final { m_pOwner = _pOwner; }

	GameScene* GetOwner() { return m_pOwner; }

	void ResetAttackCoolTime() { m_attackCoolTime = 0; }

	virtual void SetRunState(){}
	virtual void SetDeathState(){}
	virtual void SetAttackState(){}

	virtual int GetSpaceWidthImg() { return 40; }
	virtual int GetSpaceHeightImg() { return 20; }

	void SetDamage(float _dmg);

	virtual int GetDmg() { return 0; }//çUåÇÉÇÅ[ÉVÉáÉìÇ™Ç†ÇÈìGÇÃÇ›

	std::shared_ptr<EnemyPattern> GetEnemyState(){ return m_pState; }

	virtual Math::Vector2 GetMovePow() { return m_move; }

	virtual float GetAngleDeg(Math::Vector2 src, Math::Vector2 dest)final;

	int GetAttackHitCnt() { return m_attackHitCnt; }

protected:
	void InitUI();

	Math::Vector2 m_startPos = {};

	int m_moveRange = 0;
	int m_attackRange = 0;

	int m_attackHitCnt = 0;

	float m_hp = 0;

	bool m_bDmg = false;
	int DmgEfcCnt = 0;

	int m_attackCoolTime = 0;

	std::shared_ptr<EnemyPattern> m_pState = nullptr;

	std::shared_ptr<EnemyHPBar> m_pHPBar = nullptr;

	KdTexture m_gaugeTex;
	KdTexture m_barTex;

	GameScene* m_pOwner = nullptr;
};