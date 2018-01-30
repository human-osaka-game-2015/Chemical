/**
* @file	EnemyManager.cpp
* @brief	エネミーマネージャ実装
* @author	fujioka
*/

#include "EnemyManager.h"
#include "EnemyBase\WalkEnemy\WalkEnemy.h"
#include "EnemyBase\FryEnemy\FryEnemy.h"
#include "EnemyBase\EggEnemy\EggEnemy.h"
#include "EnemyBase\JumpEnemy\JumpEnemy.h"
#include "EnemyBase\SuicideEnemy\SuicideEnemy.h"
#include "EnemyBase\ThrowEnemy\ThrowEnemy.h"
#include "..\InitializeFile\InitializeFile.h"

#include "..\..\GameDataManager\GameDataManager.h"
#include "InputDeviceManager\InputDeviceManager.h"
#include "InputDeviceManager\KeyDevice\KeyDevice.h"
#include "EventManager\EventManager.h"
#include "GameObjectManager\StageManager\StageGimmickManager\StageGimmickBase\EnemyGenerator\EnemyGeneratorEvent\EnemyGeneratorEvent.h"
#include "GameDefine.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	EnemyManager::EnemyManager(InitializeFile* _pInitializeFile) :
		m_pInitializeFile(_pInitializeFile),
		m_InitializeIndex(0)
	{

		m_pUpdateTask = new Lib::UpdateTask();
		m_pUpdateTask->SetObject(this);

		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);

		void(EnemyManager::*MultipleGenerate[])(D3DXVECTOR2*) =
		{
			&Game::EnemyManager::WalkGenerate,
			&Game::EnemyManager::FryGenerate,
			&Game::EnemyManager::JumpGenerate,
			&Game::EnemyManager::SuicideGenerate,
			&Game::EnemyManager::EggGenerate,
			&Game::EnemyManager::ThrowGenerate
		};

		std::vector<D3DXVECTOR2> EnemysInitPos = m_pInitializeFile->GetEnemysInitPos();
		std::vector<int>		 EnemysPattern = m_pInitializeFile->GetEnemysPattern();

		for (auto itr = EnemysInitPos.begin(); itr != EnemysInitPos.end(); itr++)
		{
			if (EnemysPattern[m_InitializeIndex] - 2 >= 0 && EnemysPattern[m_InitializeIndex] - 2 < MAX_TYPE)
			{
				(this->*MultipleGenerate[EnemysPattern[m_InitializeIndex] - 2])(&EnemysInitPos[m_InitializeIndex]);
				m_InitializeIndex++;
			}

		}

	}

	EnemyManager::~EnemyManager()
	{

		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
		delete m_pUpdateTask;
	}

	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool EnemyManager::Initialize()
	{
		m_ReceiveFunc = std::bind(&EnemyManager::ReceiveEvent, this, std::placeholders::_1);
		m_pEventListener = new Lib::EventListener(&m_ReceiveFunc);
		SINGLETON_INSTANCE(Lib::EventManager)->AddEventListener(
			m_pEventListener,
			TO_STRING(ENEMYGENERATOR_EVENT_GROUP));

		return true;
	}

	void EnemyManager::Finalize()
	{
		SINGLETON_INSTANCE(Lib::EventManager)->RemoveEventListener(
			m_pEventListener,
			TO_STRING(ENEMYGENERATOR_EVENT_GROUP));
		SafeDelete(m_pEventListener);

		std::vector<WalkEnemy*>::iterator Walkitr;
		for (Walkitr = m_pWalkEnemys.begin(); Walkitr != m_pWalkEnemys.end();) {
			(*Walkitr)->Finalize();
			SafeDelete(*Walkitr);
			Walkitr = m_pWalkEnemys.erase(Walkitr);
			continue;
			Walkitr++;
		}

		std::vector<FryEnemy*>::iterator Fryitr;
		for (Fryitr = m_pFryEnemys.begin(); Fryitr != m_pFryEnemys.end();) {
			(*Fryitr)->Finalize();
			SafeDelete(*Fryitr);
			Fryitr = m_pFryEnemys.erase(Fryitr);
			continue;
			Fryitr++;
		}

		std::vector<EggEnemy*>::iterator Eggitr;
		for (Eggitr = m_pEggEnemys.begin(); Eggitr != m_pEggEnemys.end();) {

			(*Eggitr)->Finalize();
			SafeDelete(*Eggitr);
			Eggitr = m_pEggEnemys.erase(Eggitr);

			continue;
			Eggitr++;
		}

		std::vector<JumpEnemy*>::iterator Jumpitr;
		for (Jumpitr = m_pJumpEnemys.begin(); Jumpitr != m_pJumpEnemys.end();) {
			(*Jumpitr)->Finalize();
			SafeDelete(*Jumpitr);
			Jumpitr = m_pJumpEnemys.erase(Jumpitr);
			continue;

			Jumpitr++;
		}

		std::vector<SuicideEnemy*>::iterator Suicideitr;
		for (Suicideitr = m_pSuicideEnemys.begin(); Suicideitr != m_pSuicideEnemys.end();) {
			(*Suicideitr)->Finalize();
			SafeDelete(*Suicideitr);
			Suicideitr = m_pSuicideEnemys.erase(Suicideitr);
			continue;

			Suicideitr++;
		}

		std::vector<ThrowEnemy*>::iterator Throwitr;
		for (Throwitr = m_pThrowEnemys.begin(); Throwitr != m_pThrowEnemys.end();) {
			(*Throwitr)->Finalize();
			SafeDelete(*Throwitr);
			Throwitr = m_pThrowEnemys.erase(Throwitr);
			continue;
			Throwitr++;
		}


	}

	void EnemyManager::Update()
	{

		void(EnemyManager::*m_MultipleUpdate[])() =
		{ &Game::EnemyManager::WalkUpdate,
		&Game::EnemyManager::FryUpdate,
		&Game::EnemyManager::JumpUpdate,
		&Game::EnemyManager::SuicideUpdate,
		&Game::EnemyManager::ThrowUpdate,
		&Game::EnemyManager::EggUpdate
		};

		for (int i = 0; i < MAX_TYPE; i++)
		{
			(this->*m_MultipleUpdate[i])();
		}

	}

	void EnemyManager::WalkUpdate()
	{
		std::vector<WalkEnemy*>::iterator itr;
		for (itr = m_pWalkEnemys.begin(); itr != m_pWalkEnemys.end();) {
			if (!(*itr)->GetIsAlive()) {
				(*itr)->Finalize();
				SafeDelete(*itr);
				itr = m_pWalkEnemys.erase(itr);
				continue;
			}
			itr++;
		}

	}

	void EnemyManager::WalkGenerate(D3DXVECTOR2* _pPosition)
	{
		if (m_pWalkEnemys.size() > 6) return;

		std::vector<WalkEnemy*>::iterator itr;

		m_pWalkEnemys.push_back(new WalkEnemy(_pPosition));
		itr = m_pWalkEnemys.end() - 1;
		if (!(*itr)->Initialize())
		{
			(*itr)->Finalize();
			SafeDelete(*itr);
			itr = m_pWalkEnemys.erase(itr);
		}

	}

	void EnemyManager::FryUpdate()
	{
		std::vector<FryEnemy*>::iterator itr;
		for (itr = m_pFryEnemys.begin(); itr != m_pFryEnemys.end();) {
			if (!(*itr)->GetIsAlive()) {
				(*itr)->Finalize();
				SafeDelete(*itr);
				itr = m_pFryEnemys.erase(itr);
				continue;
			}
			itr++;
		}
	}

	void EnemyManager::FryGenerate(D3DXVECTOR2* _pPosition)
	{
		/// @todo 未対応.
		/*
		if (m_pFryEnemys.size() > 6) return;

		std::vector<FryEnemy*>::iterator itr;

		m_pFryEnemys.push_back(new FryEnemy(_pPosition, &D3DXVECTOR2(300, 0)));
		itr = m_pFryEnemys.end() - 1;
		if (!(*itr)->Initialize())
		{
			(*itr)->Finalize();
			SafeDelete(*itr);
			itr = m_pFryEnemys.erase(itr);
		}
		*/

	}

	void EnemyManager::EggUpdate()
	{
		std::vector<EggEnemy*>::iterator itr;
		for (itr = m_pEggEnemys.begin(); itr != m_pEggEnemys.end();) {
			if ((*itr)->GetCompletion())
			{
				void(EnemyManager::*m_MultipleGenerate[])(D3DXVECTOR2*) =
				{
					&Game::EnemyManager::WalkGenerate,
					&Game::EnemyManager::FryGenerate,
					&Game::EnemyManager::JumpGenerate,
					&Game::EnemyManager::SuicideGenerate,
					&Game::EnemyManager::ThrowGenerate
				};

				(this->*m_MultipleGenerate[(*itr)->GetEnemyType()])(&(*itr)->GetPosition());

				(*itr)->Finalize();
				SafeDelete(*itr);
				itr = m_pEggEnemys.erase(itr);

				continue;
			}

			else if (!(*itr)->GetIsAlive()) {
				(*itr)->Finalize();
				SafeDelete(*itr);
				itr = m_pEggEnemys.erase(itr);
				continue;
			}
			itr++;
		}

	}

	void EnemyManager::EggGenerate(D3DXVECTOR2* _pPosition)
	{
		/// @todo 未対応.

		/*
		if (m_pEggEnemys.size() > 6) return;

		std::vector<EggEnemy*>::iterator itr;
		{
			m_pEggEnemys.push_back(new EggEnemy(_pPosition, 4));
			itr = m_pEggEnemys.end() - 1;
			if (!(*itr)->Initialize())
			{
				(*itr)->Finalize();
				SafeDelete(*itr);
				itr = m_pEggEnemys.erase(itr);
			}
		}
		*/
	}

	void EnemyManager::JumpUpdate()
	{
		std::vector<JumpEnemy*>::iterator itr;
		for (itr = m_pJumpEnemys.begin(); itr != m_pJumpEnemys.end();) {
			if (!(*itr)->GetIsAlive()) {
				(*itr)->Finalize();
				SafeDelete(*itr);
				itr = m_pJumpEnemys.erase(itr);
				continue;
			}
			itr++;
		}
	}

	void EnemyManager::JumpGenerate(D3DXVECTOR2* _pPosition)
	{
		if (m_pJumpEnemys.size() > 6) return;

		std::vector<JumpEnemy*>::iterator itr;

		m_pJumpEnemys.push_back(new JumpEnemy(_pPosition));
		itr = m_pJumpEnemys.end() - 1;
		if (!(*itr)->Initialize())
		{
			(*itr)->Finalize();
			SafeDelete(*itr);
			itr = m_pJumpEnemys.erase(itr);
		}
	}

	void EnemyManager::SuicideUpdate()
	{
		std::vector<SuicideEnemy*>::iterator itr;
		for (itr = m_pSuicideEnemys.begin(); itr != m_pSuicideEnemys.end();) {
			if (!(*itr)->GetIsAlive()) {
				(*itr)->Finalize();
				SafeDelete(*itr);
				itr = m_pSuicideEnemys.erase(itr);
				continue;
			}
			itr++;
		}
	}

	void EnemyManager::SuicideGenerate(D3DXVECTOR2* _pPosition)
	{
		/// @todo 未対応.
		/*
		if (m_pSuicideEnemys.size() > 6) return;

		std::vector<SuicideEnemy*>::iterator itr;

		m_pSuicideEnemys.push_back(new SuicideEnemy(_pPosition));
		itr = m_pSuicideEnemys.end() - 1;
		if (!(*itr)->Initialize())
		{
			(*itr)->Finalize();
			SafeDelete(*itr);
			itr = m_pSuicideEnemys.erase(itr);
		}
		*/
	}

	void EnemyManager::ThrowUpdate()
	{
		std::vector<ThrowEnemy*>::iterator itr;
		for (itr = m_pThrowEnemys.begin(); itr != m_pThrowEnemys.end();) {
			if (!(*itr)->GetIsAlive()) {
				(*itr)->Finalize();
				SafeDelete(*itr);
				itr = m_pThrowEnemys.erase(itr);
				continue;
			}
			itr++;
		}
	}

	void EnemyManager::ThrowGenerate(D3DXVECTOR2* _pPosition)
	{
		/*
		if (m_pThrowEnemys.size() > 6) return;

		std::vector<ThrowEnemy*>::iterator itr;

		m_pThrowEnemys.push_back(new ThrowEnemy(_pPosition));
		itr = m_pThrowEnemys.end() - 1;
		if (!(*itr)->Initialize())
		{
			(*itr)->Finalize();
			SafeDelete(*itr);
			itr = m_pThrowEnemys.erase(itr);
		}
		*/
	}

	void EnemyManager::ReceiveEvent(Lib::EventBase* _pEvent)
	{
		switch (_pEvent->GetEventID())
		{
		case ENEMY_GENERATE_EVENT:
			D3DXVECTOR2 Pos = reinterpret_cast<EnemyGeneratorEvent*>(_pEvent)->GetEventPos();
			EnemyGeneratorEvent::ENEMY_TYPE Type = reinterpret_cast<EnemyGeneratorEvent*>(_pEvent)->GetEnemyType();
			void(EnemyManager::*MultipleGenerate[])(D3DXVECTOR2*) =
			{
				&Game::EnemyManager::WalkGenerate,
				&Game::EnemyManager::FryGenerate,
				&Game::EnemyManager::JumpGenerate,
				&Game::EnemyManager::SuicideGenerate,
				&Game::EnemyManager::EggGenerate,
				&Game::EnemyManager::ThrowGenerate
			};

			(this->*MultipleGenerate[Type])(&Pos);

			break;
		}
	}
}
