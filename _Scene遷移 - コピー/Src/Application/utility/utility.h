#pragma once

//��`
#define Gravity 1			//�d��
#define DefaultDir 1
//�v���C���[
#define PlySpeed 5			//�v���C���[���x
#define PlyJumpPow 30		//�v���C���[�̃W�����v��
#define PlyShotInterval 6	//�v���C���[�̒e��ł��o(Maxfps/���̐��l)
#define PlyMoveRange -150	//�v���C���[�̈ړ��͈�
#define PlyStartPos -210	//�v���C���[�̊J�nY���W
#define PlyStartHP 5		//�v���C���[�̊J�nHP
#define PlyMaxDmgEfcCnt 20	//�Ԃ����鎞��
#define PlyBltCRX 30		//�e�̏o��ʒu���e�܂ŕ␳X���W
#define PlyBltCRY 6			//�e�̏o��ʒu���e�܂ŕ␳Y���W

#define BltSpeed 7			//�e�̑��x

//�G�l�~�[
#define EmyMaxDmgEfcCnt 10	//�Ԃ����鎞��

#define Half 2				//�����ɂ������Ƃ��g��
#define Reverse -1			//���]

#define ChrImgSize 48		//�L�����摜�T�C�Y
#define ChrScale 2			//�L�����g�嗦

#define BltSize 3			//�e�摜�T�C�Y
#define BltScale 4			//�e�g�嗦

#define MapSize 64			//�}�b�v�T�C�Y

#define ExpSize 19			//�����摜�T�C�Y
#define ExpOneTime 5		//��摜�̎���
#define ExpNum 4			//�����摜��

enum ChangeScene
{
	no,
	title,
	game,
	result
};

enum CharaType
{
	run,
	stand,
	death,
	jump
};

namespace SCREEN
{
	const int width = 1280;
	const int height = 720;
}