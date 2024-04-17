#pragma once

class BaseObject
{
public:
	BaseObject() { m_pTex = nullptr; }
	virtual ~BaseObject() {}

	virtual void Init() = 0;
	virtual void Action() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release();

	void SetTexture(KdTexture* a_tex) { m_pTex = a_tex; }

	//数値
	virtual Math::Vector2 GetPos() { return m_pos; }
	virtual Math::Vector2 GetFuturePos() { return m_pos + m_move; }
	virtual Math::Matrix GetMat() { return m_mat; }
	virtual int GetHalfSize();

	virtual void MapHitX(float _posX, float _moveX);
	virtual void MapHitY(float _posY, float _moveY, bool _b);

	//生存フラグ
	virtual void DisableAlive() { m_bAlive = false; }
	virtual bool GetbAlive()final { return m_bAlive; }

protected:

	Math::Vector2 m_pos;
	Math::Vector2 m_move;
	Math::Matrix m_mat;
	
	int m_dir;

	//画像サイズ
	int m_Size;
	//画像拡大率
	int m_Scale;

	bool m_bAlive;

	KdTexture* m_pTex;
private:
};