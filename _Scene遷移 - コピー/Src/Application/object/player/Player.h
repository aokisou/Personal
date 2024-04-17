#pragma once

#include "../BaseObject.h"

class Bullet;
class PlayerPattern;

class Game;

class Player:public BaseObject
{
public:
	Player() { m_pState = nullptr; m_pOwner = nullptr; }
	~Player() { Release(); }

	void Init()override;
	void Action()override;
	void Update()override;
	void Draw()override;

	void SetOwner(Game* a_pOwner) { m_pOwner = a_pOwner; }

	bool GetbDmg() { return m_bDmg; }

	void SetStandState();
	void SetJumpState();
	void SetRunState();
	void SetDeadState();

	//�����蔻��p
	void ApplyDamage() { m_bDmg = true; m_hp--; }
	std::vector<Bullet*>* GetBullet() { return &m_bullet; }

	void MapHitY(float _posY, float _moveY, bool _b);

	//�m�F�p
	int GetBulletNum() { return m_bullet.size(); }
	int GetHP() { return m_hp; }

private://�֐�
	//�e
	//����
	void BulletShot();
	//�X�V�ƗL������
	void BulletActivate();

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

	Game* m_pOwner;
};