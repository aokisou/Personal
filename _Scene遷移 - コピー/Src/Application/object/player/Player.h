#pragma once

#include "../BaseObject.h"

class Arrow;
class PlayerPattern;

class GameScene;

class Player:public BaseObject
{
public:
	Player() { Init(); }
	~Player() { Release(); }

	void Action()override;
	void Update(float _scrollX)override;
	void Draw()override;

	void SetOwner(GameScene* a_pOwner) { m_pOwner = a_pOwner; }

	bool GetbDmg() { return m_bDmg; }

	void SetStandState();
	void SetJumpState();
	void SetRunState();
	void SetDeathState();
	void SetAttackState();

	int GetSpaceWidthImg() { return 30; }
	int GetSpaceHeightImg(){ return 32; }

	//当たり判定用
	void ApplyDamage() { m_bDmg = true; m_hp--; }
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

	bool m_bJump;

	std::vector<Arrow*> m_arrow;
	bool m_bShot;
	int m_shotInterval;

	bool m_bDmg;
	int m_DmgEfcCnt;

	PlayerPattern* m_pState;

	GameScene* m_pOwner;

public:
};