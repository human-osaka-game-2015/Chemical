/**
 * @file	RectangleCollision.cpp
 * @brief	矩形衝突判定オブジェクトクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "RectangleCollision.h"

#include "..\EmptyCollision\EmptyCollision.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	RectangleCollision::RectangleCollision(int _id) :
		CollisionBase(_id)
	{
	}

	RectangleCollision::~RectangleCollision()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void RectangleCollision::Dispatch(CollisionBase* _pOther)
	{
		_pOther->Collide(this);
	}

	void RectangleCollision::Collide(EmptyCollision* _pOther)
	{
	}

	void RectangleCollision::Collide(RectangleCollision* _pOther)
	{
		// 矩形同士の衝突判定.
		if (m_Rect.Left  < _pOther->m_Rect.Right &&
			m_Rect.Right > _pOther->m_Rect.Left)
		{
			if (m_Rect.Top		< _pOther->m_Rect.Bottom &&
				m_Rect.Bottom	> _pOther->m_Rect.Top)
			{
				// 衝突していた場合IDをキューにプッシュ.
				_pOther->PushOtherID(GetCollisionID());
				PushOtherID(_pOther->GetCollisionID());
			}
		}
	}

	void RectangleCollision::Collide(ChipCollision* _pOther)
	{
	}
}
