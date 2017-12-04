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

	void MushroomGimmickCollision::Collide(PlayerCollision* _pOther)
	{
		for (auto itr = m_Rectangles.begin(); itr != m_Rectangles.end(); itr++)
		{
			if ((*itr).Left  < _pOther->GetRect().Right &&
				(*itr).Right > _pOther->GetRect().Left)
			{
				if ((*itr).Top		< _pOther->GetRect().Bottom &&
					(*itr).Bottom	> _pOther->GetRect().Top)
				{
					PushCollisionData(
						COLLISION_DATA(
						PLAYER_COLLISION_ID,
						(*itr).ID));
					break;
				}
			}
		}
	}
}
