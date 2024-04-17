#pragma once

#include "../BaseObject.h"

class Bullet:public BaseObject
{
public:
	Bullet(){}
	~Bullet(){}

	void Init()override;
	void Action()override;
	void Update()override;
	void Draw()override;

	void SetPos(Math::Vector2 a_pos) { m_pos = a_pos; }
	void SetDir(int _dir) { m_dir = _dir; }//�v���C���[�̌����ɔ�Ԃ悤�ɂ���
private:
	int m_dir;
};