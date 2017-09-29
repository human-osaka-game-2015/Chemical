/**
 * @file	DrawStartUpTask_private.inl
 * @brief	描画前処理のタスククラス実装
 * @author	morimoto
 */


namespace Lib
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	inline DrawStartUpTask::DrawStartUpTask() :
		m_pObject(nullptr)
	{
	}

	inline DrawStartUpTask::~DrawStartUpTask()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	inline void DrawStartUpTask::Run()
	{
		m_pObject->DrawStartUp();
	}

	inline void DrawStartUpTask::SetObject(ObjectBase* _pObject)
	{
		m_pObject = _pObject;
	}
}
