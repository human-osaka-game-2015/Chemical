/**
 * @file	EmptyCollision.cpp
 * @brief	空の衝突判定オブジェクトクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EmptyCollision.h"

#include "..\RectangleCollision\RectangleCollision.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	EmptyCollision::EmptyCollision() : 
		CollisionBase(EMPTY_COLLISION_ID)
	{
	}

	EmptyCollision::~EmptyCollision()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void EmptyCollision::Dispatch(CollisionBase* _pOther)
	{
		_pOther->Collide(this);
	}

	void EmptyCollision::Collide(EmptyCollision* _pOther)
	{
	}

	void EmptyCollision::Collide(RectangleCollision* _pOther)
	{
	}

	void EmptyCollision::Collide(ChipCollision* _pOther)
	{
	}
}
