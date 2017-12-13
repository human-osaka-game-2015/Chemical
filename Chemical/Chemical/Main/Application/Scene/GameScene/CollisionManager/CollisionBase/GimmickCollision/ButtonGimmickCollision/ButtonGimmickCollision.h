/**
 * @file	ButtonGimmickCollision.h
 * @brief	ボタン当たり判定クラス定義
 * @author	morimoto
 */
#ifndef GAME_BUTTONGIMMICKCOLLISION_H
#define GAME_BUTTONGIMMICKCOLLISION_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\GimmickCollision.h"


namespace Game
{
	/*** ボタン当たり判定クラス */
	class ButtonGimmickCollision : public GimmickCollision
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _id 当たり判定ID
		 */
		ButtonGimmickCollision(int _id);

		/*** デストラクタ */
		virtual ~ButtonGimmickCollision();

		/**
		 * Collide関数へのDispatch関数
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Dispatch(CollisionBase* _pOther);

		/*** プレイヤーオブジェクトとの当たり判定を行う */
		virtual void Collide(PlayerCollision* _pOther);

	};
}


#endif // !GAME_BUTTONGIMMICKCOLLISION_H
