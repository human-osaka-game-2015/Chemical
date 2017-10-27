/**
 * @file	TitleScene.cpp
 * @brief	タイトルシーンクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "TitleScene.h"

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
#include "TitleObjectManager\TitleObjectManager.h"
#include "TitleObjectManager\TitleMenu\MenuCursorEvent\MenuCursorEvent.h"
#include "TitleDefine.h"


namespace Title
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	TitleScene::TitleScene(int _sceneId) :
		Lib::SceneBase(_sceneId),
		m_pObjectManager(nullptr)
	{
	}

	TitleScene::~TitleScene()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool TitleScene::Initialize()
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

		m_pObjectManager = new Title::ObjectManager();
		if (!m_pObjectManager->Initialize())
		{
			return false;
		}

		m_pReciveFunc = std::bind(&TitleScene::ReciveEvent, this, std::placeholders::_1);
		m_pEventListener = new Lib::EventListener(&m_pReciveFunc);

		SINGLETON_INSTANCE(Lib::EventManager)->AddEventListener(m_pEventListener, 
			TO_STRING(TITLE_MENU_GROUP));

		m_State = UPDATE_STATE;

		return true;
	}

	void TitleScene::Finalize()
	{
		SINGLETON_INSTANCE(Lib::EventManager)->RemoveEventListener(m_pEventListener, 
			TO_STRING(TITLE_MENU_GROUP));

		SafeDelete(m_pEventListener);

		if (m_pObjectManager != nullptr)
		{
			m_pObjectManager->Finalize();
			SafeDelete(m_pObjectManager);
		}

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

	void TitleScene::Update()
	{
		// デバイスの入力チェック.
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyUpdate();
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyCheck(DIK_UP);
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyCheck(DIK_DOWN);
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyCheck(DIK_SPACE);

		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->Run();

		SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)->BeginScene(Lib::Dx11::GraphicsDevice::BACKBUFFER_TARGET);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->Run();
		SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)->EndScene();
	}

	void TitleScene::ReciveEvent(Lib::EventBase* _pEvent)
	{
		switch (_pEvent->GetEventID())
		{
		case TITLE_MENU_EVENT:
			MenuCursorEvent* pEvent = reinterpret_cast<MenuCursorEvent*>(_pEvent);
			switch (pEvent->GetEventType())
			{
			case MenuCursorEvent::START_BUTTON_PUSH:
				m_NextSceneID = Application::SELECT_SCENE_ID;
				m_State = FINAL_STATE;
				break;
			case MenuCursorEvent::OPTION_BUTTON_PUSH:
				// オプションに関しては未実装.
				break;
			case MenuCursorEvent::STAFF_BUTTON_PUSH:
				break;
			case MenuCursorEvent::END_BUTTON_PUSH:
				m_NextSceneID = Application::END_SCENE_ID;
				m_State = FINAL_STATE;
				break;
			}
			
			break;
		}
	}
}
