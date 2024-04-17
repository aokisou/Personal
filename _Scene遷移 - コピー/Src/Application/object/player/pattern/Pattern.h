#pragma once

#include "../../../utility/utility.h"

class Player;

//デフォルトはスタンド状態にする(エラーが起きても立っている状態にするため)
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