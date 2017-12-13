/**
 * @file	RockTop.cpp
 * @brief	岩場の上部クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "RockTop.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "..\..\..\StageChipManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	RockTop::RockTop() :
		StageChipBase(ROCK_COLLISION_ID, "Resource\\GameScene\\Texture\\Soil2.png", "RockTop")
	{
	}

	RockTop::~RockTop()
	{
	}
}
