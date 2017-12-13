/**
 * @file   RainChemical.cpp
 * @brief  RainChemicalクラスの実装
 * @author kotani
 */
#include "RainChemical.h"
#include "..\..\ChemicalFactory.h"
#include "Application\Scene\GameScene\GameDefine.h"
#include "Application\Scene\GameScene\CollisionManager\CollisionManager.h"
#include "..\..\..\..\..\GameDataManager\GameDataManager.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"

namespace Game
{
	namespace
	{
		ChemicalBase* CreateRainChemical(int _textureIndex)
		{
			ChemicalBase* pChemical = new RainChemical(_textureIndex);
			pChemical->Initialize();
			return pChemical;
		}

		const bool registered = ChemicalFactory::GetInstance().
			RegisterCreateFunc(
			ChemicalFactory::Types(BLUE_CHEMICAL, YELLOW_CHEMICAL),
			CreateRainChemical);
	}


	RainChemical::RainChemical(int _textureIndex) :
		ChemicalBase(_textureIndex, RAIN_CHEMICAL)
	{
		m_Size = D3DXVECTOR2(80,80);
	}

	RainChemical::~RainChemical()
	{
	}

	void RainChemical::Update()
	{
		if (m_Acceleration > 23.f)
		{
			m_Acceleration = 23.f;
		}

		if (m_IsLeft)
		{
			m_Pos.x -= 10.f;
		}
		else
		{
			m_Pos.x += 10.f;
		}

		m_Acceleration += m_Gravity;
		m_Pos.y += m_Acceleration;

		RectangleCollisionBase::RECTANGLE RectAngle;
		RectAngle.Left = m_Pos.x - m_Size.x / 2;
		RectAngle.Top = m_Pos.y - m_Size.y / 2;
		RectAngle.Right = m_Pos.x + m_Size.x / 2;
		RectAngle.Bottom = m_Pos.y + m_Size.y / 2;
		m_pCollision->SetRect(RectAngle);
		m_pCollision->ResetCollision();
	}
}
