/**
 * @file	Player.cpp
 * @brief	プレイヤークラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Player.h"
#include "PlayerUIManager\PlayerUIManager.h"
#include "Application\Application.h"
#include "ChemicalFactory\ChemicalFactory.h"
#include "Application\Scene\GameScene\GameDefine.h"
#include "..\..\GameDataManager\GameDataManager.h"
#include "..\..\..\CollisionManager\CollisionManager.h"
#include "Application\Scene\GameScene\CollisionManager\CollisionBase\PlayerCollision\PlayerCollision.h"

#include "DirectX11\AnimationManager\Dx11AnimationManager.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "InputDeviceManager\InputDeviceManager.h"
#include "InputDeviceManager\KeyDevice\KeyDevice.h"
#include "TaskManager\TaskManager.h"

#include <algorithm>

namespace Game
{
	const float Player::m_Gravity = 0.8f;
	const float Player::m_JumpPower = -25;
	const float Player::m_MoveSpeed = 10;

	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	
	Player::Player(const D3DXVECTOR2& _worldPos) :
		m_SelectMixChemicalIndex(0),
		m_pCollision(nullptr),
		m_WorldPos(_worldPos),
		m_Acceleration(0),
		m_IsLeft(false),
		m_IsLanding(false),
		m_AnimationState(WAIT_ANIMATION)
	{
		m_Size = D3DXVECTOR2(120.f, 240.f);
		m_Pos = D3DXVECTOR2(960.f, 400.f);

		m_SelectChemicalIndex[0] = 0;
		m_SelectChemicalIndex[1] = 1;

		for (int i = 0; i < m_NormalChemicalMax; i++)
		{
			m_ChemicalStock[i] = 100;
		}

		m_PlayerState.Pos = m_Pos;
		m_PlayerState.Life = 100;
		m_PlayerState.ChemicalRemain[0] = m_ChemicalStock[0];
		m_PlayerState.ChemicalRemain[1] = m_ChemicalStock[1];
		m_PlayerState.MixChemicalRemain[0] = 0;
		m_PlayerState.MixChemicalRemain[1] = 0;

		// プレイヤーの初期位置がスクロールの左端より左の場合
		if (m_WorldPos.x < Application::m_WindowWidth / 2)
		{
			m_Pos = m_WorldPos;
		}
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
		ChemicalFactory::GetInstance().Initialize();

		m_pPlayerUIManager = new PlayerUIManager(&m_PlayerState);
		m_pPlayerUIManager->Initialize();

		m_pCollisionTask = new CollisionTask();
		m_pCollisionTask->SetObject(this);
		SINGLETON_INSTANCE(CollisionTaskManager)->AddTask(m_pCollisionTask);

		if (!InitAnimatin()) return false;

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\GameScene\\Texture\\Player.png",
			&m_TextureIndex)) return false;

		if (!CreateVertex2D()) return false;
		m_pVertex->SetUV(&D3DXVECTOR2(0.f, 0.f), &D3DXVECTOR2(1.f, 1.f));
		m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pVertex->SetAnimation(m_Animations[WAIT_ANIMATION].pData);

		m_pCollision = new PlayerCollision();
		SINGLETON_INSTANCE(CollisionManager)->AddCollision(m_pCollision);
		SINGLETON_INSTANCE(GameDataManager)->SetPlayerPosPtr(&m_WorldPos);

		pControl = &Player::NormalControl;

		return true;
	}
	
	void Player::Finalize()
	{
		for (int i = 0; i < m_MixChemicalStockMax; i++)
		{
			if (m_pMixChemical[i] != nullptr)
			{
				m_pMixChemical[i]->Finalize();
				SafeDelete(m_pMixChemical[i]);
			}
		}
		SINGLETON_INSTANCE(CollisionManager)->RemoveCollision(m_pCollision);

		ReleaseVertex2D();

		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);
		for (const auto& itr : m_Animations)
		{
			SINGLETON_INSTANCE(Lib::Dx11::AnimationManager)->
				ReleaseAnimation(itr.Index);
		}

		SINGLETON_INSTANCE(CollisionTaskManager)->RemoveStartUpTask(m_pCollisionTask);
		SafeDelete(m_pCollisionTask);

		m_pPlayerUIManager->Finalize();
		SafeDelete(m_pPlayerUIManager);

		ChemicalFactory::GetInstance().Finalize();

		SafeDelete(m_pCollision);

		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
	}

	void Player::CollisionTaskUpdate()
	{
		float X = static_cast<float>(Application::m_WindowWidth / 2);	//!< 画面中央からスクロール.

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
		if (m_WorldPos.x <= X)
		{
			m_Pos.x += m_pCollision->GetCollisionDiff().x;
		}
		m_WorldPos += m_pCollision->GetCollisionDiff() ;
	}

	void Player::Update()
	{
		m_PlayerState.ChemicalRemain[0] = m_ChemicalStock[m_SelectChemicalIndex[0]];
		m_PlayerState.ChemicalRemain[1] = m_ChemicalStock[m_SelectChemicalIndex[1]];

		for (int i = 0; i < 2; i++)
		{
			if (m_pMixChemical[i] != nullptr)
			{
				m_PlayerState.MixChemicalRemain[i] = m_pMixChemical[i]->GetRemain();
			}
			else
			{
				m_PlayerState.MixChemicalRemain[i] = 0;
			}
		}

		(this->*pControl)();
		GravityUpdate();

		m_pVertex->SetAnimation(m_Animations[m_AnimationState].pData);

		RectangleCollisionBase::RECTANGLE RectAngle;
		RectAngle.Left = m_WorldPos.x - m_Size.x / 2;
		RectAngle.Top = m_WorldPos.y - m_Size.y / 2;
		RectAngle.Right = m_WorldPos.x + m_Size.x / 2;
		RectAngle.Bottom = m_WorldPos.y + m_Size.y / 2;
		m_pCollision->SetRect(RectAngle);
		m_pCollision->ResetCollisionDiff();
		
		m_PlayerState.Pos = m_Pos;
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

	bool Player::InitAnimatin()
	{
		using ANIMATION_PATTERN = Lib::Dx11::IAnimation::ANIMATION_PATTERN;

		auto LoadAnimation = [this](
			std::string		  _fileName,
			ANIMATION_STATE   _animationState,
			ANIMATION_PATTERN _animationPattern,
			float			  _animationSpeed)
		{
			std::string FileName = "Resource\\GameScene\\Animation\\" + _fileName;
			if (!SINGLETON_INSTANCE(Lib::Dx11::AnimationManager)->LoadAnimation(
				FileName.c_str(),
				&m_Animations[_animationState].Index)) return false;

			m_Animations[_animationState].pData =
				SINGLETON_INSTANCE(Lib::Dx11::AnimationManager)->GetAnimation(m_Animations[_animationState].Index);
			
			m_Animations[_animationState].pData->
				SetAnimationPattern(_animationPattern);
			m_Animations[_animationState].pData->SetAnimationSpeed(_animationSpeed);

			return true;
		};

		if (!LoadAnimation(
			"PlayerWalk.anim",
			WALK_ANIMATION,
			ANIMATION_PATTERN::LOOP_ANIMATION,
			0.1f)) return false;

		if (!LoadAnimation(
			"PlayerWait.anim",
			WAIT_ANIMATION,
			ANIMATION_PATTERN::LOOP_ANIMATION,
			0.1f)) return false;

		if (!LoadAnimation(
			"PlayerMixIn.anim",
			MIXIN_ANIMATION,
			ANIMATION_PATTERN::ONE_ANIMATION,
			0.07f)) return false;

		if (!LoadAnimation(
			"PlayerSprinkle.anim",
			SPRINKLE_ANIMATION,
			ANIMATION_PATTERN::ONE_ANIMATION,
			0.1f)) return false;

		if (!LoadAnimation(
			"PlayerDown.anim",
			DOWN_ANIMATION,
			ANIMATION_PATTERN::ONE_ANIMATION,
			0.1f)) return false;

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
		m_WorldPos.y = m_Pos.y;
	}

	void Player::NormalControl()
	{
		const Lib::KeyDevice::KEYSTATE* pKeyState = SINGLETON_INSTANCE(Lib::InputDeviceManager)->GetKeyState();
		float X = static_cast<float>(Application::m_WindowWidth / 2);	//!< 画面中央からスクロール.

		if (pKeyState[DIK_X] == Lib::KeyDevice::KEY_PUSH)
		{
			//混ぜた薬品の切り替え.
			m_SelectMixChemicalIndex++;
			if (m_SelectMixChemicalIndex >= m_MixChemicalStockMax)
			{
				m_SelectMixChemicalIndex = 0;
			}
		}

		if(pKeyState[DIK_D] == Lib::KeyDevice::KEY_PUSH)
		{
			//混ぜる動作.
			m_AnimationState = MIXIN_ANIMATION;
			m_Animations[m_AnimationState].pData->AnimationStart();
			pControl = &Player::ChemicalCreateControl;
		}
		else if (pKeyState[DIK_Z] == Lib::KeyDevice::KEY_PUSH)
		{
			// 薬品をかける動作に移行.
			if (m_pMixChemical[m_SelectMixChemicalIndex] != nullptr)
			{
				m_AnimationState = SPRINKLE_ANIMATION;
				m_Animations[m_AnimationState].pData->AnimationStart();
				pControl = &Player::SprinkleControl;
			}
		}
		else if (pKeyState[DIK_UPARROW] == Lib::KeyDevice::KEY_PUSH &&
			m_IsLanding)
		{
			m_Acceleration = m_JumpPower;
		}
		else if (pKeyState[DIK_LEFTARROW] == Lib::KeyDevice::KEY_ON)
		{
			m_AnimationState = WALK_ANIMATION;
			m_Animations[m_AnimationState].pData->Update();
			m_IsLeft = true;
			m_WorldPos.x -= m_MoveSpeed;
			if (m_WorldPos.x <= X)
			{
				m_Pos.x -= m_MoveSpeed;
				m_WorldPos.x = m_Pos.x;
			}
		}
		else if (pKeyState[DIK_RIGHTARROW] == Lib::KeyDevice::KEY_ON)
		{
			m_AnimationState = WALK_ANIMATION;
			m_Animations[m_AnimationState].pData->Update();
			m_IsLeft = false;
			m_WorldPos.x += m_MoveSpeed;
			if (m_WorldPos.x <= X)
			{
				m_Pos.x += m_MoveSpeed;
				m_WorldPos.x = m_Pos.x;
			}
		}
		else
		{
			m_AnimationState = WAIT_ANIMATION;
			m_Animations[m_AnimationState].pData->Update();
		}
	}

	void Player::SprinkleControl()
	{
		if (m_Animations[m_AnimationState].pData->Update())
		{
			m_pMixChemical[m_SelectMixChemicalIndex]->Sprinkle(m_WorldPos, m_IsLeft);
			pControl = &Player::NormalControl;
		}
	}

	void Player::ChemicalCreateControl()
	{
		if (m_Animations[m_AnimationState].pData->Update())
		{
			if (m_pMixChemical[0] == nullptr)
			{
				m_pMixChemical[0] = ChemicalFactory::GetInstance().
					Create(ChemicalFactory::Types(BLUE_CHEMICAL, RED_CHEMICAL));
			}
			else if (m_pMixChemical[1] == nullptr)
			{
				m_pMixChemical[1] = ChemicalFactory::GetInstance().
					Create(ChemicalFactory::Types(BLUE_CHEMICAL, RED_CHEMICAL));
			}
			else
			{
				m_pMixChemical[m_SelectMixChemicalIndex]->Finalize();
				SafeDelete(m_pMixChemical[m_SelectMixChemicalIndex]);

				m_pMixChemical[m_SelectMixChemicalIndex] = ChemicalFactory::GetInstance().
					Create(ChemicalFactory::Types(BLUE_CHEMICAL, RED_CHEMICAL));
			}
			pControl = &Player::NormalControl;
		}
	}

	void Player::MixControl()
	{
	}

	void Player::DamageControl()
	{
	}
}
