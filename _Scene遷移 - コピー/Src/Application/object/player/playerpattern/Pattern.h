#pragma once

#include "../../../utility/utility.h"

class Player;

//�f�t�H���g�̓X�^���h��Ԃɂ���(�G���[���N���Ă������Ă����Ԃɂ��邽��)
class PlayerPattern
{
public:
	PlayerPattern() { m_player = 0; m_AnimeCnt = 0; m_CoolCnt = 0; }
	~PlayerPattern() { Release(); }

	virtual void Init(Player* a_player)final;
	virtual void Update();

	virtual void Release() { m_player = nullptr; }

	virtual int GetAnimeCnt() { return m_AnimeCnt; }
	virtual int GetStateType() { return stand; }

protected:
	Player* m_player;

	int m_AnimeCnt;
	int m_CoolCnt;
};