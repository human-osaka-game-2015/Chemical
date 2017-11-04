/**
 * @file	SoilGroundTop.cpp
 * @brief	土の上部クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "SoilGroundTop.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "..\..\..\StageChipManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	SoilGroundTop::SoilGroundTop() :
		StageChipBase(ROAD_COLLISION_ID, "Resource\\GameScene\\Texture\\Chip12.png", "SoilGroundTop")
	{
	}

	SoilGroundTop::~SoilGroundTop()
	{
	}
}
