#pragma once

#include "../BaseObject.h"

class Arrow;
class PlayerPattern;

class Player:public BaseObject
{
public:
	Player() { Init(); }
	~Player() { Release(); }

	void Action()override;
	void Update(float _scrollX)override;
	void Draw()override;

	bool GetbDmg() { return m_bDmg; }
	bool GetbDead() { return m_bDead; }

	void SetStandState();
	void SetJumpState();
	void SetRunState();
	void SetDeathState();
	void SetAttackState();
	void SetFallState();
	void SetGetHitState();

	void EndDamageEfc();

	int GetSpaceWidthImg() { return 30; }
	int GetSpaceHeightImg(){ return 32; }

	//当たり判定用
	void ApplyDamage(float _enemyMove);
	std::vector<Arrow*>* GetArrow() { return &m_arrow; }

	void MapHitY(float _posY, float _moveY, bool _b);

	//確認用
	int GetArrowNum() { return m_arrow.size(); }
	int GetHP() { return m_hp; }

private:
	void Init()override;
	//弾
	//発射
	bool ArrowShot();
	//更新と有効判定
	void ArrowActivate(float _scrollX);

	void Release()override;

	float m_hp;

	float m_moveKnockBack;

	bool m_bJump;

	std::vector<Arrow*> m_arrow;

	bool m_bDmg;
	bool m_bDead;

	PlayerPattern* m_pState;

	const std::string m_fileName[7] = {  "Texture/player/Idle.png","Texture/player/GetHit.png","Texture/player/Death.png","Texture/player/Jump.png",
										 "Texture/player/Run.png","Texture/player/Attack.png","Texture/player/Fall.png" };
public:
};