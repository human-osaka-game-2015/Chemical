/**
* @file	WalkEnemy.cpp
* @brief	ウォークエネミークラス実装
* @author	fujioka
*/

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "WalkEnemy.h"
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

	const int WalkEnemy::m_GuardTime = 80;
	const int WalkEnemy::m_WalkTime = 160;
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	WalkEnemy::WalkEnemy(D3DXVECTOR2* _pPosotion) :
		m_pWalkAnimation(nullptr),
		m_AiEnable(true),
		m_Frame(0),
		m_IsGuard(false)
	{
		m_Pos = *_pPosotion;
		m_Size = D3DXVECTOR2(80.0f, 80.0f);
		m_CollisionSize = D3DXVECTOR2(70.0f, 70.0f);

		m_Acceleration = 0;

		m_Attack = 10;
		m_Health = 300;
		m_Speed.x = 6.0f;

	}

	WalkEnemy::~WalkEnemy()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool WalkEnemy::Initialize()
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
			"Resource\\GameScene\\Animation\\Enemy0.anim",
			&m_AnimationIndex)) return false;

		m_pWalkAnimation = SINGLETON_INSTANCE(Lib::Dx11::AnimationManager)->GetAnimation(m_AnimationIndex);
		m_pWalkAnimation->SetAnimationPattern(Lib::Dx11::IAnimation::ANIMATION_PATTERN::LOOP_ANIMATION);
		m_pWalkAnimation->SetAnimationSpeed(0.1f);
		m_pWalkAnimation->AnimationStart();

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\GameScene\\Texture\\Enemy0.png",
			&m_TextureIndex)) return false;

		if (!CreateVertex2D()) return false;
		m_pVertex->SetUV(&D3DXVECTOR2(0.0f, 0.0f), &D3DXVECTOR2(1.0f, 1.0f));
		m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pVertex->SetAnimation(m_pWalkAnimation);

		m_pCollision = new EnemyCollision();
		SINGLETON_INSTANCE(CollisionManager)->AddCollision(m_pCollision);
		return true;
	}

	void WalkEnemy::Finalize()
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

	void WalkEnemy::CollisionTaskUpdate()
	{
		if (!m_AiEnable)
		{
			return;
		}

		DamageDecision();

		if (m_pCollision->GetCollisionDiff().x != 0)
		{
			m_IsLeft = !m_IsLeft;
		}

		// 地面に足が着いている.
		if (m_pCollision->GetCollisionDiff().y != 0)
		{
			m_Acceleration = 0;
			m_IsLanding = true;
		}
		else
		{
			m_IsLanding = false;
			m_IsLeft = !m_IsLeft;
		}

		m_Pos += m_pCollision->GetCollisionDiff();
	}

	void WalkEnemy::Update()
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

	void WalkEnemy::Draw()
	{
		if (!m_AiEnable)
		{
			return;
		}
		m_pVertex->SetInverse(!m_IsLeft);// テクスチャが反対なので反転.

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

	void WalkEnemy::GravityUpdate()
	{
		if (m_Acceleration > 23.0f)
		{
			m_Acceleration = 23.0f;
		}

		m_Acceleration += m_Gravity;
		m_Pos.y += m_Acceleration;
	}

	bool WalkEnemy::AiEnable()
	{
		if (m_Pos.x - SINGLETON_INSTANCE(GameDataManager)->GetScreenPos().x < m_EnableArea.Left ||
			m_Pos.x - SINGLETON_INSTANCE(GameDataManager)->GetScreenPos().x > m_EnableArea.Right)
		{
			return false;
		}
		return true;
	}

	void WalkEnemy::EnemyAi()
	{
		if (m_Health <= 0)
		{
			m_IsAlive = false;
		}

		if (m_Frame % (m_GuardTime + m_WalkTime) < m_WalkTime)
		{
			m_IsGuard = false;

			if (m_IsLeft)
			{
				m_Pos.x -= m_Speed.x;
				m_pWalkAnimation->Update();
			}
			else
			{
				m_Pos.x += m_Speed.x;
				m_pWalkAnimation->Update();
			}

		}
		else
		{
			m_IsGuard = true;
		}

		m_Frame++;
	}

	void WalkEnemy::DamageDecision()
	{
		if (!m_IsGuard&&m_pCollision->GetDamagestate().IsDamage)
		{
			m_Health -= 3;
		}
	}
}
