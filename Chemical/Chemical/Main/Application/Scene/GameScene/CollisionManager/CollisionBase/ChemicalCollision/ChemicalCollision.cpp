/**
* @file   ChemicalCollision.cpp
* @brief  ChemicalCollisionクラスのcppファイル
* @author kotani
*/

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ChemicalCollision.h"
#include "..\ChipCollision\ChipCollision.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	ChemicalCollision::ChemicalCollision() :
		RectangleCollisionBase(PLAYER_COLLISION_ID),
		m_IsHit(false)
	{
	}

	ChemicalCollision::~ChemicalCollision()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void ChemicalCollision::Dispatch(CollisionBase* _pOther)
	{
		_pOther->Collide(this);
	}

	void ChemicalCollision::Collide(ChipCollision* _pOther)
	{
		// 衝突判定.
		std::vector<ChipCollision::RECTANGLE> Rect = *_pOther->GetRect();

		for (const auto& itr : Rect)
		{
			if (itr.Left  < GetRect().Right &&
				itr.Right > GetRect().Left &&
				itr.Top		< GetRect().Bottom &&
				itr.Bottom	> GetRect().Top &&
				_pOther->GetCollisionID() == SOIL_COLLISION_ID)
			{
				m_IsHit = true;
				break;
			}
		}
	}
}
