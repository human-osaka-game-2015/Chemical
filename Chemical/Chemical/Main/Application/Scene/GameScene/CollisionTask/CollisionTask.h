/**
 * @file	CollisionTask.h
 * @brief	当たり判定更新のタスククラス定義
 * @author	kotani
 */
#ifndef GAME_COLLISIONTASK_H
#define GAME_COLLISIONTASK_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "TaskManager\TaskManager.h"
#include "Object2DBase\Object2DBase.h"


namespace Game
{
	/*** 当たり判定更新のタスククラス */
	class CollisionTask final : public Lib::TaskBase<>
	{
	public:
		/*** コンストラクタ */
		CollisionTask();

		/*** デストラクタ */
		virtual ~CollisionTask();

		/*** 当たり判定更新タスク実行 */
		virtual void Run();

		/**
		 * 当たり判定更新オブジェクトをセット
		 * @param[in] _pObject 更新オブジェクト
		 */
		void SetObject(Object2DBase* _pObject);

	private:
		Object2DBase* m_pObject;	//!< 当たり判定更新を行うオブジェクト.

	};

	typedef Lib::TaskManager<CollisionTask> CollisionTaskManager;
}

#include "CollisionTask_private.inl"


#endif // !GAME_COLLISIONTASK_H
