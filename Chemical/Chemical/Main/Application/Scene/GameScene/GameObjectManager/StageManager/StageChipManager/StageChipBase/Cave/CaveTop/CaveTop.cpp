/**
 * @file	CaveTop.cpp
 * @brief	洞窟壁の上部クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "CaveTop.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "..\..\..\StageChipManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	CaveTop::CaveTop() :
		StageChipBase(CAVE_COLLISION_ID, "Resource\\GameScene\\Texture\\Cave2.png", "CaveTop")
	{
	}

	CaveTop::~CaveTop()
	{
	}
}
