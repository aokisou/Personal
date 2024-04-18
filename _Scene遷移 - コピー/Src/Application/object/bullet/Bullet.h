#pragma once

#include "../BaseObject.h"

class Bullet:public BaseObject
{
public:
	Bullet() { Init(); }
	~Bullet(){}

	void Action()override;
	void Update(float _scrollX)override;
	void Draw()override;

	void SetPos(Math::Vector2 a_pos) { m_pos = a_pos; }
	void SetDir(int _dir) { m_dir = _dir; }//�v���C���[�̌����ɔ�Ԃ悤�ɂ���

	bool GetContent()override { return true; }
private:
	void Init()override;

	int m_dir;
};