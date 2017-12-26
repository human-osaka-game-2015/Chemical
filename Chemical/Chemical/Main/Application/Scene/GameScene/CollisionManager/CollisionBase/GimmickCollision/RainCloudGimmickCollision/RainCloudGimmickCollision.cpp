/**
 * @file	RainCloudGimmickCollision.cpp
 * @brief	雨雲ギミック当たり判定クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "RainCloudGimmickCollision.h"

#include "..\..\PlayerCollision\PlayerCollision.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	RainCloudGimmickCollision::RainCloudGimmickCollision(int _id) :
		GimmickCollision(_id)
	{
	}

	RainCloudGimmickCollision::~RainCloudGimmickCollision()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void RainCloudGimmickCollision::Dispatch(CollisionBase* _pOther)
	{
		_pOther->Collide(this);
	}
}
