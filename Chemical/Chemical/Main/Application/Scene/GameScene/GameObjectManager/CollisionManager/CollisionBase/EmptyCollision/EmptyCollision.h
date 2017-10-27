/**
 * @file	EmptyCollision.h
 * @brief	空の衝突判定オブジェクトクラス定義
 * @author	morimoto
 */
#ifndef GAME_EMPTYCOLLISION_H
#define GAME_EMPTYCOLLISION_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\CollisionBase.h"


namespace Game
{
	/*** 空の衝突判定オブジェクトクラス */
	class EmptyCollision : public CollisionBase
	{
	public:
		/*** コンストラクタ */
		EmptyCollision();

		/*** デストラクタ */
		virtual ~EmptyCollision();

		/**
		 * Collide関数へのDispatch関数
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Dispatch(CollisionBase* _pOther);

		/*** 空オブジェクトとの当たり判定を行う */
		virtual void Collide(EmptyCollision* _pOther);

		/*** 矩形オブジェクトとの当たり判定を行う */
		virtual void Collide(RectangleCollision* _pOther);

	};
}


#endif // !GAME_EMPTYCOLLISION_H
