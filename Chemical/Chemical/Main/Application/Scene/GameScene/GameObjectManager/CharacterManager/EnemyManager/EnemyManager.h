/**
* @file	EnemyManager.h
* @brief	エネミーマネージャ定義
* @author	fujioka
*/

#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <vector>

#include "ObjectManagerBase\ObjectBase\ObjectBase.h"
#include "TaskManager\TaskBase\UpdateTask\UpdateTask.h"
#include "EventManager\EventListener\EventListener.h"

#include <D3DX11.h>
#include <D3DX10.h>

namespace Game
{
	class WalkEnemy;
	class FryEnemy;
	class EggEnemy;
	class JumpEnemy;
	class SuicideEnemy;
	class ThrowEnemy;

	class InitializeFile;

	class EnemyManager : public Lib::ObjectBase
	{
	public:

		enum EnemyType
		{
			WALK_TYPE,
			FRY_TYPE,
			JUMP_TYPE,
			SUICIDE_TYPE,
			THROW_TYPE,
			EGG_TYPE,
			MAX_TYPE
		};

		EnemyManager(InitializeFile* _pInitializeFile);
		virtual ~EnemyManager();

		virtual bool Initialize();

		virtual void Finalize();

		virtual void Update();
		
	private:
		
		std::vector<WalkEnemy*>		m_pWalkEnemys;
		std::vector<FryEnemy*>		m_pFryEnemys;
		std::vector<EggEnemy*>		m_pEggEnemys;
		std::vector<JumpEnemy*>		m_pJumpEnemys;
		std::vector<SuicideEnemy*>	m_pSuicideEnemys;
		std::vector<ThrowEnemy*>	m_pThrowEnemys;

		Lib::UpdateTask*	m_pUpdateTask;
		
		InitializeFile* m_pInitializeFile;

		int m_InitializeIndex;

		void WalkUpdate();
		void FryUpdate();
		void EggUpdate();
		void JumpUpdate();
		void SuicideUpdate();
		void ThrowUpdate();

		void WalkGenerate(D3DXVECTOR2* _pPosition);
		void FryGenerate(D3DXVECTOR2* _pPosition);
		void EggGenerate(D3DXVECTOR2* _pPosition);
		void JumpGenerate(D3DXVECTOR2* _pPosition);
		void SuicideGenerate(D3DXVECTOR2* _pPosition);
		void ThrowGenerate(D3DXVECTOR2* _pPosition);

		Lib::EventListener* m_pEventListener;
		std::function<void(Lib::EventBase*)> m_ReceiveFunc;

		void ReceiveEvent(Lib::EventBase* _pEvent);

	};
}

#endif