/**
* @file   EnemyCollision.h
* @brief  エネミーコリジョンクラスの実装
* @author fujioka
*/
#include "EnemyCollision.h"
#include "..\ChipCollision\ChipCollision.h"
#include "..\PlayerCollision\PlayerCollision.h"
#include "..\GimmickCollision\MushroomGimmickCollision\MushroomGimmickCollision.h"
#include "..\GimmickCollision\RecoveryGimmickCollision\RecoveryGimmickCollision.h"
#include "..\GimmickCollision\GateGimmickCollision\GateGimmickCollision.h"
#include "..\GimmickCollision\BlockGimmickCollision\BlockGimmickCollision.h"
#include "..\GimmickCollision\BeltConveyorGimmickCollision\BeltConveyorGimmickCollision.h"
#include "..\GimmickCollision\WarpGimmickCollision\WarpGimmickCollision.h"
#include "..\GimmickCollision\SpeedUpGimmickCollision\SpeedUpGimmickCollision.h"

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


	EnemyCollision::EnemyCollision() :
		RectangleCollisionBase(ENEMY_COLLISION_ID),
		m_CollisionDiff(D3DXVECTOR2(0, 0))
	{
		m_DamageState.IsDamage = false;
	}

	EnemyCollision::~EnemyCollision()
	{
	}


	//----------------------------------------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------------------------------------

	void EnemyCollision::Dispatch(CollisionBase* _pOther)
	{
		_pOther->Collide(this);
	}

	void EnemyCollision::Collide(EmptyCollision* _pOther)
	{
	}

	void EnemyCollision::Collide(RectangleCollisionBase* _pOther)
	{
	}

	void EnemyCollision::Collide(ChipCollision* _pOther)
	{
		//衝突判定
		std::vector<ChipCollision::RECTANGLE> Rect = *_pOther->GetRect();

		for (const auto& itr : Rect)
		{
			if (itr.Left  < GetRect().Right - 10 &&
				itr.Right > GetRect().Left + 10 &&
				itr.Top		< GetRect().Bottom &&
				itr.Bottom	> GetRect().Top)
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
				itr.Bottom > GetRect().Top + abs(m_CollisionDiff.y) + 1)
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

	void EnemyCollision::Collide(PlayerCollision* _pOther)
	{
		//衝突判定
		RECTANGLE Rect = _pOther->GetRect();

			if (Rect.Left	<= GetRect().Right &&
				Rect.Right	>= GetRect().Left &&
				Rect.Top	<= GetRect().Bottom &&
				Rect.Bottom	>= GetRect().Top)
			{
				m_DamageState.IsDamage = true;
				m_DamageState.LiquidTtpe = 2;
			}
			else
			{
				m_DamageState.IsDamage = false;
			}
	}

	void EnemyCollision::Collide(MushroomGimmickCollision* _pOther)
	{
		RectCheck<GimmickCollision::GIMMICK_RECTANGLE>(&m_CollisionDiff, &GetRect(), _pOther->GetRect());
	}

	void EnemyCollision::Collide(GateGimmickCollision* _pOther)
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

	void EnemyCollision::Collide(BlockGimmickCollision* _pOther)
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

	void EnemyCollision::Collide(BeltConveyorGimmickCollision* _pOther)
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
}
