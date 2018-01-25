/**
 * @file	StaffScene.cpp
 * @brief	スタッフシーンクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "StaffScene.h"

#include "Application\Application.h"
#include "Debugger\Debugger.h"
#include "DirectX11\GraphicsDevice\Dx11GraphicsDevice.h"
#include "DirectX11\ShaderManager\Dx11ShaderManager.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "InputDeviceManager\InputDeviceManager.h"
#include "SoundDevice\SoundDevice.h"
#include "SoundManager\SoundManager.h"
#include "TaskManager\TaskBase\UpdateTask\UpdateTask.h"
#include "TaskManager\TaskBase\DrawTask\DrawTask.h"
#include "EventManager\EventManager.h"
#include "EventManager\EventBase\EventBase.h"
#include "StaffObjectManager\StaffObjectManager.h"
#include "JoyconManager\JoyconManager.h"
#include "StaffDefine.h"


namespace Staff
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	StaffScene::StaffScene(int _sceneID) :
		SceneBase(_sceneID)
	{
	}

	StaffScene::~StaffScene()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool StaffScene::Initialize()
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

		m_pReciveFunc = std::bind(&StaffScene::ReciveEvent, this, std::placeholders::_1);
		m_pEventListener = new Lib::EventListener(&m_pReciveFunc);
		SINGLETON_INSTANCE(Lib::EventManager)->AddEventListener(
			m_pEventListener,
			TO_STRING(STAFF_GROUP));

		m_pObjectManager = new StaffObjectManager();
		if (!m_pObjectManager->Initialize())
		{
			OutputErrorLog("オブジェクト管理クラスの初期化に失敗しました");
			return false;
		}

		m_State = UPDATE_STATE;

		return true;
	}

	void StaffScene::Finalize()
	{
		m_pObjectManager->Finalize();
		SafeDelete(m_pObjectManager);

		SINGLETON_INSTANCE(Lib::EventManager)->RemoveEventListener(
			m_pEventListener,
			TO_STRING(STAFF_GROUP));
		SafeDelete(m_pEventListener);

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

	void StaffScene::Update()
	{
		// デバイスの入力チェック.
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyUpdate();
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyCheck(DIK_SPACE);

		SINGLETON_INSTANCE(JoyconManager)->CheckButton(Joycon::RIGHT_CONTROLLER, Joycon::A_BUTTON);

		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->Run();

		SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)->BeginScene(Lib::Dx11::GraphicsDevice::BACKBUFFER_TARGET);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->Run();
		SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)->EndScene();
	}


	//----------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------
	void StaffScene::ReciveEvent(Lib::EventBase* _pEvent)
	{
		switch (_pEvent->GetEventID())
		{
		case STAFF_EVENT:
			m_NextSceneID = Application::TITLE_SCENE_ID;
			m_State = FINAL_STATE;
			break;
		}
	}
}
