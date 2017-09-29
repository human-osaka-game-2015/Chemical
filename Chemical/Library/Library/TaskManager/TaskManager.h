/**
 * @file	TaskManager.h
 * @brief	タスク管理の基底クラス定義
 * @author	morimoto
 */
#ifndef LIB_TASKMANAGER_H
#define LIB_TASKMANAGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <list>
#include <algorithm>

#include "Debugger\Debugger.h"
#include "TaskBase\TaskBase.h"
#include "..\SingletonBase\SingletonBase.h"


namespace Lib
{
	/**
	 * タスク管理の基底クラス
	 * @tparam Type 管理するタスクオブジェクト
	 * @tparam StartUpTask Typeタスク実行前に処理を行うタスクオブジェクト
	 */
	template <typename Type, typename StartUpTask = TaskBase<>>
	class TaskManager : public SingletonBase<TaskManager<Type, StartUpTask>>
	{
	public:
		friend SingletonBase<TaskManager<Type, StartUpTask>>;
	
		/**
		 * タスクの実行
		 */
		void Run();
	
		/**
		 * タスクの追加
		 * @param[in] _pTask 追加するタスク
		 */
		void AddTask(Type* _pTask);

		/**
		 * タスクの削除
		 * @param[in] _pTask 削除するタスク
		 */
		void RemoveTask(Type* _pTask);
	
		/**
		 * 開始タスクの追加
		 * @param[in] _pStartUpTask 追加するタスク
		 */
		void AddStartUpTask(StartUpTask* _pStartUpTask);

		/**
		 * 開始タスクの削除
		 * @param[in] _pStartUpTask 削除するタスク
		 */
		void RemoveStartUpTask(StartUpTask* _pStartUpTask);

	private:
		/**
		 * コンストラクタ
		 */
		TaskManager();
	
		/**
		 * デストラクタ
		 */
		virtual ~TaskManager();


		std::list<StartUpTask*>	m_pStartUpTaskList;	//!< 起動タスクオブジェクトを管理するコンテナ.
		std::list<Type*>		m_pTaskList;		//!< タスクオブジェクトを管理するコンテナ.

#ifdef _DEBUG
		Debugger::ConsoleWindow		m_ConsoleWindow;	//!< デバッグ情報を出力するウィンドウ.
		Debugger::DebugTimer		m_DebugTimer;		//!< タスク一つの作業時間を計測するタイマクラス.
		Debugger::DebugTimer		m_DebugTimer2;		//!< タスク全体の作業時間を計測するタイマクラス.
#endif // _DEBUG

	};
}


#include "TaskManager_private.inl"


#endif // !LIB_TASKMANAGER_H
