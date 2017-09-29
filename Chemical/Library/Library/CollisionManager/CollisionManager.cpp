/**
 * @file	CollisionManager.cpp
 * @brief	衝突判定管理クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "CollisionManager.h"

#include "CollisionBase\CollisionQuad2D\CollisionQuad2D.h"

#include <algorithm>


namespace Lib
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	CollisionManager::CollisionManager()
	{
	}

	CollisionManager::~CollisionManager()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void CollisionManager::Run()
	{
		for (unsigned int i = 0; i < m_pQuadCollision.size(); i++)
		{
			for (unsigned int j = i + 1; j < m_pQuadCollision.size(); j++)
			{
				if (m_pQuadCollision[i]->GetFilter() & m_pQuadCollision[j]->GetFilter())
				{
					CollisionCheck(m_pQuadCollision[i], m_pQuadCollision[j]);
				}
			}
		}
	}

	void CollisionManager::AddCollision(CollisionQuad2D* _pCollision)
	{
		m_pQuadCollision.push_back(_pCollision);
	}

	void CollisionManager::RemoveCollision(CollisionQuad2D* _pCollision)
	{
		m_pQuadCollision.erase(
			std::remove(m_pQuadCollision.begin(), m_pQuadCollision.end(), _pCollision),
			m_pQuadCollision.end());
	}


	//----------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------
	void CollisionManager::CollisionCheck(CollisionQuad2D* _pCollision1, CollisionQuad2D* _pCollision2)
	{
		D3DXVECTOR2 Pos1 = _pCollision1->GetPos();
		D3DXVECTOR2 Pos2 = _pCollision2->GetPos();

		D3DXVECTOR2 Size1 = _pCollision1->GetSize();
		D3DXVECTOR2 Size2 = _pCollision2->GetSize();

		// 衝突しているかチェック.
		if ((Pos1.x - Size1.x / 2) < (Pos2.x + Size2.x / 2) &&
			(Pos1.x + Size1.x / 2) > (Pos2.x - Size2.x / 2))
		{
			if ((Pos1.y - Size1.y / 2) < (Pos2.y + Size2.y / 2) &&
				(Pos1.y + Size1.y / 2) > (Pos2.y - Size2.y / 2))
			{
				CollisionQuad2D::COLLISION_INFO Info1, Info2;

				Info1.pName = _pCollision1->GetName();
				Info2.pName = _pCollision2->GetName();
				Info1.HitData = 0;
				Info2.HitData = 0;

				if ((Pos1.x - Size1.x / 2) < (Pos2.x - Size2.x / 2))
				{
					Info1.HitData |= CollisionQuad2D::RIGHT_HIT;
					Info2.HitData |= CollisionQuad2D::LEFT_HIT;
				}

				if ((Pos1.x + Size1.x / 2) > (Pos2.x + Size2.x / 2))
				{
					Info1.HitData |= CollisionQuad2D::LEFT_HIT;
					Info2.HitData |= CollisionQuad2D::RIGHT_HIT;
				}

				if ((Pos1.y - Size1.y / 2) < (Pos2.y - Size2.y / 2))
				{
					Info1.HitData |= CollisionQuad2D::BOTTOM_HIT;
					Info2.HitData |= CollisionQuad2D::TOP_HIT;
				}

				if ((Pos1.y + Size1.y / 2) > (Pos2.y + Size2.y / 2))
				{
					Info1.HitData |= CollisionQuad2D::TOP_HIT;
					Info2.HitData |= CollisionQuad2D::BOTTOM_HIT;
				}

				_pCollision1->AddCollisionInfo(&Info1);
				_pCollision2->AddCollisionInfo(&Info2);
			}
		}
	}
}
