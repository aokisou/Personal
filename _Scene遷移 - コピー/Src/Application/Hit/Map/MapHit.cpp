#include "MapHit.h"
#include "../../Map/Map.h"
#include "../../Object/BaseObject.h"
#include "../../Utility/utility.h"

void MapHit::MapObjHit(int _s, int _e, Map* m_map, BaseObject* _obj)
{
	const float objRight	= _obj->GetPos().x + _obj->GetHalfSize() - _obj->GetSpaceWidthImg();
	const float objLeft		= _obj->GetPos().x - _obj->GetHalfSize() + _obj->GetSpaceWidthImg();
	const float objTop		= _obj->GetPos().y + _obj->GetHalfSize() - _obj->GetSpaceHeightImg();
	const float objBottom	= _obj->GetPos().y - _obj->GetHalfSize() + _obj->GetSpaceHeightImg();

	const float objNextRight	= _obj->GetFuturePos().x + _obj->GetHalfSize() - _obj->GetSpaceWidthImg();
	const float objNextLeft		= _obj->GetFuturePos().x - _obj->GetHalfSize() + _obj->GetSpaceWidthImg();
	const float objNextTop		= _obj->GetFuturePos().y + _obj->GetHalfSize() - _obj->GetSpaceHeightImg();
	const float objNextBottom	= _obj->GetFuturePos().y - _obj->GetHalfSize() + _obj->GetSpaceHeightImg();
	
	for (int i = 0; i < m_map->GetMaxHeight(); i++)
	{
		for (int j = _s; j < _e; j++)
		{
			int md;
			if ((md = m_map->GetMapData(i, j)) == none) { continue; }

			const float mapRight	= m_map->GetPos(i,j).x + m_map->GetHalfSize();
			const float mapLeft		= m_map->GetPos(i,j).x - m_map->GetHalfSize();
			const float mapTop		= m_map->GetPos(i,j).y + m_map->GetHalfSize();
			const float mapBottom	= m_map->GetPos(i,j).y - m_map->GetHalfSize();

			if (objRight > mapLeft && objLeft < mapRight)
			{
				if (objNextBottom < mapTop && objNextTop > mapTop)//未来座標当たり判定(上)
				{
					if (_obj->GetContent()) { _obj->SetFalseAlive(); }
					_obj->MapHitY(mapTop + _obj->GetHalfSize() - _obj->GetSpaceHeightImg(), 0.f, false);
				}
				else if (objNextTop > mapBottom && objNextBottom < mapBottom)//未来座標当たり判定(下)
				{
					_obj->MapHitY(mapBottom - _obj->GetHalfSize() + _obj->GetSpaceHeightImg(), 0.f,true);
				}
			}
			else if (objTop > mapBottom && objBottom < mapTop)
			{
				if (objNextLeft < mapRight && objNextRight > mapRight)//未来座標当たり判定(右)
				{
					if (_obj->GetContent()) { _obj->SetFalseAlive(); }
					_obj->MapHitX(mapRight + _obj->GetHalfSize() - _obj->GetSpaceWidthImg(), 0.f);
				}
				else if (objNextRight > mapLeft && objNextLeft < mapLeft)//未来座標当たり判定(左)
				{
					if (_obj->GetContent()) { _obj->SetFalseAlive(); }
					_obj->MapHitX(mapLeft - _obj->GetHalfSize() + _obj->GetSpaceWidthImg(), 0.f);
				}
			}
		}
	}
}