/**
 * @file	TaskManager_private.inl
 * @brief	タスク管理の基底クラステンプレート実装
 * @author	morimoto
 */
#ifndef LIB_TASKMANAGER_PRIVATE_H
#define LIB_TASKMANAGER_PRIVATE_H


namespace Lib
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	template <typename Type, typename StartUpTask>
	inline TaskManager<Type, StartUpTask>::TaskManager()
	{
#ifdef _DEBUG
		m_ConsoleWindow.Initialize(Debugger::TypeToString<Type>());
#endif // _DEBUG
	}

	template <typename Type, typename StartUpTask>
	inline TaskManager<Type, StartUpTask>::~TaskManager()
	{
#ifdef _DEBUG
		m_ConsoleWindow.Finalize();
#endif // _DEBUG
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	template <typename Type, typename StartUpTask>
	inline void TaskManager<Type, StartUpTask>::Run()
	{
#ifdef _DEBUG

		m_DebugTimer2.StartTimer();	// タスク全体の作業時間計測開始.

		m_ConsoleWindow.Print("\n\n--------------------%s--------------------\n",
			Debugger::TypeToString<StartUpTask>());

		// 起動時実行タスクの処理.
		m_pStartUpTaskList.sort(StartUpTask::TaskCmp());
		for (auto itr = m_pStartUpTaskList.begin(); itr != m_pStartUpTaskList.end(); itr++)
		{
			// タスクの作業時間計測.
			m_DebugTimer.StartTimer();
			(*itr)->Run();
			m_DebugTimer.EndTimer();

			m_ConsoleWindow.Print(
				"Name : %s - Time : %d us\n",
				(*itr)->GetName(),
				m_DebugTimer.GetMicroSecond());
		}


		m_ConsoleWindow.Print("\n--------------------%s--------------------\n",
			Debugger::TypeToString<Type>());

		// 実行タスクの処理.
		m_pTaskList.sort(Type::TaskCmp());
		for (auto itr = m_pTaskList.begin(); itr != m_pTaskList.end(); itr++)
		{
			// タスクの作業時間計測.
			m_DebugTimer.StartTimer();
			(*itr)->Run();
			m_DebugTimer.EndTimer();

			m_ConsoleWindow.Print(
				"Name : %s - Time : %d us\n",
				(*itr)->GetName(),
				m_DebugTimer.GetMicroSecond());
		}

		m_DebugTimer2.EndTimer();	// タスク全体の作業時間計測終了.
		m_ConsoleWindow.Print(
			"\nResult : %d us\n",
			m_DebugTimer2.GetMicroSecond());

#else // _DEBUG

		// 起動時実行タスクの処理.
		m_pStartUpTaskList.sort(StartUpTask::TaskCmp());
		for (auto itr = m_pStartUpTaskList.begin(); itr != m_pStartUpTaskList.end(); itr++)
		{
			// タスクの作業時間計測.
			(*itr)->Run();
		}

		// 実行タスクの処理.
		m_pTaskList.sort(Type::TaskCmp());
		for (auto itr = m_pTaskList.begin(); itr != m_pTaskList.end(); itr++)
		{
			// タスクの作業時間計測.
			(*itr)->Run();
		}

#endif // !_DEBUG
	}

	template <typename Type, typename StartUpTask>
	inline void TaskManager<Type, StartUpTask>::AddTask(Type* _pTask)
	{
		m_pTaskList.push_back(_pTask);
	}

	template <typename Type, typename StartUpTask>
	inline void TaskManager<Type, StartUpTask>::RemoveTask(Type* _pTask)
	{
		m_pTaskList.remove(_pTask);
	}

	template <typename Type, typename StartUpTask>
	inline void TaskManager<Type, StartUpTask>::AddStartUpTask(StartUpTask* _pStartUpTask)
	{
		m_pStartUpTaskList.push_back(_pStartUpTask);
	}

	template <typename Type, typename StartUpTask>
	inline void TaskManager<Type, StartUpTask>::RemoveStartUpTask(StartUpTask* _pStartUpTask)
	{
		m_pStartUpTaskList.remove(_pStartUpTask);
	}
}


#endif // !LIB_TASKMANAGER_PRIVATE_H
