#pragma once

#include "../../../utility/utility.h"

class BaseEnemy;

//�f�t�H���g�̓X�^���h��Ԃɂ���(�G���[���N���Ă������Ă����Ԃɂ��邽��)
class EnemyPattern
{
public:
	EnemyPattern() { }
	virtual ~EnemyPattern() { Release(); }

	virtual void Init(BaseEnemy* _enemy,std::string _fileName)final;
	virtual void Update();

	void Release() { m_enemy = nullptr; }

	virtual int GetAnimeCnt() { return m_animeNum; }
	virtual int GetStateType() = 0{}

	KdTexture* GetTex() { return &m_tex; }

protected:
	BaseEnemy* m_enemy;

	int m_animeNum;
	int m_coolCnt;

	KdTexture m_tex;
};