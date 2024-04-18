#pragma once

//定義
#define Gravity 1			//重力
#define DefaultDir 1
//プレイヤー
#define PlySpeed 5			//プレイヤー速度
#define PlyJumpPow 20		//プレイヤーのジャンプ力
#define PlyShotInterval 6	//プレイヤーの弾を打つ感覚(Maxfps/この数値)
#define PlyMoveRange -150	//プレイヤーの移動範囲
#define PlyStartPosX -600	//プレイヤーの開始X座標
#define PlyStartPosY -210	//プレイヤーの開始Y座標
#define PlyStartHP 5		//プレイヤーの開始HP
#define PlyMaxDmgEfcCnt 20	//赤く光る時間
#define PlyBltCRX 30		//弾の出る位置を銃まで補正X座標
#define PlyBltCRY 6			//弾の出る位置を銃まで補正Y座標

#define BltSpeed 7			//弾の速度

#define Half 2				//半分にしたいとき使う
#define Reverse -1			//反転

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