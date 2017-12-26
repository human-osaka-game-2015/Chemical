/**
 * @file	BeltConveyorGimmickCollision.cpp
 * @brief	ベルトコンベアギミック当たり判定クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "BeltConveyorGimmickCollision.h"

#include "..\..\PlayerCollision\PlayerCollision.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	BeltConveyorGimmickCollision::BeltConveyorGimmickCollision(int _id) : 
		GimmickCollision(_id)
	{
	}

	BeltConveyorGimmickCollision::~BeltConveyorGimmickCollision()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void BeltConveyorGimmickCollision::Dispatch(CollisionBase* _pOther)
	{
		_pOther->Collide(this);
	}

	void BeltConveyorGimmickCollision::Collide(PlayerCollision* _pOther)
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
