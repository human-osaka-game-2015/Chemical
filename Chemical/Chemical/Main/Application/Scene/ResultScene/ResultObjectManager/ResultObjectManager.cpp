/**
 * @file	ResultObjectManager.cpp
 * @brief	リザルトオブジェクト管理クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ResultObjectManager.h"

#include "BackCharacter\BackCharacter.h"
#include "ResultBackground\ResultBackground.h"
#include "ResultMenu\ResultMenu.h"


namespace Result
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	ResultObjectManager::ResultObjectManager()
	{
		m_pObjects.push_back(new BackCharacter());
		m_pObjects.push_back(new ResultBackground());
		m_pObjects.push_back(new ResultMenu());
	}

	ResultObjectManager::~ResultObjectManager()
	{
		for (auto itr = m_pObjects.begin(); itr != m_pObjects.end(); itr++)
		{
			SafeDelete(*itr);
		}
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool ResultObjectManager::Initialize()
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

	void ResultObjectManager::Finalize()
	{
		for (auto itr = m_pObjects.begin(); itr != m_pObjects.end(); itr++)
		{
			(*itr)->Finalize();
		}
	}
}
