/**
 * @file	WallTop.cpp
 * @brief	塔壁の上部クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "WallTop.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "..\..\..\StageChipManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	WallTop::WallTop() :
		StageChipBase(WALL_COLLISION_ID, "Resource\\GameScene\\Texture\\Wall2.png", "WallTop")
	{
	}

	WallTop::~WallTop()
	{
	}
}
