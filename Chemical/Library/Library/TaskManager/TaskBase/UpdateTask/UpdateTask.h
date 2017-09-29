/**
 * @file	UpdateTask.h
 * @brief	更新のタスククラス定義
 * @author	morimoto
 */
#ifndef LIB_UPDATETASK_H
#define LIB_UPDATETASK_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\TaskManager.h"
#include "..\UpdateStartUpTask\UpdateStartUpTask.h"
#include "..\..\..\ObjectManagerBase\ObjectBase\ObjectBase.h"


namespace Lib
{
	/**
	 * 更新のタスククラス
	 */
	class UpdateTask final : public TaskBase<>
	{
	public:
		/**
		 * コンストラクタ
		 */
		UpdateTask();
	
		/**
		 * デストラクタ
		 */
		virtual ~UpdateTask();
	
		/**
		 * 更新タスク実行
		 */
		virtual void Run();
	
		/**
		 * 更新オブジェクトをセット
		 * @param[in] _pObject 更新オブジェクト
		 */
		void SetObject(ObjectBase* _pObject);
	
	private:
		ObjectBase* m_pObject;	//!< 更新を行うオブジェクト.
		
	};


	typedef TaskManager<UpdateTask> UpdateTaskManager;
}

#include "UpdateTask_private.inl"


#endif // !LIB_UPDATETASK_H
