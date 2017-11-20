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
#include "InitializeFile\InitializeFile.h"
#include "Application\GamePlayFile\GamePlayFile.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	CharacterManager::CharacterManager()
	{
		GamePlayFile* pPlayFile = new GamePlayFile;
		pPlayFile->Open();
		InitializeFile* pInitializeFile = new InitializeFile(pPlayFile->GetStageNum());
		pPlayFile->Close();
		m_pPlayer = new Player(pInitializeFile->GetPlayerInitPos());

		SafeDelete(pPlayFile);
		SafeDelete(pInitializeFile);
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
