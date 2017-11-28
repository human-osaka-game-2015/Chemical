/**
 * @file	RectangleCollisionBase.cpp
 * @brief	矩形衝突判定オブジェクト基底クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "RectangleCollisionBase.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	RectangleCollisionBase::RectangleCollisionBase(int _id) :
		CollisionBase(_id)
	{
	}

	RectangleCollisionBase::~RectangleCollisionBase()
	{
	}
}
