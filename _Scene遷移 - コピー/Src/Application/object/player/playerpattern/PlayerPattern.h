#pragma once

#include "../../../utility/utility.h"

class Player;

//�f�t�H���g�̓X�^���h��Ԃɂ���(�G���[���N���Ă������Ă����Ԃɂ��邽��)
class PlayerPattern
{
public:
	PlayerPattern() { }
	virtual ~PlayerPattern() { Release(); }

	virtual void Init(Player* a_player,std::string _filename)final;
	virtual void Update();

	virtual void Release() { m_player = nullptr; }

	virtual int GetAnimeCnt()final { return m_AnimeCnt; }
	virtual int GetStateType() { return playerStand; }

	KdTexture* GetTex() { return &m_tex; }

protected:
	Player* m_player = nullptr;

	int m_AnimeCnt = 0;
	int m_CoolCnt = 0;

	KdTexture m_tex;
};