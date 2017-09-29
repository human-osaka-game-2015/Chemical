/**
 * @file	UpdateStartUpTask.h
 * @brief	更新開始前のタスククラス定義
 * @author	morimoto
 */
#ifndef LIB_UPDATESTARTUPTASK_H
#define LIB_UPDATESTARTUPTASK_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\TaskBase.h"
#include "..\..\..\ObjectManagerBase\ObjectBase\ObjectBase.h"


namespace Lib
{
	/**
	 * 更新開始前のタスククラス
	 */
	class UpdateStartUpTask final : public TaskBase<>
	{
	public:
		/**
		 * コンストラクタ
		 */
		UpdateStartUpTask();

		/**
		 * デストラクタ 
		 */
		virtual ~UpdateStartUpTask();

		/**
		 * 更新前処理タスク実行
		 */
		virtual void Run();
	
		/**
		 * 更新前処理実行オブジェクトをセット
		 * @param[in] _pObject オブジェクト
		 */
		void SetObject(ObjectBase* _pObject);

	private:
		ObjectBase* m_pObject;	//!< 更新前処理を行うオブジェクト.

	};
}


#include "UpdateStartUpTask_private.inl"


#endif // !LIB_UPDATESTARTUPTASK_H
