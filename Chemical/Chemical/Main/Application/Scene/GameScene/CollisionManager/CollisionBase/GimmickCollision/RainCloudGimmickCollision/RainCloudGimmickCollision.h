/**
 * @file	RainCloudGimmickCollision.h
 * @brief	雨雲ギミック当たり判定クラス定義
 * @author	morimoto
 */
#ifndef GAME_RAINCLOUDGIMMICKCOLLISION_H
#define GAME_RAINCLOUDGIMMICKCOLLISION_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\GimmickCollision.h"


namespace Game
{
	/*** 雨雲ギミック当たり判定クラス */
	class RainCloudGimmickCollision : public GimmickCollision
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _id 当たり判定ID
		 */
		RainCloudGimmickCollision(int _id);

		/*** デストラクタ */
		virtual ~RainCloudGimmickCollision();

		/**
		 * Collide関数へのDispatch関数
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Dispatch(CollisionBase* _pOther);

	};
}


#endif // !GAME_RAINCLOUDGIMMICKCOLLISION_H
