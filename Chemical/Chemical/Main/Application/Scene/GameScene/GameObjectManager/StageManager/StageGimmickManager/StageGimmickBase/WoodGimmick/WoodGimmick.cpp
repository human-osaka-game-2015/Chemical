/**
 * @file	WoodGimmick.cpp
 * @brief	木ギミッククラス定義
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "WoodGimmick.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	WoodGimmick::WoodGimmick() :
		StageGimmickBase(EMPTY_COLLISION_ID, "", "WoodGimmick")
	{
	}

	WoodGimmick::~WoodGimmick()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool WoodGimmick::Initialize()
	{
		return true;
	}

	void WoodGimmick::Finalize()
	{
	}
}
