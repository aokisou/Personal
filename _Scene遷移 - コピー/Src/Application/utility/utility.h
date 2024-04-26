#pragma once

//定義
#define Gravity 1		//重力
#define DefaultDir 1	//通常の向き

#define Half 2			//半分にしたいとき使う
#define Reverse -1		//反転

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

enum MapTile//IDと合わせる
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
	//敵配置
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