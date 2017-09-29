/**
 * @file	UpdateStartUpTask_private.inl
 * @brief	更新開始前のタスククラス実装
 * @author	morimoto
 */


namespace Lib
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	inline UpdateStartUpTask::UpdateStartUpTask() :
		m_pObject(nullptr)
	{
	}

	inline UpdateStartUpTask::~UpdateStartUpTask()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	inline void UpdateStartUpTask::Run()
	{
		m_pObject->UpdateStartUp();
	}

	inline void UpdateStartUpTask::SetObject(ObjectBase* _pObject)
	{
		m_pObject = _pObject;
	}
}
