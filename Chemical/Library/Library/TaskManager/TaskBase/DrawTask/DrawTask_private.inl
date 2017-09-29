/**
 * @file	DrawTask_private.inl
 * @brief	描画のタスククラステンプレート実装
 * @author	morimoto
 */


namespace Lib
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	template<typename PriorityType>
	inline DrawTask<PriorityType>::DrawTask() :
		m_pObject(nullptr)
	{
	}

	template<typename PriorityType>
	inline DrawTask<PriorityType>::~DrawTask()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	template<typename PriorityType>
	inline void DrawTask<PriorityType>::Run()
	{
		m_pObject->Draw();
	}

	template<typename PriorityType>
	inline void DrawTask<PriorityType>::SetObject(ObjectBase* _pObject)
	{
		m_pObject = _pObject;
	}
}

