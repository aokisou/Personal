#pragma once

#include "../../../utility/utility.h"

class Player;

//デフォルトはスタンド状態にする(エラーが起きても立っている状態にするため)
class PlayerPattern
{
public:
	PlayerPattern() { }
	virtual ~PlayerPattern() { Release(); }

	virtual void Init(Player* a_player,std::string _filename)final;
	virtual void Update();

	virtual void Release() { m_player = nullptr; }

	virtual int GetAnimeNum()final { return m_animeNum; }
	virtual int GetStateType() { return playerStand; }

	KdTexture* GetTex() { return &m_tex; }

protected:
	Player* m_player = nullptr;

	int m_animeNum = 0;
	int m_coolCnt = 0;

	KdTexture m_tex;
};