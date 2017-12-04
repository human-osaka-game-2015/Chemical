/**
 * @file	SoilTop.cpp
 * @brief	土の上部クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "SoilTop.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "..\..\..\StageChipManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	SoilTop::SoilTop() :
		StageChipBase(SOIL_COLLISION_ID, "Resource\\GameScene\\Texture\\Soil2.png", "SoilTop")
	{
	}

	SoilTop::~SoilTop()
	{
	}
}
