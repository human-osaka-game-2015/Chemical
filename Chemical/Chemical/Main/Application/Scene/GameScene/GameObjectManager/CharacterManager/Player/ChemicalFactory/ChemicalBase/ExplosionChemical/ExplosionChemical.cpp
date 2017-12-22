/**
 * @file   ExplosionChemical.cpp
 * @brief  ExplosionChemicalクラスの実装
 * @author kotani
 */
#include "ExplosionChemical.h"
#include "..\..\ChemicalFactory.h"
#include "Application\Scene\GameScene\GameDefine.h"
#include "Application\Scene\GameScene\CollisionManager\CollisionManager.h"
#include "..\..\..\..\..\GameDataManager\GameDataManager.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"


namespace Game
{
	namespace
	{
		ChemicalBase* CreateExplosionChemical(int _textureIndex)
		{
			ChemicalBase* pChemical = new ExplosionChemical(_textureIndex);
			pChemical->Initialize();
			return pChemical;
		}

		const bool registered = ChemicalFactory::GetInstance().
			RegisterCreateFunc(
			ChemicalFactory::Types(CHEMICAL_BLUE, CHEMICAL_RED),
			CreateExplosionChemical);
	}

	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------

	ExplosionChemical::ExplosionChemical(int _textureIndex) :
		ChemicalBase(_textureIndex, CHEMICAL_EXPLOSION)
	{
		m_Size = D3DXVECTOR2(80,80);
	}

	ExplosionChemical::~ExplosionChemical()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------

	void ExplosionChemical::Update()
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
