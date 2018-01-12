/**
 * @file	Player.cpp
 * @brief	プレイヤークラス実装
 * @author	kotani
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
#include "JoyconManager\JoyconManager.h"
#include <algorithm>


namespace Game
{
	//----------------------------------------------------------------------
	// Static Private Variables
	//----------------------------------------------------------------------

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
		m_PlayerState.ChemicalData[0].Remain = m_ChemicalStock[0];
		m_PlayerState.ChemicalData[1].Remain = m_ChemicalStock[1];
		m_PlayerState.MixChemicalData[0].Remain = 0;
		m_PlayerState.MixChemicalData[1].Remain = 0;

		// プレイヤーの初期位置がスクロールの左端より左の場合.
		if (m_WorldPos.x < Application::m_WindowWidth / 2) m_Pos = m_WorldPos;
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
			m_AnimationState = JUMP_ANIMATION;
			m_IsLanding = false;
		}

		// 当たった分の差分を足す.
		m_Pos.y += m_pCollision->GetCollisionDiff().y;
		if (m_WorldPos.x <= X) m_Pos.x += m_pCollision->GetCollisionDiff().x;
		m_WorldPos += m_pCollision->GetCollisionDiff();
	}

	void Player::Update()
	{
		m_PlayerState.ChemicalData[0].Remain = m_ChemicalStock[m_SelectChemicalIndex[0]];
		m_PlayerState.ChemicalData[0].Type = static_cast<CHEMICAL_TYPE>(m_SelectChemicalIndex[0]);

		m_PlayerState.ChemicalData[1].Remain = m_ChemicalStock[m_SelectChemicalIndex[1]];
		m_PlayerState.ChemicalData[1].Type = static_cast<CHEMICAL_TYPE>(m_SelectChemicalIndex[1]);

		for (int i = 0; i < 2; i++)
		{
			if (m_pMixChemical[i] != nullptr)
				m_PlayerState.MixChemicalData[i] = m_pMixChemical[i]->GetChemicalData();
			else
				m_PlayerState.MixChemicalData[i].Remain = 0;
		}

		(this->*pControl)();

		GravityUpdate();

		m_pVertex->SetAnimation(m_Animations[m_AnimationState].pData);

		RectangleCollisionBase::RECTANGLE Rectangle;
		Rectangle.Left = m_WorldPos.x - m_Size.x / 2;
		Rectangle.Top = m_WorldPos.y - m_Size.y / 2;
		Rectangle.Right = m_WorldPos.x + m_Size.x / 2;
		Rectangle.Bottom = m_WorldPos.y + m_Size.y / 2;
		m_pCollision->SetRect(Rectangle);
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

	bool Player::LoadAnimationFile(
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
	}

	bool Player::InitAnimatin()
	{
		if (!LoadAnimationFile(
			"PlayerWalk.anim",
			WALK_ANIMATION,
			ANIMATION_PATTERN::LOOP_ANIMATION,
			0.1f)) return false;

		if (!LoadAnimationFile(
			"PlayerWait.anim",
			WAIT_ANIMATION,
			ANIMATION_PATTERN::LOOP_ANIMATION,
			0.1f)) return false;

		if (!LoadAnimationFile(
			"PlayerMixIn.anim",
			MIXIN_ANIMATION,
			ANIMATION_PATTERN::ONE_ANIMATION,
			0.07f)) return false;

		if (!LoadAnimationFile(
			"PlayerSprinkle.anim",
			SPRINKLE_ANIMATION,
			ANIMATION_PATTERN::ONE_ANIMATION,
			0.1f)) return false;

		if (!LoadAnimationFile(
			"PlayerDown.anim",
			DOWN_ANIMATION,
			ANIMATION_PATTERN::ONE_ANIMATION,
			0.1f)) return false;
		
		if (!LoadAnimationFile(
			"PlayerJump.anim",
			JUMP_ANIMATION,
			ANIMATION_PATTERN::ONE_ANIMATION,
			0.15f)) return false;

		return true;
	}

	void Player::GravityUpdate()
	{
		m_Acceleration = (std::min)(m_Acceleration, 23.f);
		m_Acceleration += m_Gravity;

		m_WorldPos.y = (m_Pos.y += m_Acceleration);
	}

	void Player::NormalControl()
	{
		const Lib::KeyDevice::KEYSTATE* pKeyState = SINGLETON_INSTANCE(Lib::InputDeviceManager)->GetKeyState();
		const Joycon::BUTTON_STATE* pLeftButtonState = SINGLETON_INSTANCE(JoyconManager)->GetJoycon(Joycon::LEFT_CONTROLLER)->GetButtonState();
		const Joycon::BUTTON_STATE* pRightButtonState = SINGLETON_INSTANCE(JoyconManager)->GetJoycon(Joycon::RIGHT_CONTROLLER)->GetButtonState();
		const Joycon* pLeftJoycon = SINGLETON_INSTANCE(JoyconManager)->GetJoycon(Joycon::LEFT_CONTROLLER);
		const Joycon* pRightJoycon = SINGLETON_INSTANCE(JoyconManager)->GetJoycon(Joycon::RIGHT_CONTROLLER);


		float X = static_cast<float>(Application::m_WindowWidth / 2);	//!< 画面中央からスクロール.

		if (pKeyState[DIK_X] == Lib::KeyDevice::KEY_PUSH)
		{
			//混ぜた薬品の切り替え.
			if (++m_SelectMixChemicalIndex >= m_MixChemicalStockMax) 
				m_SelectMixChemicalIndex = 0;
		}

		if (pLeftButtonState[Joycon::L_BUTTON] == Joycon::PUSH_BUTTON)
			m_SelectMixChemicalIndex = 0;
		else if (pRightButtonState[Joycon::R_BUTTON] == Joycon::PUSH_BUTTON)
			m_SelectMixChemicalIndex = 1;

		if (pKeyState[DIK_A] == Lib::KeyDevice::KEY_PUSH ||
			pLeftButtonState[Joycon::ZL_BUTTON] == Joycon::PUSH_BUTTON)
		{
			if (++m_SelectChemicalIndex[0] >= m_NormalChemicalMax)
				m_SelectChemicalIndex[0] = 0;
		}

		if (pKeyState[DIK_S] == Lib::KeyDevice::KEY_PUSH ||
			pRightButtonState[Joycon::ZR_BUTTON] == Joycon::PUSH_BUTTON)
		{
			if (++m_SelectChemicalIndex[1] >= m_NormalChemicalMax)
				m_SelectChemicalIndex[1] = 0;
		}

		if ((pKeyState[DIK_D] == Lib::KeyDevice::KEY_PUSH ||
			pRightButtonState[Joycon::X_BUTTON] == Joycon::PUSH_BUTTON) &&
			m_IsLanding)
		{
			//混ぜる動作.
			m_AnimationState = MIXIN_ANIMATION;
			m_Animations[m_AnimationState].pData->AnimationStart();
			pControl = &Player::ChemicalCreateControl;
		}
		else if ((pKeyState[DIK_C] == Lib::KeyDevice::KEY_PUSH ||
			abs(pRightJoycon->GetGyroSensor().z) > 7.3) &&
			m_pMixChemical[m_SelectMixChemicalIndex] != nullptr &&
			m_IsLanding)
		{
			//振る動作.
			m_AnimationState = WALK_ANIMATION; // 仮動作.
			m_Animations[m_AnimationState].pData->AnimationStart();
			pControl = &Player::ShakeControl;
		}
		else if ((pKeyState[DIK_Z] == Lib::KeyDevice::KEY_PUSH ||
			pRightJoycon->GetGyroSensor().y < -5.3) &&
			m_IsLanding)
		{
			// 薬品をかける動作に移行.
			if (m_pMixChemical[m_SelectMixChemicalIndex] != nullptr &&
				!m_pMixChemical[m_SelectMixChemicalIndex]->GetIsSprinkle())
			{
				m_AnimationState = SPRINKLE_ANIMATION;
				m_Animations[m_AnimationState].pData->AnimationStart();
				pControl = &Player::SprinkleControl;
			}
		}
		else if ((pKeyState[DIK_UPARROW] == Lib::KeyDevice::KEY_PUSH ||
			pRightButtonState[Joycon::B_BUTTON] == Joycon::PUSH_BUTTON) &&
			m_IsLanding)
		{
			m_AnimationState = JUMP_ANIMATION;
			m_Animations[m_AnimationState].pData->AnimationStart();
			m_Acceleration = m_JumpPower;
		}
		else if (pKeyState[DIK_LEFTARROW] == Lib::KeyDevice::KEY_ON ||
			pLeftJoycon->GetAnalogStick().x < -0.5)
		{
			if (m_IsLanding) m_AnimationState = WALK_ANIMATION;
			m_Animations[m_AnimationState].pData->Update();
			m_IsLeft = true;
			m_WorldPos.x -= m_MoveSpeed;

			if (m_WorldPos.x <= X) m_WorldPos.x = (m_Pos.x -= m_MoveSpeed);
		}
		else if (pKeyState[DIK_RIGHTARROW] == Lib::KeyDevice::KEY_ON ||
			pLeftJoycon->GetAnalogStick().x > +0.5)
		{
			if (m_IsLanding) m_AnimationState = WALK_ANIMATION;
			m_Animations[m_AnimationState].pData->Update();
			m_IsLeft = false;
			m_WorldPos.x += m_MoveSpeed;

			if (m_WorldPos.x <= X) m_WorldPos.x = (m_Pos.x += m_MoveSpeed);
		}
		else
		{
			if (m_IsLanding) m_AnimationState = WAIT_ANIMATION;
			m_Animations[m_AnimationState].pData->Update();
		}
	}

	void Player::SprinkleControl()
	{
		if (!m_Animations[m_AnimationState].pData->Update()) return;

		m_pMixChemical[m_SelectMixChemicalIndex]->Sprinkle(m_WorldPos, m_IsLeft);
		pControl = &Player::NormalControl;
	}

	void Player::ChemicalCreateControl()
	{
		if (m_Animations[m_AnimationState].pData->Update())
		{
			CHEMICAL_TYPE Type1 = static_cast<CHEMICAL_TYPE>(m_SelectChemicalIndex[0]);
			CHEMICAL_TYPE Type2 = static_cast<CHEMICAL_TYPE>(m_SelectChemicalIndex[1]);

			if (m_pMixChemical[0] == nullptr)
			{
				m_pMixChemical[0] = ChemicalFactory::GetInstance().
					Create(ChemicalFactory::Types(Type1,Type2));
			}
			else if (m_pMixChemical[1] == nullptr)
			{
				m_pMixChemical[1] = ChemicalFactory::GetInstance().
					Create(ChemicalFactory::Types(Type1, Type2));
			}
			else
			{
				m_pMixChemical[m_SelectMixChemicalIndex]->Finalize();
				SafeDelete(m_pMixChemical[m_SelectMixChemicalIndex]);

				m_pMixChemical[m_SelectMixChemicalIndex] = ChemicalFactory::GetInstance().
					Create(ChemicalFactory::Types(Type1, Type2));
			}
			pControl = &Player::NormalControl;
		}
	}

	void Player::ShakeControl()
	{
		const Lib::KeyDevice::KEYSTATE* pKeyState = SINGLETON_INSTANCE(Lib::InputDeviceManager)->GetKeyState();
		const Joycon* pRightJoycon = SINGLETON_INSTANCE(JoyconManager)->GetJoycon(Joycon::RIGHT_CONTROLLER);

		if (pKeyState[DIK_C] == Lib::KeyDevice::KEY_ON ||
			abs(pRightJoycon->GetGyroSensor().z) > 1.5f ||
			abs(pRightJoycon->GetGyroSensor().x) > 1.5f ||
			abs(pRightJoycon->GetGyroSensor().y) > 1.5f)
		{
			m_Animations[m_AnimationState].pData->Update(); 
			m_pMixChemical[m_SelectMixChemicalIndex]->Shake();
		}
		else
		{
			pControl = &Player::NormalControl;
		}
	}

	void Player::DamageControl()
	{
	}
}
