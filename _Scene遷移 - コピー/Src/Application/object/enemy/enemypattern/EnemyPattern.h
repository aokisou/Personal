#pragma once

#include "../../../Utility/Utility.h"

class BaseEnemy;

//�f�t�H���g�̓X�^���h��Ԃɂ���(�G���[���N���Ă������Ă����Ԃɂ��邽��)
class EnemyPattern
{
public:
	EnemyPattern() { }
	virtual ~EnemyPattern() { Release(); }

	virtual void Init(BaseEnemy* _enemy, std::string _file)final;
	virtual void Update();

	virtual int GetAnimeCnt() { return m_animeNum; }
	virtual int GetStateType() = 0{}

	void Release() { m_enemy = nullptr; }

	KdTexture* GetTex() { return &m_tex; }

protected:

	BaseEnemy* m_enemy = nullptr;

	int m_animeNum = 0;
	int m_coolCnt = 0;

	KdTexture m_tex;
};