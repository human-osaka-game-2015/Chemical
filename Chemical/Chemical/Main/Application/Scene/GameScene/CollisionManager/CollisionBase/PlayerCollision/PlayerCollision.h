/**
 * @file   PlayerCollision.h
 * @brief  PlayerCollisionクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAME_PLAYER_COLLISION_H
#define GAME_PLAYER_COLLISION_H

#include "..\RectangleCollisionBase\RectangleCollisionBase.h"
#include <D3DX11.h>
#include <D3DX10.h>

namespace Game
{
	class PlayerCollision : public RectangleCollisionBase
	{
	public:
		/*** コンストラクタ */
		PlayerCollision();

		/*** デストラクタ */
		virtual ~PlayerCollision();

		/**
		 * Collide関数へのDispatch関数
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Dispatch(CollisionBase* _pOther);

		/*** チップオブジェクトとの当たり判定を行う */
		virtual void Collide(ChipCollision* _pOther);

		/*** 当たり判定差分の初期化 */
		void ResetCollisionDiff()
		{
			m_CollisionDiff = D3DXVECTOR2(0, 0);
		}

		/**
		 * 当たり判定の差分を取得する
		 * @return _collisionDiff 当たった差分
		 */
		D3DXVECTOR2 GetCollisionDiff()
		{
			return m_CollisionDiff;
		}

	private:
		D3DXVECTOR2 m_CollisionDiff; //!< 当たった時の差分

	};
}


#endif
