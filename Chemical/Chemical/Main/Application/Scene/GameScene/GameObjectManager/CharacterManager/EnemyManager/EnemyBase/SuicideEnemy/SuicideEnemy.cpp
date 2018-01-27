/**
* @file	WalkEnemy.cpp
* @brief	ウォークエネミークラス実装
* @author	fujioka
*/

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "SuicideEnemy.h"
#include "Application\Scene\GameScene\GameDefine.h"
#include "..\..\..\..\GameDataManager\GameDataManager.h"
#include "..\..\..\..\..\CollisionManager\CollisionManager.h"
#include "Application\Scene\GameScene\CollisionManager\CollisionBase\EnemyCollision\EnemyCollision.h"

#include "DirectX11\AnimationManager\Dx11AnimationManager.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"

#include "TaskManager\TaskManager.h"
#include "..\WalkEnemy\EnemyUI\EnemyUI.h"

namespace Game
{

	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	SuicideEnemy::SuicideEnemy(D3DXVECTOR2* _pPosotion) :
		m_pWalkAnimation(nullptr),
		m_AiEnable(true),
		m_Frame(0),
		m_Radius(50.0f),
		m_SuicideStart(false)
	{
		m_Pos = *_pPosotion;
		m_Size = D3DXVECTOR2(100.0f, 100.0f);
		m_CollisionSize = D3DXVECTOR2(100.0f, 100.0f);

		m_Acceleration = 0;

		m_Attack = 10;
		m_Health = 300;
		m_Speed.x = 6.0f;

	}

	SuicideEnemy::~SuicideEnemy()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool SuicideEnemy::Initialize()
	{
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->AddTask(m_pDrawTask);
		m_pDrawTask->SetPriority(GAME_DRAW_CHARACTER);

		m_EnemyUI = new EnemyUI(this);
		if (!m_EnemyUI->Initialize())
		{
			return false;
		}

		m_pCollisionTask = new CollisionTask();
		m_pCollisionTask->SetObject(this);
		SINGLETON_INSTANCE(CollisionTaskManager)->AddTask(m_pCollisionTask);

		if (!SINGLETON_INSTANCE(Lib::Dx11::AnimationManager)->LoadAnimation(
			"Resource\\GameScene\\Animation\\PlayerWalk.anim",
			&m_AnimationIndex)) return false;

		m_pWalkAnimation = SINGLETON_INSTANCE(Lib::Dx11::AnimationManager)->GetAnimation(m_AnimationIndex);
		m_pWalkAnimation->SetAnimationPattern(Lib::Dx11::IAnimation::ANIMATION_PATTERN::LOOP_ANIMATION);
		m_pWalkAnimation->SetAnimationSpeed(0.1f);
		m_pWalkAnimation->AnimationStart();

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\GameScene\\Texture\\player.png",
			&m_TextureIndex)) return false;

		if (!CreateVertex2D()) return false;
		m_pVertex->SetUV(&D3DXVECTOR2(0.0f, 0.0f), &D3DXVECTOR2(1.0f, 1.0f));
		m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pVertex->SetAnimation(m_pWalkAnimation);

		m_pCollision = new EnemyCollision();
		SINGLETON_INSTANCE(CollisionManager)->AddCollision(m_pCollision);
		return true;
	}

	void SuicideEnemy::Finalize()
	{
		SINGLETON_INSTANCE(CollisionManager)->RemoveCollision(m_pCollision);
		SafeDelete(m_pCollision);
		m_EnemyUI->Finalize();
		SafeDelete(m_EnemyUI);

		ReleaseVertex2D();

		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);
		SINGLETON_INSTANCE(Lib::Dx11::AnimationManager)->ReleaseAnimation(m_AnimationIndex);
		SINGLETON_INSTANCE(CollisionTaskManager)->RemoveTask(m_pCollisionTask);
		SafeDelete(m_pCollisionTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
	}

	void SuicideEnemy::CollisionTaskUpdate()
	{
		if (!m_AiEnable)
		{
			return;
		}

		DamageDecision();

		if (m_pCollision->GetCollisionDiff().x != 0)
		{
			m_Health = 0;
		}

		// 地面に足が着いている.
		if (m_pCollision->GetCollisionDiff().y != 0)
		{
			m_Health = 0;
		}
		else
		{

		}

		//m_Pos += m_pCollision->GetCollisionDiff();
	}

	void SuicideEnemy::Update()
	{
		m_AiEnable = AiEnable();

		if (!m_AiEnable)
		{
			SINGLETON_INSTANCE(CollisionManager)->RemoveCollision(m_pCollision);
			m_OldEnable = m_AiEnable;
			return;
		}
		else if (!m_OldEnable)
		{
			SINGLETON_INSTANCE(CollisionManager)->AddCollision(m_pCollision);
			m_OldEnable = m_AiEnable;
		}

		EnemyAi();

		GravityUpdate();
		RectangleCollisionBase::RECTANGLE RectAngle;
		RectAngle.Left = m_Pos.x - m_CollisionSize.x / 2;
		RectAngle.Top = m_Pos.y - m_CollisionSize.y / 2;
		RectAngle.Right = m_Pos.x + m_CollisionSize.x / 2;
		RectAngle.Bottom = m_Pos.y + m_CollisionSize.y / 2;
		m_pCollision->SetRect(RectAngle);
		m_pCollision->ResetCollisionDiff();
	}

	void SuicideEnemy::Draw()
	{
		if (!m_AiEnable)
		{
			return;
		}
		m_pVertex->SetInverse(m_IsLeft);
		m_pVertex->SetVertex(&m_Size);

		m_pVertex->ShaderSetup();
		m_pVertex->WriteVertexBuffer();
		D3DXVECTOR2 Pos = m_Pos;
		Pos.x -= SINGLETON_INSTANCE(GameDataManager)->GetScreenPos().x;
		m_pVertex->WriteConstantBuffer(&Pos);
		m_pVertex->Draw();
	}

	//----------------------------------------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------------------------------------

	void SuicideEnemy::GravityUpdate()
	{
		
	}

	bool SuicideEnemy::AiEnable()
	{
		if (m_Pos.x - SINGLETON_INSTANCE(GameDataManager)->GetScreenPos().x < m_EnableArea.Left ||
			m_Pos.x - SINGLETON_INSTANCE(GameDataManager)->GetScreenPos().x>m_EnableArea.Right)
		{
			return false;
		}
		return true;
	}

	void SuicideEnemy::EnemyAi()
	{
		if (m_Health <= 0)
		{
			//m_IsAlive = false;
			m_SuicideStart = true;
		}

		if (m_SuicideStart)
		{
			m_Radius += 3;
			m_CollisionSize.x = m_Radius * 2;
			m_CollisionSize.y = m_Radius * 2;
			m_Size.x = m_Radius * 2;
			m_Size.y = m_Radius * 2;
		}

		if (m_Radius > 250)
		{
			m_IsAlive = false;
		}

		if (SINGLETON_INSTANCE(GameDataManager)->GetPlayerPos().x<m_Pos.x)
		{
			m_IsLeft = true;
		}
		else
		{
			m_IsLeft = false;
		}

		if (m_Health)
		{
			D3DXVECTOR2 Vec = (SINGLETON_INSTANCE(GameDataManager)->GetPlayerPos());// - m_Pos) / abs(hypot(SINGLETON_INSTANCE(GameDataManager)->GetPlayerPos().x - m_Pos.x, SINGLETON_INSTANCE(GameDataManager)->GetPlayerPos().y - m_Pos.y));

			m_Speed = (SINGLETON_INSTANCE(GameDataManager)->GetPlayerPos() - m_Pos)
				/ abs(hypot(SINGLETON_INSTANCE(GameDataManager)->GetPlayerPos().x - m_Pos.x, SINGLETON_INSTANCE(GameDataManager)->GetPlayerPos().y - m_Pos.y))
				* 3.0f;

			m_Pos += m_Speed;
		}
		m_pWalkAnimation->Update();
	}


	void SuicideEnemy::DamageDecision()
	{
		if (m_pCollision->GetDamagestate().IsDamage)
		{
			m_Health = 0;
		}
	}
}
