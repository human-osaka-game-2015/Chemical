/**
 * @file	FireGimmickCollision.h
 * @brief	火ギミック当たり判定クラス定義
 * @author	morimoto
 */
#ifndef GAME_FIREGIMMICKCOLLISION_H
#define GAME_FIREGIMMICKCOLLISION_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\GimmickCollision.h"


namespace Game
{
	/*** 火ギミック当たり判定クラス */
	class FireGimmickCollision : public GimmickCollision
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _id 当たり判定ID
		 */
		FireGimmickCollision(int _id);

		/*** デストラクタ */
		virtual ~FireGimmickCollision();

		/**
		 * Collide関数へのDispatch関数
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Dispatch(CollisionBase* _pOther);

		/*** プレイヤーオブジェクトとの当たり判定を行う */
		virtual void Collide(PlayerCollision* _pOther);

	};
}


#endif // !GAME_FIREGIMMICKCOLLISION_H
