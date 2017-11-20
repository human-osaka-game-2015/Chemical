/**
 * @file	CharacterManager.cpp
 * @brief	キャラクター管理クラス実装
 * @author	morimoto
 */
//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "CharacterManager.h"
#include "Player\Player.h"
#include "Enemy\Enemy.h"
#include "InitializeData\InitializeData.h"

namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	CharacterManager::CharacterManager()
	{
		SINGLETON_CREATE(InitializeData);
		SINGLETON_INSTANCE(InitializeData)->Load(1);

		m_pPlayer = new Player(SINGLETON_INSTANCE(InitializeData)->GetPlayerInitPos());
	}

	CharacterManager::~CharacterManager()
	{
		for (auto itr : m_pEnemys)
		{
			SafeDelete(itr);
		}
		SafeDelete(m_pPlayer);
		SINGLETON_DELETE(InitializeData);
	}

	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool CharacterManager::Initialize()
	{
		if (!m_pPlayer->Initialize()) return false;
		for (auto itr : m_pEnemys)
		{
			if (!itr->Initialize())
			{
				Finalize();
			}
		}
		return true;
	}

	void CharacterManager::Finalize()
	{
		for (auto itr : m_pEnemys)
		{
			itr->Finalize();
		}
		m_pPlayer->Finalize();
	}
}
