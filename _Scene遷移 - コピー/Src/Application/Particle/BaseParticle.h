#pragma once

class BaseObject;

class BaseParticle
{
public:
	BaseParticle(){}
	~BaseParticle(){}

	virtual void Update() = 0;
	virtual void Draw() = 0;
	void Init(BaseObject* _obj, std::string _file);
	void Release();

protected:
	BaseObject* m_pOwner;

	Math::Matrix m_mat;
	KdTexture m_tex;
};