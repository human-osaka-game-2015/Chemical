/**
 * @file	TaskBase.h
 * @brief	タスクの基底クラス定義
 * @author	morimoto
 */
#ifndef LIB_TASKBASE_H
#define LIB_TASKBASE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\Define\Define.h"


namespace Lib
{
	/**
	 * タスクの基底クラス
	 * @tparam PriorityType タスク実行の優先度を判断するオブジェクト
	 */
	template<typename PriorityType = int>
	class TaskBase
	{
	public:
		/**
		 * タスクの比較用ファンクタ
		 */
		struct TaskCmp
		{
		public:
			bool operator()(TaskBase<PriorityType>* _pTask1, TaskBase<PriorityType>* _pTask2) const
			{
				return (_pTask1->m_Priority < _pTask2->m_Priority);
			}

			bool operator()(
				const TaskBase<PriorityType>& _task1, 
				const TaskBase<PriorityType>& _task2) const
			{
				return (_task1.m_Priority < _task2.m_Priority);
			}
		};


		/**
		 * コンストラクタ
		 * @param[in] _taskName タスクの名前
		 * @todo できれば引数なしにしたいので何かしら修正する予定
		 */
		TaskBase(LPCTSTR _taskName = "unknown");
	
		/**
		 * デストラクタ
		 */
		virtual ~TaskBase();
	
		/**
		 * タスクの実行
		 */
		virtual void Run() = 0;
	
		/**
		 * タスク実行の優先度設定(低い値が優先される)
		 * @param[in] _priority タスクの優先度
		 */
		void SetPriority(PriorityType _priority)
		{
			m_Priority = _priority;
		}

		/**
		 * タスクの名前変更
		 * @param[in] _taskName タスクの名前
		 */
		void SetName(LPCTSTR _taskName)
		{
			m_TaskName = _taskName;
		}

		/**
		 * タスクの名前取得
		 * @return タスクの名前
		 */
		LPCTSTR GetName()
		{
			return m_TaskName;
		}
	
		/**
		 * タスクのIDを取得
		 * @return タスクのID
		 */
		unsigned int GetID()
		{
			return m_TaskID;
		}

	protected:
		unsigned int		m_TaskID;	//!< タスクのID.
		PriorityType		m_Priority;	//!< タスク実行の優先度.
		LPCTSTR				m_TaskName;	//!< タスクの名前.

	private:
		static unsigned int m_TaskCount;	//!< タスクの作成数.

		DISALLOW_COPY_AND_ASSIGN(TaskBase);

	};
}


#include "TaskBase_private.inl"


#endif // !LIB_TASKBASE_H
