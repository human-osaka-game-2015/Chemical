/**
 * @file   SelectScene.cpp
 * @brief  SelectSceneクラスの実装
 * @author kotani
 */
#include "SelectScene.h"
#include "SelectDefine.h"
#include "Application\Application.h"
#include "SelectObjectManager\SelectObjectManager.h"
#include "SelectManager\SelectManager.h"
#include "SelectGameStartEvent\SelectGameStartEvent.h"

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
#include "DirectX11\Font\Dx11Font.h"


namespace Select
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	SelectScene::SelectScene(int _sceneId) :
	SceneBase(_sceneId)
	{
	}
	
	SelectScene::~SelectScene()
	{
	}
	
	
	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool SelectScene::Initialize()
	{
		SINGLETON_CREATE(Lib::UpdateTaskManager);
		SINGLETON_CREATE(Lib::Draw2DTaskManager);
		SINGLETON_CREATE(SelectManager);

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

		m_State = UPDATE_STATE;

		m_pObjectManager = new ObjectManager();
		if (!m_pObjectManager->Initialize())
		{
			return false;
		}

		m_pReciveFunc = std::bind(&SelectScene::ReciveEvent, this, std::placeholders::_1);
		m_pEventListener = new Lib::EventListener(&m_pReciveFunc);
		SINGLETON_INSTANCE(Lib::EventManager)->AddEventListener(m_pEventListener,"");
		return true;
	}
	
	void SelectScene::Finalize()
	{
		m_pObjectManager->Finalize();
		SafeDelete(m_pObjectManager);

		SINGLETON_DELETE(Lib::EventManager);
		SafeDelete(m_pEventListener);
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
	
		SINGLETON_DELETE(SelectManager);
		SINGLETON_DELETE(Lib::Draw2DTaskManager);
		SINGLETON_DELETE(Lib::UpdateTaskManager);
	
		m_State = INIT_STATE;
	}
	
	void SelectScene::Update()
	{
		// デバイスの入力チェック.
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyUpdate();
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->MouseUpdate();
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyCheck(DIK_UPARROW);
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyCheck(DIK_LEFTARROW);
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyCheck(DIK_RIGHTARROW);
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyCheck(DIK_DOWNARROW);
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyCheck(DIK_RETURN);

		SINGLETON_INSTANCE(SelectManager)->Update();
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->Run();

		SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)->BeginScene(Lib::Dx11::GraphicsDevice::BACKBUFFER_TARGET);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->Run();
		SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)->EndScene();
	}


	//----------------------------------------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------------------------------------
	
	void SelectScene::ReciveEvent(Lib::EventBase* _pEvent)
	{
		switch (_pEvent->GetEventID())
		{
		case GAME_START_EVENT:
			GameStartEvent* pEvent = reinterpret_cast<GameStartEvent*>(_pEvent);
			switch (pEvent->GetEventType())
			{
			case GameStartEvent::START_BUTTON_PUSH:
				m_NextSceneID = Application::GAME_SCENE_ID;
				m_State = FINAL_STATE;
				break;
			}
			break;
		}
	}
}
