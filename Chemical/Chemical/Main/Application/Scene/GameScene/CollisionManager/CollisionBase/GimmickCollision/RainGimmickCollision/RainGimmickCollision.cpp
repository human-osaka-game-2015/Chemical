/**
 * @file	RainGimmickCollision.cpp
 * @brief	雨ギミック当たり判定クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "RainGimmickCollision.h"

#include "..\..\ChipCollision\ChipCollision.h"
#include "..\..\GimmickCollision\GimmickCollision.h"
#include "..\..\PlayerCollision\PlayerCollision.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	RainGimmickCollision::RainGimmickCollision(int _id) : 
		GimmickCollision(_id)
	{
	}

	RainGimmickCollision::~RainGimmickCollision()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void RainGimmickCollision::Dispatch(CollisionBase* _pOther)
	{
		_pOther->Collide(this);
	}

	void RainGimmickCollision::Collide(GimmickCollision* _pOther)
	{
	}

	void RainGimmickCollision::Collide(PlayerCollision* _pOther)
	{
	}
}
