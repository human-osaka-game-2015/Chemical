/**
* @file   EnemyCollision.h
* @brief  エネミーコリジョンクラスの定義
* @author fujioka
*/
#ifndef GAME_ENEMY_COLLISION_H
#define GAME_ENEMY_COLLISION_H

#include <D3DX11.h>
#include <D3DX10.h>
#include "Application\Scene\GameScene\CollisionManager\CollisionBase\RectangleCollisionBase\RectangleCollisionBase.h"

namespace Game
{
	class EnemyCollision : public RectangleCollisionBase
	{
	public:

		struct DAMAGESTATE
		{
			bool	IsDamage;
			int		LiquidTtpe;
			int		Damage;
		};
		/*** コンストラクタ */
		EnemyCollision();

		/*** デストラクタ */
		virtual ~EnemyCollision();

		/**
		* Collide関数へのDispatch関数
		* @param[in] _pOther 他オブジェクト
		*/
		virtual void Dispatch(CollisionBase* _pOther);

		/*** 空オブジェクトとの当たり判定を行う */
		virtual void Collide(EmptyCollision* _pOther);

		/*** 矩形オブジェクトとの当たり判定を行う */
		virtual void Collide(RectangleCollisionBase* _pOther);

		/*** チップオブジェクトとの当たり判定を行う */
		virtual void Collide(ChipCollision* _pOther);

		virtual void Collide(PlayerCollision* _pOther);
		/**
		 * きのこと当たり判定を行う
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Collide(MushroomGimmickCollision* _pOther);

		/**
		 * 門と当たり判定を行う
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Collide(GateGimmickCollision* _pOther);

		/**
		 * ブロックとの当たり判定を行う
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Collide(BlockGimmickCollision* _pOther);

		/**
		 * ベルトコンベアとの当たり判定を行う
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Collide(BeltConveyorGimmickCollision* _pOther);

		/*** 爆発オブジェクトとの当たり判定を行う */
		virtual void Collide(ExplosionCollision* _pOther);

		/*** 当たり判定差分の初期化 */
		void ResetCollisionDiff()
		{
			m_CollisionDiff = D3DXVECTOR2(0, 0);
		}

		void ResetConveyorMove(){ m_ConveyorMove = D3DXVECTOR2(0, 0); }

		D3DXVECTOR2 GetCollisionDiff(){ return m_CollisionDiff; }

		DAMAGESTATE GetDamagestate(){ return m_DamageState; }

		D3DXVECTOR2 GetConveyorMove(){ return m_ConveyorMove; }

	private:
		D3DXVECTOR2	m_ConveyorMove;  //!< ベルトコンベアを踏んだ際の移動量
		D3DXVECTOR2 m_CollisionDiff; //!< 当たった時の差分
		DAMAGESTATE m_DamageState;
	};
}


#endif
