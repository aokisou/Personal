#pragma once

#include "../../../utility/utility.h"

class Player;

//デフォルトはスタンド状態にする(エラーが起きても立っている状態にするため)
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