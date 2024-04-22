#pragma once

class BaseObject
{
public:
	BaseObject() {}
	virtual ~BaseObject() {}

	virtual void Init() = 0;
	virtual void Action() = 0;
	virtual void Update(float _scrollX) = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;

	//数値
	virtual Math::Vector2 GetPos() { return m_pos; }
	virtual Math::Vector2 GetFuturePos() { return m_pos + m_move; }
	virtual int GetHalfSize()final;

	//画像のスペース
	virtual int GetSpaceWidthImg() { return 0; }
	virtual int GetSpaceHeightImg() { return 0; }

	virtual void MapHitX(float _posX, float _moveX);
	virtual void MapHitY(float _posY, float _moveY, bool _b);

	//生存フラグ
	virtual void SetFalseAlive() { m_bAlive = false; }
	virtual bool GetAlive()final { return m_bAlive; }

	//当たり判定の時に弾がマップと当たったら壊れる
	virtual bool GetContent() { return false; }

protected:

	Math::Vector2 m_pos = {};
	Math::Vector2 m_move = {};
	Math::Matrix m_mat = {};
	
	int m_dir = 0;

	//画像サイズ
	int m_Size = 0;
	//画像拡大率
	int m_Scale = 0;

	bool m_bAlive = false;
private:
};