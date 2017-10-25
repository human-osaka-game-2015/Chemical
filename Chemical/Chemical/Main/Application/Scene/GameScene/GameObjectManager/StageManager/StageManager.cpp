/**
 * @file	StageManager.cpp
 * @brief	ステージ管理クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "StageManager.h"

#include "StageBackground\StageBackground.h"
#include "StageChipManager\StageChipManager.h"
#include "StageGimmickManager\StageGimmickManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	StageManager::StageManager()
	{
		m_pObjects.push_back(new StageBackground());
		m_pObjects.push_back(new StageChipManager());
		m_pObjects.push_back(new StageGimmickManager());
	}

	StageManager::~StageManager()
	{
		for (auto itr = m_pObjects.begin(); itr != m_pObjects.end(); itr++)
		{
			SafeDelete((*itr));
		}
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool StageManager::Initialize()
	{
		for (auto itr = m_pObjects.begin(); itr != m_pObjects.end(); itr++)
		{
			if (!(*itr)->Initialize())	return false;
		}

		return true;
	}

	void StageManager::Finalize()
	{
		for (auto itr = m_pObjects.begin(); itr != m_pObjects.end(); itr++)
		{
			(*itr)->Finalize();
		}
	}
}
