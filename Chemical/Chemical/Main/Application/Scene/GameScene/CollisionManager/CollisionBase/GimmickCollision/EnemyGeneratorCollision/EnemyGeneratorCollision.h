/**
 * @file	EnemyGeneratorCollision.h
 * @brief	エネミー生成当たり判定クラス定義
 * @author	morimoto
 */
#ifndef GAME_ENEMYGENERATORCOLLISION_H
#define GAME_ENEMYGENERATORCOLLISION_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\GimmickCollision.h"


namespace Game
{
	/*** エネミー生成当たり判定クラス */
	class EnemyGeneratorCollision : public GimmickCollision
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _id 当たり判定ID
		 */
		EnemyGeneratorCollision(int _id);

		/*** デストラクタ */
		virtual ~EnemyGeneratorCollision();

		/**
		 * Collide関数へのDispatch関数
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Dispatch(CollisionBase* _pOther);

	};
}


#endif // !GAME_ENEMYGENERATORCOLLISION_H
