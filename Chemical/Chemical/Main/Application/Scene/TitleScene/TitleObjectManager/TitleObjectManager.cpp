/**
 * @file	TitleObjectManager.cpp
 * @brief	タイトルオブジェクトクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "TitleObjectManager.h"

#include "TitleBackground\TitleBackground.h"
#include "TitleBackLogo\TitleBackLogo.h"
#include "TitleMenu\TitleMenu.h"


namespace Title
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	ObjectManager::ObjectManager()
	{
		m_pObjects.push_back(new Background());
		m_pObjects.push_back(new BackLogo());
		m_pObjects.push_back(new Menu());
	}

	ObjectManager::~ObjectManager()
	{
		for (auto itr = m_pObjects.begin(); itr != m_pObjects.end(); itr++)
		{
			SafeDelete(*itr);
		}
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
