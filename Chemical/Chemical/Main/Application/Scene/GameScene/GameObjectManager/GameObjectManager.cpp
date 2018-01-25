/**
 * @file	GameObjectManager.cpp
 * @brief	ゲームオブジェクト管理クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "GameObjectManager.h"
#include "GameDataManager\GameDataManager.h"

#include "Define\Define.h"
#include "StageManager\StageManager.h"
#include "GameTimeManager\GameTimeManager.h"
#include "CharacterManager\CharacterManager.h"
#include "GameClip\GameClip.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	ObjectManager::ObjectManager()
	{
		SINGLETON_CREATE(GameDataManager);

		m_pObjects.push_back(new StageManager());
		m_pObjects.push_back(new TimeManager());
		m_pObjects.push_back(new CharacterManager());
		m_pObjects.push_back(new GameClip());
	}

	ObjectManager::~ObjectManager()
	{
		for (auto itr = m_pObjects.begin(); itr != m_pObjects.end(); itr++)
		{
			SafeDelete(*itr);
		}

		SINGLETON_DELETE(GameDataManager);
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool ObjectManager::Initialize()
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

	void ObjectManager::Finalize()
	{
		for (auto itr = m_pObjects.begin(); itr != m_pObjects.end(); itr++)
		{
			(*itr)->Finalize();
		}
	}
}
