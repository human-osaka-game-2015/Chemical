/**
 * @file	SoilGroundTopRightSide.cpp
 * @brief	土の上部右端クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "SoilGroundTopRightSide.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "..\..\..\StageChipManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	SoilGroundTopRightSide::SoilGroundTopRightSide() :
		StageChipBase(ROAD_COLLISION_ID, "Resource\\GameScene\\Texture\\Chip16.png", "SoilGroundTopLeftSide")
	{
		m_Size = D3DXVECTOR2(80, 80);
	}

	SoilGroundTopRightSide::~SoilGroundTopRightSide()
	{
	}
}
