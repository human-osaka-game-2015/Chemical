/**
 * @file	Application.h
 * @brief	アプリケーションクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Application.h"

#include "Debugger\Debugger.h"
#include "DirectX11\GraphicsDevice\Dx11GraphicsDevice.h"
#include "InputDeviceManager\InputDeviceManager.h"
#include "JoyconManager\JoyconManager.h"
#include "Scene\TitleScene\TitleScene.h"
#include "Scene\GameScene\GameScene.h"
#include "Scene\SelectScene\SelectScene.h"
#include "Scene\StaffScene\StaffScene.h"
#include "Scene\ResultScene\ResultScene.h"


//----------------------------------------------------------------------
// Static Public Variables
//----------------------------------------------------------------------
const int Application::m_WindowWidth = 1920;
const int Application::m_WindowHeight = 1080;


//----------------------------------------------------------------------
// Static Private Variables
//----------------------------------------------------------------------
//#ifdef _DEBUG
const DWORD Application::m_WindowStyle = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX | WS_VISIBLE;
//#else
//const DWORD Application::m_WindowStyle = WS_VISIBLE | WS_POPUP;
//#endif 


//----------------------------------------------------------------------
// Constructor	Destructor
//----------------------------------------------------------------------
Application::Application() :
	m_pMainWindow(nullptr),
	m_pSceneManager(nullptr),
	m_pGameScene(nullptr)
{
}

Application::~Application()
{
}


//----------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------
bool Application::Initialize()
{
	Lib::Debugger::CheckMemoryLeak();	// メモリリーク検出関数.

	if (!CreateMainWindow())		return false;
	if (!CreateGraphicsDevice())	return false;
	if (!CreateInputDevice())		return false;
	if (!CreateSceneManager())		return false;

	return true;
}

void Application::Finalize()
{
	ReleaseSceneManager();
	ReleaseInputDevice();
	ReleaseGraphicsDevice();
	ReleaseMainWindow();
}

void Application::Run()
{
	while (1)
	{
		// ウィンドウの更新処理を実行.
		if (!m_pMainWindow->Update())
		{
			// シーンの更新処理を実行.
			if (m_pSceneManager->Update())	break;
		}
		else
		{
			break;
		}
	}
}


//----------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------
bool Application::CreateMainWindow()
{
	m_pMainWindow = new Lib::Window();
	if (!m_pMainWindow->Initialize(TEXT("ProgramDemo"), m_WindowWidth, m_WindowHeight, m_WindowStyle))
	{
		OutputErrorLog("メインウィンドウ生成に失敗しました");
		SafeDelete(m_pMainWindow);
		return false;
	}

	return true;
}

bool Application::CreateGraphicsDevice()
{
	SINGLETON_CREATE(Lib::Dx11::GraphicsDevice);
	if (!SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)->Initialize(m_pMainWindow->GetWindowHandle()))
	{
		OutputErrorLog("グラフィックデバイス生成に失敗しました");
		SINGLETON_DELETE(Lib::Dx11::GraphicsDevice);
		return false;
	}

#ifndef _DEBUG
	SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)->SetFullScreen(true);
#endif

	return true;
}

bool Application::CreateInputDevice()
{
	SINGLETON_CREATE(Lib::InputDeviceManager);
	if (!SINGLETON_INSTANCE(Lib::InputDeviceManager)->Initialize(
		SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)->GetMainWindowHandle()))
	{
		OutputErrorLog("入力デバイス管理クラス生成に失敗しました");
		SINGLETON_DELETE(Lib::InputDeviceManager);
		return false;
	}

	if (!SINGLETON_INSTANCE(Lib::InputDeviceManager)->CreateDevice(Lib::InputDeviceManager::KEYDEVICE_TYPE))
	{
		OutputErrorLog("キーデバイス生成に失敗しました");
		SINGLETON_DELETE(Lib::InputDeviceManager);
		return false;
	}

	if (!SINGLETON_INSTANCE(Lib::InputDeviceManager)->CreateDevice(Lib::InputDeviceManager::MOUSEDEVICE_TYPE))
	{
		OutputErrorLog("マウスデバイス生成に失敗しました");
		SINGLETON_DELETE(Lib::InputDeviceManager);
		return false;
	}

	if (!SINGLETON_INSTANCE(Lib::InputDeviceManager)->CreateDevice(Lib::InputDeviceManager::GAMEPAD_TYPE))
	{
		OutputErrorLog("ゲームパッド生成に失敗しました");
		SINGLETON_DELETE(Lib::InputDeviceManager);
		return false;
	}

	SINGLETON_CREATE(JoyconManager);
	SINGLETON_INSTANCE(JoyconManager)->Connect(Joycon::LEFT_CONTROLLER);
	SINGLETON_INSTANCE(JoyconManager)->Connect(Joycon::RIGHT_CONTROLLER);

	return true;
}

bool Application::CreateSceneManager()
{
	m_pSceneManager = new Lib::SceneManager();
	if(!m_pSceneManager->Initialize())
	{
		SafeDelete(m_pSceneManager);
		return false;
	}

	m_pTitleScene	= new Title::TitleScene(TITLE_SCENE_ID);
	m_pGameScene	= new Game::GameScene(GAME_SCENE_ID);
	m_pSelectScene	= new Select::SelectScene(SELECT_SCENE_ID);
	m_pStaffScene	= new Staff::StaffScene(STAFF_SCENE_ID);
	m_pResultScene	= new Result::ResultScene(RESULT_SCENE_ID);

	m_pSceneManager->AddScene(m_pTitleScene);
	m_pSceneManager->AddScene(m_pGameScene);
	m_pSceneManager->AddScene(m_pStaffScene);
	m_pSceneManager->AddScene(m_pResultScene);
	m_pSceneManager->AddScene(m_pSelectScene);

	m_pSceneManager->SetEntryScene(m_pTitleScene);	// エントリシーンとして設定.

	return true;
}

void Application::ReleaseMainWindow()
{
	if (m_pMainWindow != nullptr)
	{
		m_pMainWindow->Finalize();
		SafeDelete(m_pMainWindow);
	}
}

void Application::ReleaseGraphicsDevice()
{
	if (SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice) != nullptr)
	{
		SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)->Finalize();
		SINGLETON_DELETE(Lib::Dx11::GraphicsDevice);
	}
}

void Application::ReleaseInputDevice()
{
	SINGLETON_INSTANCE(JoyconManager)->Disconnect(Joycon::LEFT_CONTROLLER);
	SINGLETON_INSTANCE(JoyconManager)->Disconnect(Joycon::RIGHT_CONTROLLER);
	SINGLETON_DELETE(JoyconManager);

	if (SINGLETON_INSTANCE(Lib::InputDeviceManager) != nullptr)
	{
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->ReleaseDevice(Lib::InputDeviceManager::GAMEPAD_TYPE);
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->ReleaseDevice(Lib::InputDeviceManager::MOUSEDEVICE_TYPE);
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->ReleaseDevice(Lib::InputDeviceManager::KEYDEVICE_TYPE);

		SINGLETON_INSTANCE(Lib::InputDeviceManager)->Finalize();
		SINGLETON_DELETE(Lib::InputDeviceManager);
	}
}

void Application::ReleaseSceneManager()
{
	if (m_pSceneManager != nullptr)
	{
		m_pSceneManager->DeleteScene(m_pResultScene);
		SafeDelete(m_pResultScene);

		m_pSceneManager->DeleteScene(m_pStaffScene);
		SafeDelete(m_pStaffScene);

		m_pSceneManager->DeleteScene(m_pGameScene);
		SafeDelete(m_pGameScene);

		m_pSceneManager->DeleteScene(m_pSelectScene);
		SafeDelete(m_pSelectScene);
	
		m_pSceneManager->DeleteScene(m_pTitleScene);
		SafeDelete(m_pTitleScene);
		
		m_pSceneManager->Finalize();
		SafeDelete(m_pSceneManager);
	}
}

