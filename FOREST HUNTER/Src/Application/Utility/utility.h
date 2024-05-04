#pragma once

//��`
#define Gravity 1		//�d��
#define DefaultDir 1	//�ʏ�̌���

#define Half 2			//�����ɂ������Ƃ��g��
#define Reverse -1		//���]

const std::string m_numFileName[10] = { "Texture/time/0.png","Texture/time/1.png", "Texture/time/2.png", "Texture/time/3.png",
"Texture/time/4.png", "Texture/time/5.png", "Texture/time/6.png", "Texture/time/7.png",
"Texture/time/8.png", "Texture/time/9.png", };

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
	slimeDeath,
	enemyAttack = slimeDeath,
	enemyDeath,
	enemyBossEntry,
};

enum Particle
{
	walk,
};

enum PlayTime
{
	tm,
	om,
	colon,
	ts,
	os,
	ptnum,
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
	Block18,
	Block19,
	Block20,
	Block21,
	Block22,
	Block23,
	Block24,
	Block25,
	Block26,
	Block27,
	Block28,
	Block29,
	Block30,
	Block31,
	Block32,
	Block33,
	Block34,
	Block35,
	Block36,
	Block37,
	Block38,
	Block39,
	Block40,
	Block41,
	Block42,
	Block43,
	Block44,
	Block45,
	Block46,
	Block47,
	Block48,
	Block49,
	Block50,
	//�G�z�u
	Enemy = 100,
	MTSlime = 100,
	MTWolf,
	MTOrc,
	MTBee,
	MTMinotaur,
	//�`���[�g���A��
	Tutorial = 200,
	Move = 200,
	Jump,
	Attack,
};

namespace SCREEN
{
	const int width = 1280;
	const int height = 720;
	const float scale = 1.05f;
}

namespace Back
{
	const int num = 5;			//�摜��
	const int width = 576;		//�w�i����
	const int height = 324;		//�w�i�c��
	const float scale = 2.3f;	//�w�i�g�嗦
}