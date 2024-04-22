#pragma once

//��`
#define Gravity 1		//�d��
#define DefaultDir 1	//�ʏ�̌���

#define Half 2			//�����ɂ������Ƃ��g��
#define Reverse -1		//���]

enum ChangeScene
{
	no,
	title,
	game,
	result
};

enum StateType
{
	playerStand,
	playerGetHit,
	playerDeath,
	playerJump,
	playerRun,
	playerAttack,
	playerFall,
	enemyRun = 0,
	enemyDeath,
	enemyAttack,
};

enum MapTile//ID�ƍ��킹��
{
	none = -1,
	Block0 = 0,
	Block1,
	Block2,
	Block3,
	Block4,
	Block5,
	Block6,
	Block7,
	Block8,
	Block9,
	Block10,
	Block11,
	Block12,
	Block13,
	Block14,
	Block15,
	Block16,
	Block17,
};

namespace SCREEN
{
	const int width = 1280;
	const int height = 720;
}