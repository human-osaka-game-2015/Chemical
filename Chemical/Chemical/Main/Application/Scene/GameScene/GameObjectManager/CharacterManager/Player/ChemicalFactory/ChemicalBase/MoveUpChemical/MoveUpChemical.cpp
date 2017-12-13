/**
 * @file   MoveUpChemical.cpp
 * @brief  MoveUpChemicalクラスの実装
 * @author kotani
 */
#include "MoveUpChemical.h"
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
			ChemicalBase* pChemical = new MoveUpChemical(_textureIndex);
			pChemical->Initialize();
			return pChemical;
		}

		const bool registered = ChemicalFactory::GetInstance().
			RegisterCreateFunc(
			ChemicalFactory::Types(RED_CHEMICAL, YELLOW_CHEMICAL),
			CreateMoveUpChemical);
	}


	MoveUpChemical::MoveUpChemical(int _textureIndex) :
		ChemicalBase(_textureIndex, MOVEUP_CHEMICAL)
	{
		m_Size = D3DXVECTOR2(80,80);
	}

	MoveUpChemical::~MoveUpChemical()
	{
	}

	void MoveUpChemical::Update()
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
