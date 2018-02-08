/**
 * @file   ExplosionCollision.cpp
 * @brief  ExplosionCollisionクラスの実装
 * @author kotani
 */
#include "ExplosionCollision.h"

namespace Game
{
	ExplosionCollision::ExplosionCollision(int _id) :
		CollisionBase(_id)
	{
	}


	ExplosionCollision::~ExplosionCollision()
	{
	}

	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------

	void ExplosionCollision::Dispatch(CollisionBase* _pOther)
	{
		_pOther->Collide(this);
	}
}
