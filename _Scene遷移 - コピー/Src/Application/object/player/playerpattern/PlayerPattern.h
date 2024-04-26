#pragma once

#include "../../../Utility/utility.h"

class Player;

//デフォルトはスタンド状態にする(エラーが起きても立っている状態にするため)
class PlayerPattern
{
public:
	PlayerPattern() { m_player = nullptr; }
	virtual ~PlayerPattern() { Release(); }

	virtual void Init(Player* a_player,std::string _file)final;
	virtual void Update();

	virtual void Release() { m_player = nullptr; }

	virtual int GetAnimeNum()final { return m_animeNum; }
	virtual int GetStateType() { return playerStand; }

	virtual int GetMaxAnimeNum() = 0 { return 0; }

	KdTexture* GetTex() { return &m_tex; }

protected:
	Player* m_player = nullptr;

	int m_animeNum = 0;
	int m_coolCnt = 0;

	KdTexture m_tex;
};