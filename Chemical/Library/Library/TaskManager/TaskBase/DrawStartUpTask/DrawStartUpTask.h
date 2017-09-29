/**
 * @file	DrawStartUpTask.h
 * @brief	描画前処理のタスククラス定義
 * @author	morimoto
 */
#ifndef LIB_DRAWSTARTUPTASK_H
#define LIB_DRAWSTARTUPTASK_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\TaskBase.h"
#include "..\..\..\ObjectManagerBase\ObjectBase\ObjectBase.h"


namespace Lib
{
	/**
	 * 描画前処理のタスククラス
	 */
	class DrawStartUpTask final : public TaskBase<>
	{
	public:
		/**
		 * コンストラクタ 
		 */
		DrawStartUpTask();

		/**
		 * デストラクタ 
		 */
		virtual ~DrawStartUpTask();

		/**
		 * 描画前処理タスク実行
		 */
		virtual void Run();
	
		/**
		 * 描画前処理実行オブジェクトをセット
		 * @param[in] _pObject オブジェクト
		 */
		void SetObject(ObjectBase* _pObject);

	private:
		ObjectBase* m_pObject;	//!< 描画前処理を行うオブジェクト.

	};
}


#include "DrawStartUpTask_private.inl"


#endif // !LIB_DRAWSTARTUPTASK_H
