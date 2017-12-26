/**
 * @file	Wall.cpp
 * @brief	塔壁クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Wall.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "..\..\..\StageChipManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	Wall::Wall() :
		StageChipBase(WALL_COLLISION_ID, "Resource\\GameScene\\Texture\\Wall1.png", "Wall")
	{
	}

	Wall::~Wall()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void Wall::AddChip(int _x, int _y)
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

	void Wall::ClearChip()
	{
		m_Rectangles.clear();
		m_Positions.clear();
	}
}
