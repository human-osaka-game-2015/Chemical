/**
 * @file	MushroomGimmickCollision.cpp
 * @brief	キノコギミック当たり判定クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "MushroomGimmickCollision.h"

#include "..\..\PlayerCollision\PlayerCollision.h"
#include "..\RainGimmickCollision\RainGimmickCollision.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	MushroomGimmickCollision::MushroomGimmickCollision(int _id) : 
		GimmickCollision(_id)
	{
	}

	MushroomGimmickCollision::~MushroomGimmickCollision()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void MushroomGimmickCollision::Dispatch(CollisionBase* _pOther)
	{
		_pOther->Collide(this);
	}

	void MushroomGimmickCollision::Collide(RainGimmickCollision* _pOther)
	{
		for (auto itr = m_Rectangles.begin(); itr != m_Rectangles.end(); itr++)
		{
			auto Rect = _pOther->GetRect();
			for (auto RainGimmick : *Rect)
			{
				if ((*itr).Left  < RainGimmick.Right &&
					(*itr).Right > RainGimmick.Left)
				{
					if ((*itr).Top		< RainGimmick.Bottom &&
						(*itr).Bottom	> RainGimmick.Top)
					{
						PushCollisionData(
							COLLISION_DATA(
							RAIN_GIMMICK_COLLISION_ID,
							(*itr).ID));
						break;
					}
				}
			}
		}
	}
}
