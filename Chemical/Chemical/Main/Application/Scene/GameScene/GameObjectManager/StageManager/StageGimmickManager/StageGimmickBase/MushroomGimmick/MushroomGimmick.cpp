/**
 * @file	MushroomGimmick.cpp
 * @brief	キノコギミッククラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "MushroomGimmick.h"

#include "..\..\StageGimmickManager.h"
#include "..\..\..\..\GameDataManager\GameDataManager.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	MushroomGimmick::MushroomGimmick() :
		StageGimmickBase(EMPTY_COLLISION_ID, "Resource\\GameScene\\Texture\\Gimmick1.png", "MushroomGimmick")
	{
	}

	MushroomGimmick::~MushroomGimmick()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void MushroomGimmick::Update()
	{
		D3DXVECTOR2 ScreenPos = SINGLETON_INSTANCE(GameDataManager)->GetScreenPos();

		m_pMultipleVertex->WriteConstantBuffer(-ScreenPos);
	}

	void MushroomGimmick::Draw()
	{
		if (m_GimmickNum == 0) return;
		m_pMultipleVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pMultipleVertex->DefaultDraw(&m_Positions[0]);
	}

	void MushroomGimmick::AddGimmick(int _x, int _y)
	{
		float X = StageGimmickManager::m_DefaultGimmickSize.x;
		float Y = StageGimmickManager::m_DefaultGimmickSize.y;

		D3DXVECTOR2 Pos(_x * X + X / 2, _y * Y + Y / 2);

		RECTANGLE Rect(
			Pos.x - X / 2,
			Pos.y - Y / 2,
			Pos.x + X / 2,
			Pos.y + Y / 2);

		m_Positions.emplace_back(Pos);
		m_Rectangles.emplace_back(Rect);
		m_pCollision->AddRect(Rect);
		m_GimmickNum++;	// ギミックの個数をカウント.
	}

	void MushroomGimmick::ClearChip()
	{
		m_Rectangles.clear();
		m_Positions.clear();
	}
}
