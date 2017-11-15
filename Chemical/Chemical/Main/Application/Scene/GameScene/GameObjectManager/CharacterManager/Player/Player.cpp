/**
 * @file	Player.cpp
 * @brief	プレイヤークラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Player.h"
#include "Application\Application.h"
#include "Application\Scene\GameScene\GameDefine.h"
#include "..\..\GameDataManager\GameDataManager.h"
#include "..\..\..\CollisionManager\CollisionManager.h"
#include "Application\Scene\GameScene\CollisionManager\CollisionBase\PlayerCollision\PlayerCollision.h"

#include "DirectX11\AnimationManager\Dx11AnimationManager.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "InputDeviceManager\InputDeviceManager.h"
#include "InputDeviceManager\KeyDevice\KeyDevice.h"
#include "TaskManager\TaskManager.h"


namespace Game
{
	const float Player::m_Gravity = 0.8f;
	const float Player::m_JumpPower = -25;
	const float Player::m_MoveSpeed = 6;

	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	
	Player::Player() :
		m_IsLeft(false),
		m_pCollision(nullptr),
		m_Acceleration(0),
		m_IsLanding(false),
		m_AnimationState(WALK_ANIMATION)
	{
		m_Size = D3DXVECTOR2(220.f, 220.f);
		m_Pos = D3DXVECTOR2(980.f, 400.f);
		m_WorldPos = m_Pos;
	}

	Player::~Player()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------

	bool Player::Initialize()
	{
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->AddTask(m_pDrawTask);
		m_pDrawTask->SetPriority(GAME_DRAW_CHARACTER);
		m_pCollisionTask = new CollisionTask();
		m_pCollisionTask->SetObject(this);
		SINGLETON_INSTANCE(CollisionTaskManager)->AddTask(m_pCollisionTask);

		if (!LoadAnimation("PlayerWalk.anim", WALK_ANIMATION)) return false;

		m_Animations[WALK_ANIMATION].pData->
			SetAnimationPattern(Lib::Dx11::IAnimation::ANIMATION_PATTERN::LOOP_ANIMATION);
		m_Animations[WALK_ANIMATION].pData->SetAnimationSpeed(0.1f);

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\GameScene\\Texture\\player.png",
			&m_TextureIndex)) return false;

		if (!CreateVertex2D()) return false;
		m_pVertex->SetUV(&D3DXVECTOR2(0.f, 0.f), &D3DXVECTOR2(1.f, 1.f));
		m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pVertex->SetAnimation(m_Animations[WALK_ANIMATION].pData);

		m_pCollision = new PlayerCollision();
		RectangleCollision::RECTANGLE RectAngle;
		RectAngle.Left = m_Pos.x - m_Size.x / 2;
		RectAngle.Top = m_Pos.y - m_Size.y / 2;
		RectAngle.Right = m_Pos.x + m_Size.x / 2;
		RectAngle.Bottom = m_Pos.y + m_Size.y / 2;
		m_pCollision->SetRect(RectAngle);
		SINGLETON_INSTANCE(CollisionManager)->AddCollision(m_pCollision);

		SINGLETON_INSTANCE(GameDataManager)->SetPlayerPosPtr(&m_WorldPos);

		return true;
	}
	
	void Player::Finalize()
	{
		SINGLETON_INSTANCE(CollisionManager)->RemoveCollision(m_pCollision);
		SafeDelete(m_pCollision);

		ReleaseVertex2D();

		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);
		for (const auto& itr : m_Animations)
		{
			SINGLETON_INSTANCE(Lib::Dx11::AnimationManager)->
				ReleaseAnimation(itr.Index);
		}
		
		SINGLETON_INSTANCE(CollisionTaskManager)->RemoveStartUpTask(m_pCollisionTask);
		SafeDelete(m_pCollisionTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
	}

	void Player::CollisionTaskUpdate()
	{
		// 地面に足が着いている.
		if (m_pCollision->GetCollisionDiff().y != 0)
		{
			m_Acceleration = 0;
			m_IsLanding = true;
		}
		else
		{
			m_IsLanding = false;
		}

		m_Pos.y += m_pCollision->GetCollisionDiff().y;
		m_WorldPos += m_pCollision->GetCollisionDiff();
	}

	void Player::Update()
	{
		const Lib::KeyDevice::KEYSTATE* pKeyState = SINGLETON_INSTANCE(Lib::InputDeviceManager)->GetKeyState();
		float X = static_cast<float>(Application::m_WindowWidth / 2);	//!< 画面中央からスクロール.

		if (pKeyState[DIK_UPARROW] == Lib::KeyDevice::KEY_PUSH &&
			m_IsLanding)
		{
			m_Acceleration = m_JumpPower;
		}

		if (pKeyState[DIK_LEFTARROW] == Lib::KeyDevice::KEY_ON)
		{
			m_Animations[WALK_ANIMATION].pData->Update();
			m_IsLeft = true;
			m_WorldPos.x -= m_MoveSpeed;
			if (m_WorldPos.x < X)
			{
				m_Pos.x -= m_MoveSpeed;
			}
		}
		else if (pKeyState[DIK_RIGHTARROW] == Lib::KeyDevice::KEY_ON)
		{
			m_WorldPos.x += m_MoveSpeed;
			if (m_WorldPos.x < X)
			{
				m_Pos.x += m_MoveSpeed;
			}
			m_Animations[WALK_ANIMATION].pData->Update();
			m_IsLeft = false;
		}
		GravityUpdate();

		RectangleCollision::RECTANGLE RectAngle;
		RectAngle.Left = m_WorldPos.x - m_Size.x / 2;
		RectAngle.Top = m_Pos.y - m_Size.y / 2;
		RectAngle.Right = m_WorldPos.x + m_Size.x / 2;
		RectAngle.Bottom = m_Pos.y + m_Size.y / 2;
		m_pCollision->SetRect(RectAngle);
		m_pCollision->ResetCollisionDiff();
	}
	
	void Player::Draw()
	{
		m_pVertex->SetInverse(m_IsLeft);
		m_pVertex->ShaderSetup();
		m_pVertex->WriteVertexBuffer();
		m_pVertex->WriteConstantBuffer(&m_Pos);
		m_pVertex->Draw();
	}


	//----------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------

	bool Player::LoadAnimation(std::string _fileName, ANIMATION_STATE _animationState)
	{
		std::string FileName = "Resource\\GameScene\\Animation\\" + _fileName;
		if (!SINGLETON_INSTANCE(Lib::Dx11::AnimationManager)->LoadAnimation(
			FileName.c_str(),
			&m_Animations[_animationState].Index)) return false;

		m_Animations[WALK_ANIMATION].pData =
			SINGLETON_INSTANCE(Lib::Dx11::AnimationManager)->GetAnimation(m_Animations[_animationState].Index);

		return true;
	}

	void Player::GravityUpdate()
	{
		if (m_Acceleration > 23.f)
		{
			m_Acceleration = 23.f;
		}

		m_Acceleration += m_Gravity;
		m_Pos.y += m_Acceleration;
	}

}
