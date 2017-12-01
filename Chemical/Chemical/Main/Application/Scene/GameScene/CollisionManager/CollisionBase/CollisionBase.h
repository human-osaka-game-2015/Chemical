/**
 * @file	CollisionBase.h
 * @brief	当たり判定基底クラス定義
 * @author	morimoto
 */
#ifndef GAME_COLLISIONBASE_H
#define GAME_COLLISIONBASE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\GameDefine.h"

#include <queue>


namespace Game
{
	class EmptyCollision;
	class ChipCollision;
	class GimmickCollision;
	class PlayerCollision;
	class ChemicalCollision;

	/*** 当たり判定基底クラス */
	class CollisionBase
	{
	public:
		/**
		 * コンストラクタ 
		 * @param[in] _id 当たり判定ID
		 */
		CollisionBase(int _id);

		/*** デストラクタ */
		virtual ~CollisionBase();

		/**
		 * Collide関数へのDispatch関数
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Dispatch(CollisionBase* _pOther) = 0;

		/*** 空オブジェクトとの当たり判定を行う */
		virtual void Collide(EmptyCollision* _pOther);

		/*** チップオブジェクトとの当たり判定を行う */
		virtual void Collide(ChipCollision* _pOther);

		/*** ギミックオブジェクトとの当たり判定を行う */
		virtual void Collide(GimmickCollision* _pOther);

		/*** プレイヤーオブジェクトとの当たり判定を行う */
		virtual void Collide(PlayerCollision* _pOther);

		/*** 薬品との当たり判定を行う */
		virtual void Collide(ChemicalCollision* _pOther);

		/**
		 * 当たり判定ID取得
		 * @return 当たり判定ID
		 */
		int GetCollisionID() { return m_CollisionID; }

	private:
		static unsigned int m_CollisionBaseNum;	//!< 当たり判定オブジェクトの数.

		int					m_CollisionID;	//!< 当たり判定オブジェクトID.
		int					m_ID;			//!< ユニークID.

	};
}


#endif // !GAME_COLLISIONBASE_H
