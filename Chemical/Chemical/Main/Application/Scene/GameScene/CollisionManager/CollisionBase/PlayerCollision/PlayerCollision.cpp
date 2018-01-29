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
#include "..\GimmickCollision\MushroomGimmickCollision\MushroomGimmickCollision.h"
#include "..\GimmickCollision\RecoveryGimmickCollision\RecoveryGimmickCollision.h"
#include "..\GimmickCollision\GateGimmickCollision\GateGimmickCollision.h"
#include "..\GimmickCollision\BlockGimmickCollision\BlockGimmickCollision.h"
#include "..\GimmickCollision\BeltConveyorGimmickCollision\BeltConveyorGimmickCollision.h"
#include "..\GimmickCollision\WarpGimmickCollision\WarpGimmickCollision.h"
#include "..\GimmickCollision\SpeedUpGimmickCollision\SpeedUpGimmickCollision.h"
#include "..\GimmickCollision\FireGimmickCollision\FireGimmickCollision.h"
#include "..\EnemyCollision\EnemyCollision.h"


namespace Game
{
	namespace
	{
		template<class Type>
		bool RectCheck(
			D3DXVECTOR2* _pCollisionDiff,
			PlayerCollision::RECTANGLE* _pPlayerRect, 
			const std::vector<Type>* _rects)
		{
			// 衝突判定.
			std::vector<Type> Rect = *_rects;
			bool result = false;

			for (const auto& itr : Rect)
			{
				if (itr.Left  < _pPlayerRect->Right - 30 &&
					itr.Right > _pPlayerRect->Left + 30 &&
					itr.Top		< _pPlayerRect->Bottom &&
					itr.Bottom	> _pPlayerRect->Top)
				{
					if (itr.Bottom >= _pPlayerRect->Bottom &&
						itr.Top >= _pPlayerRect->Top)
						_pCollisionDiff->y = itr.Top - _pPlayerRect->Bottom;
					else
						_pCollisionDiff->y = itr.Bottom - _pPlayerRect->Top;

					result = true;
					break;
				}
			}

			for (const auto& itr : Rect)
			{
				if (itr.Left  < _pPlayerRect->Right &&
					itr.Right > _pPlayerRect->Left &&
					itr.Top	  < _pPlayerRect->Bottom - abs(_pCollisionDiff->y) - 1 &&
					itr.Bottom > _pPlayerRect->Top + abs(_pCollisionDiff->y) + 1)
				{
					if (itr.Right >= _pPlayerRect->Right &&
						itr.Left >= _pPlayerRect->Left)
						_pCollisionDiff->x = itr.Left - _pPlayerRect->Right;
					else
						_pCollisionDiff->x = itr.Right - _pPlayerRect->Left;

					result = true;
					break;
				}
			}

			return result;
		}
	}

	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	PlayerCollision::PlayerCollision() :
		RectangleCollisionBase(PLAYER_COLLISION_ID),
		m_CollisionDiff(D3DXVECTOR2(0,0)),
		m_ConveyorMove(D3DXVECTOR2(0,0)),
		m_IsWarpHit(false),
		m_IsOldWarpHit(false),
		m_IsWarp(false)
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
		RectCheck<ChipCollision::RECTANGLE>(&m_CollisionDiff, &GetRect(), _pOther->GetRect());
	}

	void PlayerCollision::Collide(MushroomGimmickCollision* _pOther)
	{
		RectCheck<GimmickCollision::GIMMICK_RECTANGLE>(&m_CollisionDiff, &GetRect(), _pOther->GetRect());
	}

	void PlayerCollision::Collide(RecoveryGimmickCollision* _pOther)
	{
		if (RectCheck<GimmickCollision::GIMMICK_RECTANGLE>(&D3DXVECTOR2(0, 0), &GetRect(), _pOther->GetRect()))
		{

		}
	}

	void PlayerCollision::Collide(GateGimmickCollision* _pOther)
	{
		// 衝突判定.
		std::vector<GimmickCollision::GIMMICK_RECTANGLE>* pRects = _pOther->GetRect();
		std::vector<BYTE>* pIsActives = _pOther->GetIsActive();
		int count = 0;
		for (const auto& itr : *pRects)
		{
			if (itr.Left  < GetRect().Right - 30 &&
				itr.Right > GetRect().Left + 30 &&
				itr.Top		< GetRect().Bottom &&
				itr.Bottom	> GetRect().Top &&
				(*pIsActives)[count])
			{
				if (itr.Bottom >= GetRect().Bottom &&
					itr.Top >= GetRect().Top)
					m_CollisionDiff.y = itr.Top - GetRect().Bottom;
				else
					m_CollisionDiff.y = itr.Bottom - GetRect().Top;

				break;
			}
			count++;
		}

		count = 0;
		for (const auto& itr : *pRects)
		{
			if (itr.Left  < GetRect().Right &&
				itr.Right > GetRect().Left &&
				itr.Top	  < GetRect().Bottom - abs(m_CollisionDiff.y) - 1 &&
				itr.Bottom > GetRect().Top + abs(m_CollisionDiff.y) + 1 &&
				(*pIsActives)[count])
			{
				if (itr.Right >= GetRect().Right &&
					itr.Left >= GetRect().Left)
					m_CollisionDiff.x = itr.Left - GetRect().Right;
				else
					m_CollisionDiff.x = itr.Right - GetRect().Left;

				break;
			}
			count++;
		}
	}

	void PlayerCollision::Collide(BlockGimmickCollision* _pOther)
	{
		// 衝突判定.
		std::vector<GimmickCollision::GIMMICK_RECTANGLE>* pRects = _pOther->GetRect();

		for (const auto& itr : *pRects)
		{
			if (itr.Left  < GetRect().Right - 30 &&
				itr.Right > GetRect().Left + 30 &&
				itr.Top		< GetRect().Bottom &&
				itr.Bottom	> GetRect().Top &&
				_pOther->GetIsActive())
			{
				if (itr.Bottom >= GetRect().Bottom &&
					itr.Top >= GetRect().Top)
					m_CollisionDiff.y = itr.Top - GetRect().Bottom;
				else
					m_CollisionDiff.y = itr.Bottom - GetRect().Top;

				break;
			}
		}

		for (const auto& itr : *pRects)
		{
			if (itr.Left  < GetRect().Right &&
				itr.Right > GetRect().Left &&
				itr.Top	  < GetRect().Bottom - abs(m_CollisionDiff.y) - 1 &&
				itr.Bottom > GetRect().Top + abs(m_CollisionDiff.y) + 1 &&
				_pOther->GetIsActive())
			{
				if (itr.Right >= GetRect().Right &&
					itr.Left >= GetRect().Left)
					m_CollisionDiff.x = itr.Left - GetRect().Right;
				else
					m_CollisionDiff.x = itr.Right - GetRect().Left;

				break;
			}
		}
	}

	void PlayerCollision::Collide(BeltConveyorGimmickCollision* _pOther)
	{
		// 衝突判定.
		std::vector<GimmickCollision::GIMMICK_RECTANGLE>* pRects = _pOther->GetRect();
		std::vector<BYTE>* pIsLeft = _pOther->GetIsLeft();
		int count = 0;

		for (const auto& itr : *pRects)
		{
			if (itr.Left  < GetRect().Right - 30 &&
				itr.Right > GetRect().Left + 30 &&
				itr.Top		< GetRect().Bottom &&
				itr.Bottom	> GetRect().Top)
			{
				if (itr.Bottom >= GetRect().Bottom &&
					itr.Top >= GetRect().Top)
				{
					m_CollisionDiff.y = itr.Top - GetRect().Bottom;
					if ((*pIsLeft)[count])
						m_ConveyorMove.x = -10;
					else
						m_ConveyorMove.x = +10;
				}
				else
				{
					m_CollisionDiff.y = itr.Bottom - GetRect().Top;
					if ((*pIsLeft)[count])
						m_ConveyorMove.x = -10;
					else
						m_ConveyorMove.x = +10;
				}

				break;
			}
			count++;
		}

		for (const auto& itr : *pRects)
		{
			if (itr.Left  < GetRect().Right &&
				itr.Right > GetRect().Left &&
				itr.Top	  < GetRect().Bottom - abs(m_CollisionDiff.y) - 1 &&
				itr.Bottom > GetRect().Top + abs(m_CollisionDiff.y) + 1)
			{
				if (itr.Right >= GetRect().Right &&
					itr.Left >= GetRect().Left)
					m_CollisionDiff.x = itr.Left - GetRect().Right;
				else
					m_CollisionDiff.x = itr.Right - GetRect().Left;

				break;
			}
		}
	}

	void PlayerCollision::Collide(WarpGimmickCollision* _pOther)
	{
		std::vector<GimmickCollision::GIMMICK_RECTANGLE>* pRects = _pOther->GetRect();

		for (const auto& itr : *pRects)
		{
			if (itr.Left  < GetRect().Right - 30 &&
				itr.Right > GetRect().Left + 30 &&
				itr.Top		< GetRect().Bottom &&
				itr.Bottom	> GetRect().Top)
			{
				m_IsWarpHit = true;
				break;
			}
		}

		for (const auto& itr : *pRects)
		{
			if (itr.Left  < GetRect().Right &&
				itr.Right > GetRect().Left &&
				itr.Top	  < GetRect().Bottom - abs(m_CollisionDiff.y) - 1 &&
				itr.Bottom > GetRect().Top + abs(m_CollisionDiff.y) + 1)
			{
				m_IsWarpHit = true;
				break;
			}
		}

		m_IsWarp = (m_IsWarpHit && !m_IsOldWarpHit);
	}

	void PlayerCollision::Collide(SpeedUpGimmickCollision* _pOther)
	{
		std::vector<GimmickCollision::GIMMICK_RECTANGLE>* pRects = _pOther->GetRect();

		int Count = 0;
		for (const auto& itr : *pRects)
		{
			if (itr.Left  < GetRect().Right &&
				itr.Right > GetRect().Left &&
				itr.Top		< GetRect().Bottom &&
				itr.Bottom	> GetRect().Top)
			{
				PushCollisionData(
					COLLISION_DATA(
					_pOther->GetCollisionID(),
					itr.ID,
					(*_pOther->GetGrade())[Count]));
				break;
			}
			Count++;
		}
	}

	void PlayerCollision::Collide(EnemyCollision* _pOther)
	{
		if (_pOther->GetRect().Left		< GetRect().Right &&
			_pOther->GetRect().Right	> GetRect().Left &&
			_pOther->GetRect().Top		< GetRect().Bottom &&
			_pOther->GetRect().Bottom	> GetRect().Top)
		{
			m_Damage = 10;	// 敵から受けるダメージ量は固定.
		}
	}

	void PlayerCollision::Collide(FireGimmickCollision* _pOther)
	{
		std::vector<GimmickCollision::GIMMICK_RECTANGLE>* pRects = _pOther->GetRect();

		for (const auto& itr : *pRects)
		{
			if (itr.Left  < GetRect().Right - 30 &&
				itr.Right > GetRect().Left + 30 &&
				itr.Top		< GetRect().Bottom &&
				itr.Bottom	> GetRect().Top)
			{
				m_Damage = 10;	// 炎から受けるダメージ量は固定.
				break;
			}
		}
	}
}
