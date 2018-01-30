/**
 * @file	WoodGimmickCollision.h
 * @brief	木ギミック当たり判定クラス定義
 * @author	morimoto
 */
#ifndef GAME_WOODGIMMICKCOLLISION_H
#define GAME_WOODGIMMICKCOLLISION_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\GimmickCollision.h"


namespace Game
{
	/*** 木ギミック当たり判定クラス */
	class WoodGimmickCollision : public GimmickCollision
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _id 当たり判定ID
		 */
		WoodGimmickCollision(int _id);

		/*** デストラクタ */
		virtual ~WoodGimmickCollision();

		/**
		 * Collide関数へのDispatch関数
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Dispatch(CollisionBase* _pOther);

		/*** 爆発オブジェクトとの当たり判定を行う */
		virtual void Collide(ExplosionCollision* _pOther);

	};
}


#endif // !GAME_WOODGIMMICKCOLLISION_H
