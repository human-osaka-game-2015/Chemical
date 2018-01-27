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
//#include "Enemy\Enemy.h"
#include "InitializeFile\InitializeFile.h"
#include "Application\GamePlayFile\GamePlayFile.h"

#include "EnemyManager\EnemyManager.h"

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

		m_pEnemyManager = new EnemyManager(pInitializeFile);

		SafeDelete(pPlayFile);
		SafeDelete(pInitializeFile);

		D3DXVECTOR2 TestPos(900.0f, 200.0f);
		
	}

	CharacterManager::~CharacterManager()
	{
		
		SafeDelete(m_pEnemyManager);
	
		SafeDelete(m_pPlayer);
	}

	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool CharacterManager::Initialize()
	{
		if (!m_pPlayer->Initialize()) return false;
		if (!m_pEnemyManager->Initialize()) return false;

		return true;
	}

	void CharacterManager::Finalize()
	{
		
		m_pEnemyManager->Finalize();
		m_pPlayer->Finalize();
	}
}
