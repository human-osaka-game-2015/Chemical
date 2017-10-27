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
#include "..\..\..\GameDefine.h"

#include <queue>


namespace Game
{
	class EmptyCollision;
	class RectangleCollision;

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

		/*** 矩形オブジェクトとの当たり判定を行う */
		virtual void Collide(RectangleCollision* _pOther);

		/**
		 * 当たり判定ID取得
		 * @return 当たり判定ID
		 */
		int GetCollisionID() { return m_CollisionID; }

		/**
		 * 衝突したオブジェクトのIDを取得(取得したIDはキューから削除される)
		 * @return 衝突したオブジェクトID
		 */
		int PopOtherID()
		{
			// 空の場合はエラー値を返す.
			if (m_OthersID.empty()) return EMPTY_COLLISION_ID;

			int Id = m_OthersID.front();
			m_OthersID.pop();

			return Id;
		}

		/**
		 * 衝突したオブジェクトのIDを設定
		 * @param[in] _id 衝突したオブジェクトID
		 */
		void PushOtherID(int _id) { m_OthersID.push(_id); }

	private:
		static unsigned int m_CollisionBaseNum;	//!< 当たり判定オブジェクトの数.

		int					m_CollisionID;	//!< 当たり判定オブジェクトID.
		std::queue<int>		m_OthersID;		//!< 衝突したオブジェクトのIDキュー.
		int					m_ID;			//!< ユニークID.

	};
}


#endif // !GAME_COLLISIONBASE_H
