#pragma once

#include "../BaseObject.h"

class Bullet;
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

	int GetSpaceWidthImg();
	int GetSpaceHeightImg();

	//当たり判定用
	void ApplyDamage() { m_bDmg = true; m_hp--; }
	std::vector<Bullet*>* GetBullet() { return &m_bullet; }

	void MapHitY(float _posY, float _moveY, bool _b);

	//確認用
	int GetBulletNum() { return m_bullet.size(); }
	int GetHP() { return m_hp; }

private:
	void Init()override;
	//弾
	//発射
	void BulletShot();
	//更新と有効判定
	void BulletActivate(float _scrollX);

	void Release()override;

	Math::Matrix m_shadowMat;

	int m_hp;

	bool m_bJump;

	std::vector<Bullet*> m_bullet;
	bool m_bshot;
	int m_shotinterval;

	bool m_bDmg;
	int m_DmgEfcCnt;

	PlayerPattern* m_pState;

	GameScene* m_pOwner;

};