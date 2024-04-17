#pragma once

#include "../../../utility/utility.h"

class BaseEnemy;

//�f�t�H���g�̓X�^���h��Ԃɂ���(�G���[���N���Ă������Ă����Ԃɂ��邽��)
class EnemyPattern
{
public:
	EnemyPattern() { m_enemy = 0; m_AnimeCnt = 0; m_CoolCnt = 0; }
	~EnemyPattern() { Release(); }

	virtual void Init(BaseEnemy* _enemy)final;
	virtual void Update();

	void Release() { m_enemy = nullptr; }

	virtual int GetAnimeCnt() { return m_AnimeCnt; }
	virtual int GetStateType() { return stand; }

protected:
	BaseEnemy* m_enemy;

	int m_AnimeCnt;
	int m_CoolCnt;
};