#include "MapHit.h"
#include "Map.h"
#include "../object/BaseObject.h"

void MapHit::MapObjHit(Map* m_map, BaseObject* _obj)
{
	const float objRight = _obj->GetPos().x + _obj->GetHalfSize();
	const float objLeft = _obj->GetPos().x - _obj->GetHalfSize();
	const float objTop = _obj->GetPos().y + _obj->GetHalfSize();
	const float objBottom = _obj->GetPos().y - _obj->GetHalfSize();

	const float objNextRight = _obj->GetFuturePos().x + _obj->GetHalfSize();
	const float objNextLeft = _obj->GetFuturePos().x - _obj->GetHalfSize();
	const float objNextTop = _obj->GetFuturePos().y + _obj->GetHalfSize();
	const float objNextBottom = _obj->GetFuturePos().y - _obj->GetHalfSize();
	
	for (int i = 0; i < m_map->GetWidth(); i++)
	{
		for (int j = 0; j < m_map->GetHeight(); j++)
		{
			if (!m_map->GetMapData(i, j)) { break; }

			const float mapRight = m_map->GetPos(i,j).x + m_map->GetHalfSize();
			const float mapLeft = m_map->GetPos(i,j).x - m_map->GetHalfSize();
			const float mapTop = m_map->GetPos(i,j).y + m_map->GetHalfSize();
			const float mapBottom = m_map->GetPos(i,j).y - m_map->GetHalfSize();

			if (objRight > mapLeft && objLeft < mapRight)
			{
				if (objNextBottom < mapTop && objNextTop > mapTop)//�������W�����蔻��(��)
				{
					_obj->MapHitY(mapTop + _obj->GetHalfSize(), 0,false);
				}
				else if (objNextTop > mapBottom && objNextBottom < mapBottom)//�������W�����蔻��(��)
				{
					_obj->MapHitY(mapBottom - _obj->GetHalfSize(), 0,true);
				}
			}
			else if (objTop > mapBottom && objBottom < mapTop)
			{
				if (objNextLeft < mapRight && objNextRight > mapRight)//�������W�����蔻��(�E)
				{
					_obj->MapHitX(mapBottom + _obj->GetHalfSize(), 0);
				}
				else if (objNextRight > mapLeft && objNextLeft < mapLeft)//�������W�����蔻��(��)
				{
					_obj->MapHitX(mapBottom - _obj->GetHalfSize(), 0);
				}
			}
		}
	}
}