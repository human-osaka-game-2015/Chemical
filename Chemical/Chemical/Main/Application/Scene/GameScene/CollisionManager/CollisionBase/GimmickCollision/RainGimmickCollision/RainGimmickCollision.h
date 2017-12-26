/**
 * @file	RainGimmickCollision.h
 * @brief	雨ギミック当たり判定クラス定義
 * @author	morimoto
 */
#ifndef GAME_RAINGIMMICKCOLLISION_H
#define GAME_RAINGIMMICKCOLLISION_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\GimmickCollision.h"


namespace Game
{
	/*** 雨ギミック当たり判定クラス */
	class RainGimmickCollision : public GimmickCollision
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _id 当たり判定ID
		 */
		RainGimmickCollision(int _id);

		/*** デストラクタ */
		~RainGimmickCollision();

		/**
		 * Collide関数へのDispatch関数
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Dispatch(CollisionBase* _pOther);

		/*** ギミックオブジェクトとの当たり判定を行う */
		virtual void Collide(GimmickCollision* _pOther);

		/*** プレイヤーオブジェクトとの当たり判定を行う */
		virtual void Collide(PlayerCollision* _pOther);

	};
}


#endif // !GAME_RAINGIMMICKCOLLISION_H
