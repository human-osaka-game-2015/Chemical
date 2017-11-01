/**
 * @file	SoilChip.cpp
 * @brief	土チップクラス実装
 * @author	morimoto
 */
//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "SoilChip.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	SoilChip::SoilChip() : 
		StageChipBase(SOIL_COLLISION_ID, "Resource\\GameScene\\Texture\\Soil.png", "SoilChip")
	{
		m_Size = D3DXVECTOR2(80, 80);
	}

	SoilChip::~SoilChip()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void SoilChip::Update()
	{
	}

	void SoilChip::Draw()
	{
		m_pMultipleVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pMultipleVertex->DefaultDraw(&m_Positions[0]);
	}
}
