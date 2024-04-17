#pragma once

class BaseObject
{
public:
	BaseObject() {}
	virtual ~BaseObject() {}

	virtual void Init();
	virtual void Action();
	virtual void Update();
	virtual void Draw();

	virtual void SetTexture(KdTexture* a_tex)final { m_tex = a_tex; }

	//���l
	virtual Math::Vector2 GetPos() { return m_pos; }
	virtual Math::Vector2 GetFuturePos() { return m_pos + m_move; }
	virtual Math::Matrix GetMat() { return m_mat; }
	virtual int GetHalfSize();

	virtual void MapHitX(float _posX, float _moveX);
	virtual void MapHitY(float _posY, float _moveY, bool _b);

	//�����t���O
	virtual void DisableAlive() { m_bAlive = false; }
	virtual bool GetbAlive()final { return m_bAlive; }

protected:
	virtual void Release();

	Math::Vector2 m_pos;
	Math::Vector2 m_move;
	Math::Matrix m_mat;
	
	int m_dir;

	//�摜�T�C�Y
	int m_Size;
	//�摜�g�嗦
	int m_Scale;

	bool m_bAlive;

	KdTexture* m_tex;
private:
};