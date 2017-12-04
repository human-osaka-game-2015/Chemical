/**
 * @file	GimmickCollision.cpp
 * @brief	ギミック当たり判定クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "GimmickCollision.h"

#include "..\PlayerCollision\PlayerCollision.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	GimmickCollision::GimmickCollision(int _id) : 
		CollisionBase(_id)
	{
	}

	GimmickCollision::~GimmickCollision()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void GimmickCollision::Dispatch(CollisionBase* _pOther)
	{
		_pOther->Collide(this);
	}
}
