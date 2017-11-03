/**
 * @file	ChipCollision.cpp
 * @brief	矩形衝突判定オブジェクトクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ChipCollision.h"

#include "..\EmptyCollision\EmptyCollision.h"
#include "..\RectangleCollision\RectangleCollision.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	ChipCollision::ChipCollision(int _id) :
		CollisionBase(_id)
	{
	}

	ChipCollision::~ChipCollision()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void ChipCollision::Dispatch(CollisionBase* _pOther)
	{
		_pOther->Collide(this);
	}

	void ChipCollision::Collide(EmptyCollision* _pOther)
	{
	}

	void ChipCollision::Collide(RectangleCollision* _pOther)
	{
		// 矩形同士の衝突判定.
		for (auto itr = m_Rectangles.begin(); itr != m_Rectangles.end(); itr++)
		{
			if ((*itr).Left  < _pOther->GetRect().Right &&
				(*itr).Right > _pOther->GetRect().Left)
			{
				if ((*itr).Top		< _pOther->GetRect().Bottom &&
					(*itr).Bottom	> _pOther->GetRect().Top)
				{
					// 衝突していた場合IDをキューにプッシュ.
					_pOther->PushOtherID(GetCollisionID());
					break;
				}
			}
		}
	}

	void ChipCollision::Collide(ChipCollision* _pOther)
	{
	}
}
