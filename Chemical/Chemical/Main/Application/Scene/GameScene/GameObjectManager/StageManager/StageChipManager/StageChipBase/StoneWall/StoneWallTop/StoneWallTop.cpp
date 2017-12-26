/**
 * @file	StoneWallTop.cpp
 * @brief	石壁の上部クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "StoneWallTop.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "..\..\..\StageChipManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	StoneWallTop::StoneWallTop() :
		StageChipBase(STONEWALL_COLLISION_ID, "Resource\\GameScene\\Texture\\StoneWall2.png", "StoneWallTop")
	{
	}

	StoneWallTop::~StoneWallTop()
	{
	}
}
