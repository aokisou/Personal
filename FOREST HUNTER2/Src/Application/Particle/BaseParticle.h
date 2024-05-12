#pragma once

class BaseObject;

class BaseParticle
{
public:
	BaseParticle(){}
	~BaseParticle(){}

	virtual void Update(float _scrollX) = 0;
	virtual void Draw() = 0;
	void Init(BaseObject* _obj, std::string _file);
	void Release();

	bool GetAlive() { return m_bAlive; }
protected:
	Math::Vector2 m_pos;
	Math::Vector2 m_move;

	float m_size = 0;
	int m_cnt = 0;
	bool m_bAlive = true;

	BaseObject* m_pOwner;

	Math::Matrix m_mat;
	KdTexture m_tex;
};