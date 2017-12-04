/**
 * @file	RecoveryGimmickCollision.cpp
 * @brief	回復ギミック当たり判定クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "RecoveryGimmickCollision.h"

#include "..\..\PlayerCollision\PlayerCollision.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	RecoveryGimmickCollision::RecoveryGimmickCollision(int _id) : 
		GimmickCollision(_id)
	{
	}

	RecoveryGimmickCollision::~RecoveryGimmickCollision()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void RecoveryGimmickCollision::Dispatch(CollisionBase* _pOther)
	{
		_pOther->Collide(this);
	}

	void RecoveryGimmickCollision::Collide(PlayerCollision* _pOther)
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
