#pragma once

class BaseObject;
class Map;

class MapHit
{
public:
	MapHit(){}
	~MapHit(){}

	void MapObjHit(int _s, int _e, Map* _map,BaseObject* _obj);
private:
};