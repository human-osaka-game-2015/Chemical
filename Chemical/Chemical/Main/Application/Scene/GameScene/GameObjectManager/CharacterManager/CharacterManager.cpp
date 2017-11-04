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

namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	CharacterManager::CharacterManager()
	{
		m_pPlayer = new Player();
	}

	CharacterManager::~CharacterManager()
	{
		for (auto itr : m_pEnemys)
		{
			SafeDelete(itr);
		}
		SafeDelete(m_pPlayer);
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
