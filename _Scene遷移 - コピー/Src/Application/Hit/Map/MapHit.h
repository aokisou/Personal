#pragma once

class BaseObject;
class Map;

class MapHit
{
public:
	MapHit(){}
	~MapHit(){}

	void MapObjHit(int _s, int _e, Map* m_map,BaseObject* _obj);
private:
};