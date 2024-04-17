#pragma once

class BaseObject;
class Map;

class MapHit
{
public:
	MapHit(){}
	~MapHit(){}

	void MapObjHit(Map* m_map,BaseObject* _obj);
private:
};