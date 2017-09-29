/**
 * @file	DrawTask.h
 * @brief	描画のタスククラス定義
 * @author	morimoto
 */
#ifndef LIB_DRAWTASK_H
#define LIB_DRAWTASK_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\TaskManager.h"
#include "..\DrawStartUpTask\DrawStartUpTask.h"
#include "..\..\..\ObjectManagerBase\ObjectBase\ObjectBase.h"


namespace Lib
{
	class ObjectBase;

	/**
	 * 描画のタスククラス
	 * @tparam PriorityType タスク実行の優先度を判断するオブジェクト
	 */
	template<typename PriorityType = int>
	class DrawTask final : public TaskBase<PriorityType>
	{
	public:
		/**
		 * コンストラクタ
		 */
		DrawTask();
	
		/**
		 * デストラクタ
		 */
		virtual ~DrawTask();
	
		/**
		 * 描画タスク実行
		 */
		virtual void Run();
	
		/**
		 * 描画オブジェクトをセット
		 * @param[in] _pObject 描画オブジェクト
		 */
		void SetObject(ObjectBase* _pObject);

	private:
		ObjectBase* m_pObject;	//!< 描画を行うオブジェクト.
	
	};


	typedef DrawTask<> Draw2DTask;		//!< 2Dオブジェクト描画タスク.
	typedef DrawTask<float> Draw3DTask;	//!< 3Dオブジェクト描画タスク.

	typedef TaskManager<Draw2DTask, DrawStartUpTask> Draw2DTaskManager;	//!< 2D描画タスク管理クラス.
	typedef TaskManager<Draw3DTask, DrawStartUpTask> Draw3DTaskManager;	//!< 3D描画タスク管理クラス.
}


#include "DrawTask_private.inl"


#endif // !LIB_DRAWTASK_H
