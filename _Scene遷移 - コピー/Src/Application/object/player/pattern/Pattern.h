#pragma once

#include "../../../utility/utility.h"

class Player;

//�f�t�H���g�̓X�^���h��Ԃɂ���(�G���[���N���Ă������Ă����Ԃɂ��邽��)
class Pattern
{
public:
	Pattern() {}
	~Pattern(){}

	virtual void Init(Player* a_player);
	virtual void Update();

	virtual int GetAnimeCnt() { return m_AnimeCnt; }
	virtual int GetStateType() { return stand; }

protected:
	Player* m_player;

	int m_AnimeCnt;
	int m_CoolCnt;
};