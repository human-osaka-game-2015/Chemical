/**
 * @file	CollisionBase.cpp
 * @brief	衝突判定オブジェクト基底クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "CollisionBase.h"


namespace Lib
{
	//----------------------------------------------------------------------
	// Static Private Variables
	//----------------------------------------------------------------------
	unsigned int CollisionBase::m_CollisionBaseCount = 0;


	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	CollisionBase::CollisionBase() :
		m_CollisionID(m_CollisionBaseCount),
		m_Filter(CHARACTER | STAGE | BACKGROUND)
	{
		m_CollisionBaseCount++;
	}

	CollisionBase::~CollisionBase()
	{
	}
}
