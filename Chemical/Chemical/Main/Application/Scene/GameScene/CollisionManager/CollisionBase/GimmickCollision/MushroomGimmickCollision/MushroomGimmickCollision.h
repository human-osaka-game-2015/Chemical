/**
 * @file	MushroomGimmickCollision.h
 * @brief	キノコギミック当たり判定クラス定義
 * @author	morimoto
 */
#ifndef GAME_MUSHROOMGIMMICKCOLLISION_H
#define GAME_MUSHROOMGIMMICKCOLLISION_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\GimmickCollision.h"


namespace Game
{
	/*** キノコギミック当たり判定クラス */
	class MushroomGimmickCollision : public GimmickCollision
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _id 当たり判定ID
		 */
		MushroomGimmickCollision(int _id);

		/*** デストラクタ */
		virtual ~MushroomGimmickCollision();

		/**
		 * Collide関数へのDispatch関数
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Dispatch(CollisionBase* _pOther);

		/*** 雨オブジェクトとの当たり判定を行う */
		virtual void Collide(RainGimmickCollision* _pOther);

	};
}


#endif // !GAME_MUSHROOMGIMMICKCOLLISION_H
