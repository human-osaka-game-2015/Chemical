/**
 * @file	CollisionBase.cpp
 * @brief	当たり判定基底クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "CollisionBase.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Static Private Variables
	//----------------------------------------------------------------------
	unsigned int CollisionBase::m_CollisionBaseNum = 0;


	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	CollisionBase::CollisionBase(int _id) : 
		m_CollisionID(_id)
	{
		m_ID = m_CollisionBaseNum;
		m_CollisionBaseNum++;
	}

	CollisionBase::~CollisionBase()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void CollisionBase::Collide(EmptyCollision* _pOther)
	{
	}

	void CollisionBase::Collide(RectangleCollision* _pOther)
	{
	}

	void CollisionBase::Collide(ChipCollision* _pOther)
	{
	}
}
