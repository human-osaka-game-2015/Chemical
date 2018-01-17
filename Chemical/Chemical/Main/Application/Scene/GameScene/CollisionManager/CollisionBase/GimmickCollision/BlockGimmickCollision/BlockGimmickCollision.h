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

	};
}


#endif // !GAME_BLOCKGIMMICKCOLLISION_H
