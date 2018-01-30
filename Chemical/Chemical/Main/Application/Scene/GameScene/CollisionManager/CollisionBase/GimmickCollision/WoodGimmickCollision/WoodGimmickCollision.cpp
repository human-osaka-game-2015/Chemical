/**
 * @file	WoodGimmickCollision.cpp
 * @brief	木ギミック当たり判定クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "WoodGimmickCollision.h"

#include "..\..\PlayerCollision\PlayerCollision.h"
#include "..\..\ExplosionCollision\ExplosionCollision.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	WoodGimmickCollision::WoodGimmickCollision(int _id) :
		GimmickCollision(_id)
	{
	}

	WoodGimmickCollision::~WoodGimmickCollision()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void WoodGimmickCollision::Dispatch(CollisionBase* _pOther)
	{
		_pOther->Collide(this);
	}

	void WoodGimmickCollision::Collide(ExplosionCollision* _pOther)
	{
		auto Circle = _pOther->GetCircle();
		for (auto itr = m_Rectangles.begin(); itr != m_Rectangles.end(); itr++)
		{
			if ((*itr).Left  < (Circle.Pos.x + Circle.Radius) &&
				(*itr).Right > (Circle.Pos.x - Circle.Radius))
			{
				if ((*itr).Top		< (Circle.Pos.y + Circle.Radius) &&
					(*itr).Bottom	> (Circle.Pos.y - Circle.Radius))
				{
					PushCollisionData(
						COLLISION_DATA(
							EXPLOSION_COLLISION_ID,
							(*itr).ID));
					break;
				}
			}
		}
	}
}
