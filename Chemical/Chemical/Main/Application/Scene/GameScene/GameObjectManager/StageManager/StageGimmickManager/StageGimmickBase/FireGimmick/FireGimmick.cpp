/**
 * @file	FireGimmick.cpp
 * @brief	炎ギミッククラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "FireGimmick.h"

#include "..\..\StageGimmickManager.h"
#include "..\..\..\..\GameDataManager\GameDataManager.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	FireGimmick::FireGimmick() : 
		StageGimmickBase(EMPTY_COLLISION_ID, "Resource\\GameScene\\Texture\\Gimmick0.png", "FireGimmick")
	{
	}

	FireGimmick::~FireGimmick()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void FireGimmick::Update()
	{
		D3DXVECTOR2 ScreenPos = SINGLETON_INSTANCE(GameDataManager)->GetScreenPos();

		m_pMultipleVertex->WriteConstantBuffer(-ScreenPos);
	}

	void FireGimmick::Draw()
	{
		if (m_GimmickNum == 0) return;
		m_pMultipleVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pMultipleVertex->DefaultDraw(&m_Positions[0]);
	}

	void FireGimmick::AddGimmick(int _x, int _y)
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

	void FireGimmick::ClearChip()
	{
		m_Rectangles.clear();
		m_Positions.clear();
	}
}
