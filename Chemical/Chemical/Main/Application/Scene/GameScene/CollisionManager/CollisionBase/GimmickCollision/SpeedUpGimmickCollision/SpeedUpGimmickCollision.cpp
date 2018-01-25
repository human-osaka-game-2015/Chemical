/**
* @file	  SpeedUpGimmickCollision.cpp
* @brief  移動速度上昇判定クラス実装
* @author kotani
*/

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "SpeedUpGimmickCollision.h"

#include "..\..\PlayerCollision\PlayerCollision.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------

	SpeedUpGimmickCollision::SpeedUpGimmickCollision(int _id) :
		GimmickCollision(_id)
	{
	}

	SpeedUpGimmickCollision::~SpeedUpGimmickCollision()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------

	void SpeedUpGimmickCollision::Dispatch(CollisionBase* _pOther)
	{
		_pOther->Collide(this);
	}

	void SpeedUpGimmickCollision::Collide(PlayerCollision* _pOther)
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
