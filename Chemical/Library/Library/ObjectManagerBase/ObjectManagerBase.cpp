/**
 * @file	ObjectManagerBase.cpp
 * @brief	オブジェクト管理基底クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ObjectManagerBase.h"


namespace Lib
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	ObjectManagerBase::ObjectManagerBase()
	{
	}

	ObjectManagerBase::~ObjectManagerBase()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool ObjectManagerBase::Initialize()
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

	void ObjectManagerBase::Finalize()
	{
		for (auto itr = m_pObjects.begin(); itr != m_pObjects.end(); itr++)
		{
			(*itr)->Finalize();
		}
	}
}

