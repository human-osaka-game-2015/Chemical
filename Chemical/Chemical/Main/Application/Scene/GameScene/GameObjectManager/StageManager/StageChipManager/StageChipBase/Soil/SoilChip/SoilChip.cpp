/**
 * @file	SoilChip.cpp
 * @brief	土チップクラス実装
 * @author	morimoto
 */
//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "SoilChip.h"

#include "..\..\..\StageChipManager.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	SoilChip::SoilChip() : 
		StageChipBase(SOIL_COLLISION_ID, "Resource\\GameScene\\Texture\\Chip11.png", "SoilChip")
	{
	}

	SoilChip::~SoilChip()
	{
	}
}
