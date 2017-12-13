/**
 * @file	SeaTop.cpp
 * @brief	水中ブロックの上部クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "SeaTop.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	SeaTop::SeaTop() :
		StageChipBase(SEA_COLLISION_ID, "Resource\\GameScene\\Texture\\Sea2.png", "SeaTop")
	{
	}

	SeaTop::~SeaTop()
	{
	}
}
