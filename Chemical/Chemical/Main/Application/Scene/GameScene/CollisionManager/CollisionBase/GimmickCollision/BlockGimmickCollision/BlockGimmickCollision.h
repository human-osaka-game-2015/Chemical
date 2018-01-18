/**
 * @file	BlockGimmickCollision.h
 * @brief	ブロックギミック当たり判定定義
 * @author	morimoto
 */
#ifndef GAME_BLOCKGIMMICKCOLLISION_H
#define GAME_BLOCKGIMMICKCOLLISION_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\GimmickCollision.h"


namespace Game
{
	/*** ブロックギミック当たり判定クラス */
	class BlockGimmickCollision : public GimmickCollision
	{
	public:
		/**
		 * コンストラクタ 
		 * @param[in] _id 当たり判定ID
		 */
		BlockGimmickCollision(int _id);

		/*** デストラクタ */
		virtual ~BlockGimmickCollision();

		/**
		 * Collide関数へのDispatch関数
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Dispatch(CollisionBase* _pOther);

		/*** 活性状態フラグ設定 */
		void SetIsActive(bool _isActive){ m_IsActives = _isActive; }

		/*** 活性状態フラグ取得 */
		bool GetIsActive(){ return m_IsActives; }

	private:
		bool	m_IsActives;	//!< 当たり判定が活性状態か.

	};
}


#endif // !GAME_BLOCKGIMMICKCOLLISION_H
