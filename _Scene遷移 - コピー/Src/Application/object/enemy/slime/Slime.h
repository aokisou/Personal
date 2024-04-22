#pragma once

#include "../BaseEnemy.h"

class Slime :public BaseEnemy
{
public:
	Slime() { Init(); }
	~Slime() { Release(); }

	void Action()override;
	void Update(float _scrollX)override;
	void Attack()override;

	void SetRunState()override;
	void SetDeathState()override;

	int GetSpaceWidthImg() { return 40; }
	int GetSpaceHeightImg() { return 20; }

	float GetHP() { return m_hp; }
private:
	void Init()override;
	void Release()override;

	const int EmyMaxDmgEfcCnt = 10;	//�Ԃ����鎞��
	const int ImgSize = 48;		//�L�����摜�T�C�Y
	const int Scale = 2;		//�L�����g�嗦

	bool m_bAttack = false;

	const std::string m_fileName[2] = { "Texture/enemy/1/S_Walk.png","Texture/enemy/1/S_Death.png" };
};