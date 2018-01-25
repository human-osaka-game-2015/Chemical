/**
 * @file	StaffObjectManager.cpp
 * @brief	スタッフオブジェクト管理クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "StaffObjectManager.h"

#include "StaffBackground\StaffBackground.h"
#include "Define\Define.h"


namespace Staff
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	StaffObjectManager::StaffObjectManager()
	{
		m_pObjects.push_back(new Background());
	}

	StaffObjectManager::~StaffObjectManager()
	{
		for (auto itr = m_pObjects.begin(); itr != m_pObjects.end(); itr++)
		{
			SafeDelete(*itr);
		}
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool StaffObjectManager::Initialize()
	{
		for (auto itr = m_pObjects.begin(); itr != m_pObjects.end(); itr++)
		{
			if (!(*itr)->Initialize())
			{
				Finalize();
				return false;
			}
		}

		return true;
	}

	void StaffObjectManager::Finalize()
	{
		for (auto itr = m_pObjects.begin(); itr != m_pObjects.end(); itr++)
		{
			(*itr)->Finalize();
		}
	}
}
