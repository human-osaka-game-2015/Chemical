/**
 * @file	UpdateTask_private.inl
 * @brief	更新のタスククラス実装
 * @author	morimoto
 */


namespace Lib
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	inline UpdateTask::UpdateTask() :
		m_pObject(nullptr)
	{
	}

	inline UpdateTask::~UpdateTask()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	inline void UpdateTask::Run()
	{
		m_pObject->Update();
	}

	inline void UpdateTask::SetObject(ObjectBase* _pObject)
	{
		m_pObject = _pObject;
	}
}
