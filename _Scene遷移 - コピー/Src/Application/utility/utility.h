#pragma once

//’è‹`
#define Gravity 1		//d—Í
#define DefaultDir 1	//’Êí‚ÌŒü‚«

#define Half 2			//”¼•ª‚É‚µ‚½‚¢‚Æ‚«g‚¤
#define Reverse -1		//”½“]

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

enum MapTile//ID‚Æ‡‚í‚¹‚é
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
	//“G”z’u
	MTSlime = 100,
	MTWolf,
	MTOrc,
	MTBee
};

namespace SCREEN
{
	const int width = 1280;
	const int height = 720;
	const float scale = 1.05f;
}

namespace Back
{
	const int Num = 5;			//‰æ‘œ”
	const int Width = 576;		//”wŒi‰¡•
	const int Height = 324;		//”wŒic•
	const float Scale = 2.3f;	//”wŒiŠg‘å—¦
}