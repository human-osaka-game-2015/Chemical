/**
 * @file	BlockGimmickCollision.cpp
 * @brief	ブロックギミック当たり判定実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "BlockGimmickCollision.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	BlockGimmickCollision::BlockGimmickCollision(int _id) :
		GimmickCollision(_id),
		m_IsActives(true)
	{
	}

	BlockGimmickCollision::~BlockGimmickCollision()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void BlockGimmickCollision::Dispatch(CollisionBase* _pOther)
	{
		_pOther->Collide(this);
	}
}
