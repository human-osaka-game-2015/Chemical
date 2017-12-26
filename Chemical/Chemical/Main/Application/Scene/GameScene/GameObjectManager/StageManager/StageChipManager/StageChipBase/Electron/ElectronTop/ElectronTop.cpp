/**
 * @file	ElectronTop.cpp
 * @brief	塔壁の上部クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ElectronTop.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "..\..\..\StageChipManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	ElectronTop::ElectronTop() :
		StageChipBase(ELECTRON_COLLISION_ID, "Resource\\GameScene\\Texture\\Electron2.png", "ElectronTop")
	{
	}

	ElectronTop::~ElectronTop()
	{
	}
}
