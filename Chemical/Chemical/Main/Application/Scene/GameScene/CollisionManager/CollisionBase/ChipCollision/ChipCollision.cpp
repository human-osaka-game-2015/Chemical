/**
 * @file	ChipCollision.cpp
 * @brief	矩形衝突判定オブジェクトクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ChipCollision.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	ChipCollision::ChipCollision(int _id) :
		CollisionBase(_id)
	{
	}

	ChipCollision::~ChipCollision()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void ChipCollision::Dispatch(CollisionBase* _pOther)
	{
		_pOther->Collide(this);
	}
}
