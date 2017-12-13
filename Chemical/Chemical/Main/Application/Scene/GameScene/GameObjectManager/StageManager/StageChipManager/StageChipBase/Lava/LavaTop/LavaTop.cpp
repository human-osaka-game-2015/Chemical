/**
 * @file	LavaTop.cpp
 * @brief	溶岩の上部クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "LavaTop.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "..\..\..\StageChipManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	LavaTop::LavaTop() :
		StageChipBase(LAVA_COLLISION_ID, "Resource\\GameScene\\Texture\\Lava2.png", "LavaTop")
	{
	}

	LavaTop::~LavaTop()
	{
	}
}
