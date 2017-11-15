/**
 * @file	CollisionTask_private.inl
 * @brief	当たり判定のタスククラス実装
 * @author	kotani
 */

namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	inline CollisionTask::CollisionTask() :
		m_pObject(nullptr)
	{
	}

	inline CollisionTask::~CollisionTask()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	inline void CollisionTask::Run()
	{
		m_pObject->CollisionTaskUpdate();
	}

	inline void CollisionTask::SetObject(Object2DBase* _pObject)
	{
		m_pObject = _pObject;
	}
}