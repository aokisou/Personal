#pragma once

#include "../../../Utility/Utility.h"

class BaseEnemy;

//デフォルトはスタンド状態にする(エラーが起きても立っている状態にするため)
class EnemyPattern
{
public:
	EnemyPattern() { }
	virtual ~EnemyPattern() { Release(); }

	virtual void Init(BaseEnemy* _enemy, std::string _file)final;
	virtual void Update();

	int GetAnimeCnt() { return m_animeNum; }
	virtual int GetStateType() = 0{}

	virtual int GetMaxAnimeNum() = 0 { return 0; }

	KdTexture* GetTex() { return &m_tex; }

	void Release() { m_enemy = nullptr; }
protected:

	BaseEnemy* m_enemy = nullptr;

	int m_animeNum = 0;
	int m_coolCnt = 0;

	KdTexture m_tex;
};