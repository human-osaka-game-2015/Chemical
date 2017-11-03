/**
 * @file	SoilGroundTopLeftSide.cpp
 * @brief	土の上部左端クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "SoilGroundTopLeftSide.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "..\..\..\StageChipManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	SoilGroundTopLeftSide::SoilGroundTopLeftSide() :
		StageChipBase(ROAD_COLLISION_ID, "Resource\\GameScene\\Texture\\Chip8.png", "SoilGroundTopLeftSide")
	{
		m_Size = D3DXVECTOR2(80, 80);
	}

	SoilGroundTopLeftSide::~SoilGroundTopLeftSide()
	{
	}
}
