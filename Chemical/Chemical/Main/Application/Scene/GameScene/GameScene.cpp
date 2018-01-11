/**
 * @file	GameScene.cpp
 * @brief	ゲームシーンクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "GameScene.h"

#include "Debugger\Debugger.h"
#include "DirectX11\GraphicsDevice\Dx11GraphicsDevice.h"
#include "DirectX11\ShaderManager\Dx11ShaderManager.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "DirectX11\AnimationManager\Dx11AnimationManager.h"
#include "InputDeviceManager\InputDeviceManager.h"
#include "SoundDevice\SoundDevice.h"
#include "SoundManager\SoundManager.h"
#include "TaskManager\TaskBase\UpdateTask\UpdateTask.h"
#include "TaskManager\TaskBase\DrawTask\DrawTask.h"
#include "CollisionManager\CollisionManager.h"
#include "CollisionTask\CollisionTask.h"
#include "EventManager\EventManager.h"
#include "JoyconManager\JoyconManager.h"

namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	GameScene::GameScene(int _sceneId) :
		SceneBase(_sceneId)
	{
	}

	GameScene::~GameScene()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool GameScene::Initialize()
	{
		SINGLETON_CREATE(Lib::UpdateTaskManager);
		SINGLETON_CREATE(Lib::Draw2DTaskManager);

		SINGLETON_CREATE(Lib::Dx11::ShaderManager);
		if (!SINGLETON_INSTANCE(Lib::Dx11::ShaderManager)->Initialize(
			SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)))
		{
			OutputErrorLog("シェーダー管理クラスの生成に失敗しました");
			return false;
		}

		SINGLETON_CREATE(Lib::Dx11::TextureManager);
		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->Initialize(
			SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)))
		{
			OutputErrorLog("テクスチャ管理クラスの生成に失敗しました");
			return false;
		}

		SINGLETON_CREATE(Lib::Dx11::AnimationManager);
		if (!SINGLETON_INSTANCE(Lib::Dx11::AnimationManager)->Initialize())
		{
			OutputErrorLog("アニメーション管理クラスの生成に失敗しました");
			return false;
		}

		SINGLETON_CREATE(Lib::SoundDevice);
		if (!SINGLETON_INSTANCE(Lib::SoundDevice)->Initialize(
			SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)->GetMainWindowHandle()))
		{
			OutputErrorLog("サウンドデバイスの生成に失敗しました");
			return false;
		}

		SINGLETON_CREATE(Lib::SoundManager);
		if (!SINGLETON_INSTANCE(Lib::SoundManager)->Initialize(SINGLETON_INSTANCE(Lib::SoundDevice)))
		{
			OutputErrorLog("サウンド管理クラスの生成に失敗しました");
			return false;
		}

		SINGLETON_CREATE(Lib::EventManager);
		SINGLETON_CREATE(CollisionManager);
		SINGLETON_CREATE(CollisionTaskManager);

		SINGLETON_CREATE(JoyconManager);
		SINGLETON_INSTANCE(JoyconManager)->Connect(Joycon::LEFT_CONTROLLER);
		SINGLETON_INSTANCE(JoyconManager)->Connect(Joycon::RIGHT_CONTROLLER);

		m_pObjectManager = new ObjectManager();
		if (!m_pObjectManager->Initialize())
		{
			OutputErrorLog("オブジェクト管理クラスの生成に失敗しました");
			return false;
		}

		m_State = UPDATE_STATE;

		return true;
	}

	void GameScene::Finalize()
	{
		m_pObjectManager->Finalize();
		SafeDelete(m_pObjectManager);

		SINGLETON_INSTANCE(JoyconManager)->Disconnect(Joycon::LEFT_CONTROLLER);
		SINGLETON_INSTANCE(JoyconManager)->Disconnect(Joycon::RIGHT_CONTROLLER);
		SINGLETON_DELETE(JoyconManager);

		SINGLETON_DELETE(CollisionTaskManager);
		SINGLETON_DELETE(CollisionManager);
		SINGLETON_DELETE(Lib::EventManager);

		if (SINGLETON_INSTANCE(Lib::SoundManager) != nullptr)
		{
			SINGLETON_INSTANCE(Lib::SoundManager)->Finalize();
			SINGLETON_DELETE(Lib::SoundManager);
		}

		if (SINGLETON_INSTANCE(Lib::SoundDevice) != nullptr)
		{
			SINGLETON_INSTANCE(Lib::SoundDevice)->Finalize();
			SINGLETON_DELETE(Lib::SoundDevice);
		}

		if (SINGLETON_INSTANCE(Lib::Dx11::AnimationManager) != nullptr)
		{
			SINGLETON_INSTANCE(Lib::Dx11::AnimationManager)->Finalize();
			SINGLETON_DELETE(Lib::Dx11::AnimationManager);
		}

		if (SINGLETON_INSTANCE(Lib::Dx11::TextureManager) != nullptr)
		{
			SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->Finalize();
			SINGLETON_DELETE(Lib::Dx11::TextureManager);
		}

		if (SINGLETON_INSTANCE(Lib::Dx11::ShaderManager) != nullptr)
		{
			SINGLETON_INSTANCE(Lib::Dx11::ShaderManager)->Finalize();
			SINGLETON_DELETE(Lib::Dx11::ShaderManager);
		}

		SINGLETON_DELETE(Lib::Draw2DTaskManager);
		SINGLETON_DELETE(Lib::UpdateTaskManager);

		m_State = INIT_STATE;
	}

	void GameScene::Update()
	{
		// デバイスの入力チェック.
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyUpdate();
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->MouseUpdate();
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyCheck(DIK_UPARROW);
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyCheck(DIK_LEFTARROW);
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyCheck(DIK_RIGHTARROW);
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyCheck(DIK_Z);
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyCheck(DIK_X);
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyCheck(DIK_A);
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyCheck(DIK_S);
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyCheck(DIK_D);
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyCheck(DIK_C);

		SINGLETON_INSTANCE(JoyconManager)->CheckButton(Joycon::RIGHT_CONTROLLER, Joycon::B_BUTTON);
		SINGLETON_INSTANCE(JoyconManager)->CheckButton(Joycon::RIGHT_CONTROLLER, Joycon::X_BUTTON);
		SINGLETON_INSTANCE(JoyconManager)->CheckButton(Joycon::RIGHT_CONTROLLER, Joycon::ZR_BUTTON);
		SINGLETON_INSTANCE(JoyconManager)->CheckButton(Joycon::RIGHT_CONTROLLER, Joycon::R_BUTTON);
		SINGLETON_INSTANCE(JoyconManager)->CheckButton(Joycon::LEFT_CONTROLLER, Joycon::ZL_BUTTON);
		SINGLETON_INSTANCE(JoyconManager)->CheckButton(Joycon::LEFT_CONTROLLER, Joycon::L_BUTTON);


		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->Run();
		SINGLETON_INSTANCE(CollisionManager)->Run();
		SINGLETON_INSTANCE(CollisionTaskManager)->Run();

		SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)->BeginScene(Lib::Dx11::GraphicsDevice::BACKBUFFER_TARGET);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->Run();
		SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)->EndScene();
	}
}
