/**
 * @file   ExplosionChemical.cpp
 * @brief  ExplosionChemicalクラスの実装
 * @author kotani
 */
#include "ExplosionChemical.h"
#include "Application\Scene\GameScene\GameDefine.h"
#include "Application\Scene\GameScene\CollisionManager\CollisionManager.h"
#include "..\..\..\..\..\GameDataManager\GameDataManager.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"

namespace Game
{
	ExplosionChemical::ExplosionChemical(int _textureIndex, const D3DXVECTOR2&  _pos, bool _isLeft) :
		ChemicalBase(_textureIndex, _pos, _isLeft)
	{
		m_Size = D3DXVECTOR2(80,80);
	}

	ExplosionChemical::~ExplosionChemical()
	{
	}

	void ExplosionChemical::Update()
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
