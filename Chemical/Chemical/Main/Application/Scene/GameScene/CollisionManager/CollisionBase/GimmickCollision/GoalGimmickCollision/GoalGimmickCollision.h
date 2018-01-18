/**
 * @file	GoalGimmickCollision.h
 * @brief	ゴールギミック当たり判定クラス定義
 * @author	morimoto
 */
#ifndef GAME_GOALGIMMICKCOLLISION_H
#define GAME_GOALGIMMICKCOLLISION_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\GimmickCollision.h"


namespace Game
{
	/*** ゴールギミック当たり判定クラス */
	class GoalGimmickCollision : public GimmickCollision
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _id 当たり判定ID
		 */
		GoalGimmickCollision(int _id);
		
		virtual ~GoalGimmickCollision();

		/**
		 * Collide関数へのDispatch関数
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Dispatch(CollisionBase* _pOther);

		/*** プレイヤーオブジェクトとの当たり判定を行う */
		virtual void Collide(PlayerCollision* _pOther);
	};
}


#endif //! GAME_GOALGIMMICKCOLLISION_H
