/**
 * @file   SpeedUpChemical.cpp
 * @brief  SpeedUpChemicalクラスの実装
 * @author kotani
 */
#include "SpeedUpChemical.h"
#include "..\..\ChemicalFactory.h"
#include "Application\Scene\GameScene\GameDefine.h"
#include "Application\Scene\GameScene\CollisionManager\CollisionManager.h"
#include "..\..\..\..\..\GameDataManager\GameDataManager.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"

namespace Game
{
	namespace
	{
		ChemicalBase* CreateMoveUpChemical(int _textureIndex)
		{
			ChemicalBase* pChemical = new SpeedUpChemical(_textureIndex);
			pChemical->Initialize();
			return pChemical;
		}

		const bool registered = ChemicalFactory::GetInstance().
			RegisterCreateFunc(
			ChemicalFactory::Types(CHEMICAL_RED, CHEMICAL_YELLOW),
			CreateMoveUpChemical);
	}


	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------

	SpeedUpChemical::SpeedUpChemical(int _textureIndex) :
		ChemicalBase(_textureIndex, CHEMICAL_MOVEUP)
	{
		m_Size = D3DXVECTOR2(80,80);
	}

	SpeedUpChemical::~SpeedUpChemical()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------

	void SpeedUpChemical::Update()
	{
		m_Acceleration = (std::min)(m_Acceleration, 23.f);

		m_Pos.x += m_IsLeft ? -10.f : 10.f;
		m_Pos.y += (m_Acceleration += m_Gravity);

		RectangleCollisionBase::RECTANGLE Rectangle(
			m_Pos.x - m_Size.x / 2,
			m_Pos.y - m_Size.y / 2,
			m_Pos.x + m_Size.x / 2,
			m_Pos.y + m_Size.y / 2);
		m_pCollision->SetRect(Rectangle);
		m_pCollision->ResetCollision();
	}
}
