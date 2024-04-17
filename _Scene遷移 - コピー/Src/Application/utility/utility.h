#pragma once

//定義
#define Gravity 1			//重力
#define DefaultDir 1
//プレイヤー
#define PlySpeed 5			//プレイヤー速度
#define PlyJumpPow 30		//プレイヤーのジャンプ力
#define PlyShotInterval 6	//プレイヤーの弾を打つ感覚(Maxfps/この数値)
#define PlyMoveRange -150	//プレイヤーの移動範囲
#define PlyStartPos -210	//プレイヤーの開始Y座標
#define PlyStartHP 5		//プレイヤーの開始HP
#define PlyMaxDmgEfcCnt 20	//赤く光る時間
#define PlyBltCRX 30		//弾の出る位置を銃まで補正X座標
#define PlyBltCRY 6			//弾の出る位置を銃まで補正Y座標

#define BltSpeed 7			//弾の速度

//エネミー
#define EmyMaxDmgEfcCnt 10	//赤く光る時間

#define Half 2				//半分にしたいとき使う
#define Reverse -1			//反転

#define ChrImgSize 48		//キャラ画像サイズ
#define ChrScale 2			//キャラ拡大率

#define BltSize 3			//弾画像サイズ
#define BltScale 4			//弾拡大率

#define MapSize 64			//マップサイズ

#define ExpSize 19			//爆発画像サイズ
#define ExpOneTime 5		//一画像の時間
#define ExpNum 4			//爆発画像数

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