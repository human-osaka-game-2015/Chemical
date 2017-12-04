/**
 * @file	RecoveryGimmickCollision.h
 * @brief	回復ギミック当たり判定クラス定義
 * @author	morimoto
 */
#ifndef GAME_RECOVERYGIMMICKCOLLISION_H
#define GAME_RECOVERYGIMMICKCOLLISION_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\GimmickCollision.h"


namespace Game
{
	/*** 回復ギミッククラス */
	class RecoveryGimmickCollision : public GimmickCollision
	{
	public:
		/**
		 * コンストラクタ 
		 * @param[in] _id 当たり判定ID
		 */
		RecoveryGimmickCollision(int _id);

		/*** デストラクタ */
		virtual ~RecoveryGimmickCollision();

		/**
		 * Collide関数へのDispatch関数
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Dispatch(CollisionBase* _pOther);

		/*** プレイヤーオブジェクトとの当たり判定を行う */
		virtual void Collide(PlayerCollision* _pOther);

	};
}


#endif // !GAME_RECOVERYGIMMICKCOLLISION_H
