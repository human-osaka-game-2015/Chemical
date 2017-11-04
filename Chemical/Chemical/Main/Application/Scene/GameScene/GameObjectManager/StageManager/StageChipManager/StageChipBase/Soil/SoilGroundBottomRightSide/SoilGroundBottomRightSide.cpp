﻿/**
 * @file	SoilGroundBottomRightSide.cpp
 * @brief	土の下部右端クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "SoilGroundBottomRightSide.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "..\..\..\StageChipManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	SoilGroundBottomRightSide::SoilGroundBottomRightSide() :
		StageChipBase(SOIL_COLLISION_ID, "Resource\\GameScene\\Texture\\Chip14.png", "SoilGroundBottomRightSide")
	{
		m_Size = D3DXVECTOR2(80, 80);
	}

	SoilGroundBottomRightSide::~SoilGroundBottomRightSide()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void SoilGroundBottomRightSide::AddChip(int _x, int _y)
	{
		float X = StageChipManager::m_DefaultChipSize.x;
		float Y = StageChipManager::m_DefaultChipSize.y;

		D3DXVECTOR2 Pos(_x * X + X / 2, _y * Y + Y / 2);

		RECTANGLE Rect(
			Pos.x - X / 2,
			Pos.y - Y / 2,
			Pos.x + X / 2,
			Pos.y + Y / 2);

		m_Positions.emplace_back(Pos);

		m_Rectangles.emplace_back(Rect);
		m_pCollision->AddRect(Rect);
		m_ChipNum++;	// チップの個数をカウント.
	}

	void SoilGroundBottomRightSide::ClearChip()
	{
		m_Rectangles.clear();
		m_Positions.clear();
	}
}