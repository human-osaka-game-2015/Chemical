/**
 * @file	RoadChip.cpp
 * @brief	道チップクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "RoadChip.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "..\..\StageChipManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	RoadChip::RoadChip() :
		StageChipBase(ROAD_COLLISION_ID, "Resource\\GameScene\\Texture\\Road.png", "RoadChip")
	{
		m_Size = D3DXVECTOR2(80, 80);
	}

	RoadChip::~RoadChip()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void RoadChip::Update()
	{
	}

	void RoadChip::Draw()
	{
		m_pMultipleVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pMultipleVertex->DefaultDraw(&m_Positions[0]);
	}

	void RoadChip::AddChip(int _x, int _y)
	{
		float X = StageChipManager::m_DefaultChipSize.x;
		float Y = StageChipManager::m_DefaultChipSize.y;

		RECTANGLE Rect(
			_x * X,
			_y * Y / 2,
			_x * X + X,
			_y * Y + Y);

		m_Positions.emplace_back(
			_x * X + X / 2,
			_y * Y + Y / 2 + Y / 2 / 2);

		m_Rectangles.emplace_back(Rect);
		m_pCollision->AddRect(Rect);
	}

	void RoadChip::ClearChip()
	{
		m_Rectangles.clear();
		m_Positions.clear();
	}
}
