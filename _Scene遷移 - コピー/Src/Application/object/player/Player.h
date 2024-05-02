#pragma once

#include "../BaseObject.h"

class Arrow;
class PlayerPattern;
class PlayerHPBar;
class BaseParticle;

class Player:public BaseObject
{
public:
	Player() { Init(); }
	~Player() { Release(); }

	void Action()override;
	void Update(float _scrollX)override;
	void Draw()override;
	void Reset()override;

	void UpdateUI();
	void DrawUI();

	Math::Vector2 GetFuturePos() { return { m_pos.x + m_move.x + m_moveKnockBack,m_pos.y + m_move.y }; }
	bool GetDmg() { return m_bDmg; }
	std::shared_ptr<PlayerPattern> GetPlayerState() { return m_pState; }

	void SetStandState();
	void SetJumpState();
	void SetRunState();
	void SetDeathState();
	void SetAttackState();
	void SetFallState();
	void SetGetHitState();

	void EndDamageEfc();

	int GetSpaceWidthImg() { return (int)(34 * m_scale); }
	int GetSpaceHeightImg(){ return (int)(32 * m_scale); }

	//当たり判定用
	void SetDmg(int _hp, float _enemyMove);//ノックバックをつける
	std::vector<Arrow*>* GetArrow() { return &m_arrow; }

	void MapHitX(float _posX, float _moveX);
	void MapHitY(float _posY, float _moveY, bool _b);

private:
	void Init()override;
	//弾
	//発射
	bool ArrowShot();
	//更新と有効判定
	void ArrowActivate(float _scrollX);
	void ArrowDel();
	void Release()override;

	void CreateWalk();

	int m_hp = 0;

	float m_moveKnockBack = 0;

	bool m_bJump = false;

	std::vector<Arrow*> m_arrow;

	bool m_bDmg = false;

	std::shared_ptr<PlayerPattern> m_pState;

	std::shared_ptr<PlayerHPBar> m_hpBar;

	std::vector<std::shared_ptr<BaseParticle>> m_particle;

	KdTexture m_arrowTex;

	const std::string m_fileName[7] = { "Texture/Player/Idle.png","Texture/Player/GetHit.png","Texture/Player/Death.png","Texture/Player/Jump.png",
										 "Texture/Player/Run.png","Texture/Player/Attack.png","Texture/Player/Fall.png" };
	const std::string m_fileNameP[1] = { "Particle/Walk/walk.png" };
};