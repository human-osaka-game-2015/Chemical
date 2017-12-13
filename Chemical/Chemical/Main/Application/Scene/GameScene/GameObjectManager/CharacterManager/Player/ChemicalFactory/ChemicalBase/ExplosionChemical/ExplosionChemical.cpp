﻿/**
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
			ChemicalFactory::Types(BLUE_CHEMICAL, RED_CHEMICAL),
			CreateExplosionChemical);
	}


	ExplosionChemical::ExplosionChemical(int _textureIndex) :
		ChemicalBase(_textureIndex, EXPLOSION_CHEMICAL)
	{
		m_Size = D3DXVECTOR2(80,80);
	}

	ExplosionChemical::~ExplosionChemical()
	{
	}

	void ExplosionChemical::Update()
	{
		if (!m_IsSprinkle) return;

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
