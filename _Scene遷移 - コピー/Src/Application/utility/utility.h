#pragma once

//��`
#define Gravity 1			//�d��
#define DefaultDir 1
//�v���C���[
#define PlySpeed 5			//�v���C���[���x
#define PlyJumpPow 20		//�v���C���[�̃W�����v��
#define PlyShotInterval 6	//�v���C���[�̒e��ł��o(Maxfps/���̐��l)
#define PlyMoveRange -150	//�v���C���[�̈ړ��͈�
#define PlyStartPosX -600	//�v���C���[�̊J�nX���W
#define PlyStartPosY -210	//�v���C���[�̊J�nY���W
#define PlyStartHP 5		//�v���C���[�̊J�nHP
#define PlyMaxDmgEfcCnt 20	//�Ԃ����鎞��
#define PlyBltCRX 30		//�e�̏o��ʒu���e�܂ŕ␳X���W
#define PlyBltCRY 6			//�e�̏o��ʒu���e�܂ŕ␳Y���W

#define BltSpeed 7			//�e�̑��x

#define Half 2				//�����ɂ������Ƃ��g��
#define Reverse -1			//���]

enum ChangeScene
{
	no,
	title,
	game,
	result
};

enum StateType
{
	playerRun,
	playerStand,
	playerDeath,
	playerJump,
	enemyStand = 0,
	enemyRun,
	enemyShot,
	enemyDeath
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
	HalfBlock8,
	HalfBlock9,
	HalfBlock10,
	HalfBlock11,
	HalfBlock12,
	HalfBlock13,
	HalfBlock14,
	Fence15,
	Fence16,
	Fence17,
};

namespace SCREEN
{
	const int width = 1280;
	const int height = 720;
}