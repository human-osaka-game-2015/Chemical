/**
 * @file	ButtonGimmickCollision.cpp
 * @brief	ボタン当たり判定クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ButtonGimmickCollision.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	ButtonGimmickCollision::ButtonGimmickCollision(int _id) : 
		GimmickCollision(_id)
	{
	}

	ButtonGimmickCollision::~ButtonGimmickCollision()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void ButtonGimmickCollision::Dispatch(CollisionBase* _pOther)
	{
		_pOther->Collide(this);
	}
}
