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

	bool GetDmg() { return m_bDmg; }
	bool GetDead() { return m_bDead; }

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

	//�����蔻��p
	void SetDamage(float _enemyMove);//�m�b�N�o�b�N������
	std::vector<Arrow*>* GetArrow() { return &m_arrow; }

	void MapHitY(float _posY, float _moveY, bool _b);

	//�m�F�p
	int GetArrowNum() { return m_arrow.size(); }
	int GetHP() { return m_hp; }

private:
	void Init()override;
	//�e
	//����
	bool ArrowShot();
	//�X�V�ƗL������
	void ArrowActivate(float _scrollX);

	void Release()override;

	float m_hp = 0;

	float m_moveKnockBack = 0;

	bool m_bJump = false;

	std::vector<Arrow*> m_arrow;

	bool m_bDmg = false;
	bool m_bDead = false;

	PlayerPattern* m_pState;

	KdTexture m_arrowTex;

	const std::string m_fileName[7] = { "Texture/player/Idle.png","Texture/player/GetHit.png","Texture/player/Death.png","Texture/player/Jump.png",
										"Texture/player/Run.png","Texture/player/Attack.png","Texture/player/Fall.png" };
public:
};