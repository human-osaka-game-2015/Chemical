/**
 * @file	WarpGimmickCollision.h
 * @brief	ワープギミック当たり判定クラス定義
 * @author	morimoto
 */
#ifndef GAME_WARPGIMMICKCOLLISION_H
#define GAME_WARPGIMMICKCOLLISION_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\GimmickCollision.h"


namespace Game
{
	/*** ワープギミック当たり判定クラス */
	class WarpGimmickCollision : public GimmickCollision
	{
	public:
		/**
		 * コンストラクタ 
		 * @param[in] _id 当たり判定ID
		 */
		WarpGimmickCollision(int _id);

		/*** デストラクタ */
		virtual ~WarpGimmickCollision();

		/**
		 * Collide関数へのDispatch関数
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Dispatch(CollisionBase* _pOther);

		/*** プレイヤーオブジェクトとの当たり判定を行う */
		virtual void Collide(PlayerCollision* _pOther);

	};
}


#endif // !GAME_WARPGIMMICKCOLLISION_H
