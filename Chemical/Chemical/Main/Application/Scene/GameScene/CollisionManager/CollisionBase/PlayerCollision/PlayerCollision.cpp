/**
 * @file   PlayerCollision.cpp
 * @brief  PlayerCollisionクラスのcppファイル
 * @author kotani
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "PlayerCollision.h"
#include "..\ChipCollision\ChipCollision.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	PlayerCollision::PlayerCollision() :
		RectangleCollisionBase(PLAYER_COLLISION_ID),
		m_CollisionDiff(D3DXVECTOR2(0,0))
	{
	}

	PlayerCollision::~PlayerCollision()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void PlayerCollision::Dispatch(CollisionBase* _pOther)
	{
		_pOther->Collide(this);
	}

	void PlayerCollision::Collide(ChipCollision* _pOther)
	{
		// 衝突判定.
		std::vector<ChipCollision::RECTANGLE> Rect = *_pOther->GetRect();

		for (const auto& itr : Rect)
		{
			if (itr.Left  < GetRect().Right - 30 &&
				itr.Right > GetRect().Left + 30 &&
				itr.Top		< GetRect().Bottom &&
				itr.Bottom	> GetRect().Top &&
				_pOther->GetCollisionID() == SOIL_COLLISION_ID)
			{
				if (itr.Bottom >= GetRect().Bottom &&
					itr.Top >= GetRect().Top)
				{
					m_CollisionDiff.y = itr.Top - GetRect().Bottom;
				}
				else
				{
					m_CollisionDiff.y = itr.Bottom - GetRect().Top;
				}
				break;
			}
		}

		for (const auto& itr : Rect)
		{
			if (itr.Left  < GetRect().Right &&
				itr.Right > GetRect().Left &&
				itr.Top	  < GetRect().Bottom - abs(m_CollisionDiff.y) - 1 &&
				itr.Bottom > GetRect().Top + abs(m_CollisionDiff.y) + 1 &&
				_pOther->GetCollisionID() == SOIL_COLLISION_ID)
			{
				if (itr.Right >= GetRect().Right &&
					itr.Left >= GetRect().Left)
				{
					m_CollisionDiff.x = itr.Left - GetRect().Right;
				}
				else
				{
					m_CollisionDiff.x = itr.Right - GetRect().Left;
				}
				break;
			}
		}
	}
}
