/**
 * @file	GimmickCollision.cpp
 * @brief	ギミック当たり判定クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "GimmickCollision.h"

#include "..\RectangleCollision\RectangleCollision.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	GimmickCollision::GimmickCollision(int _id) : 
		CollisionBase(_id)
	{
	}

	GimmickCollision::~GimmickCollision()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void GimmickCollision::Dispatch(CollisionBase* _pOther)
	{
		_pOther->Collide(this);
	}

	void GimmickCollision::Collide(EmptyCollision* _pOther)
	{
	}

	void GimmickCollision::Collide(RectangleCollision* _pOther)
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

	void GimmickCollision::Collide(ChipCollision* _pOther)
	{
	}

	void GimmickCollision::Collide(PlayerCollision* _pOther)
	{
	}
}
