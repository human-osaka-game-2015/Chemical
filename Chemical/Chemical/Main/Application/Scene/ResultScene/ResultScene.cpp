/**
 * @file	ResultScene.cpp
 * @brief	リザルトシーンクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ResultScene.h"

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
#include "ResultObjectManager\ResultMenu\ResultMenuEvent\ResultMenuEvent.h"
#include "DirectX11\Font\Dx11Font.h"
#include "JoyconManager\JoyconManager.h"
#include "Application\ResultFile\ResultFile.h"
#include "ResultDefine.h"
#include "Application\Application.h"


namespace Result
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	ResultScene::ResultScene(int _sceneId) :
		SceneBase(_sceneId)
	{
	}

	ResultScene::~ResultScene()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool ResultScene::Initialize()
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

		m_pObjectManager = new ResultObjectManager();
		if (!m_pObjectManager->Initialize())
		{
			return false;
		}

		m_pReceiveFunc = std::bind(&ResultScene::ReceiveEvent, this, std::placeholders::_1);
		m_pEventListener = new Lib::EventListener(&m_pReceiveFunc);
		SINGLETON_INSTANCE(Lib::EventManager)->AddEventListener(
			m_pEventListener,
			TO_STRING(RESULT_MENU_EVENT_GROUP));

		m_State = UPDATE_STATE;

		return true;
	}

	void ResultScene::Finalize()
	{
		SINGLETON_INSTANCE(Lib::EventManager)->RemoveEventListener(
			m_pEventListener,
			TO_STRING(RESULT_MENU_EVENT_GROUP));
		SafeDelete(m_pEventListener);
		m_pObjectManager->Finalize();
		SafeDelete(m_pObjectManager);

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

	void ResultScene::Update()
	{
		// デバイスの入力チェック.
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyUpdate();
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->MouseUpdate();
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyCheck(DIK_UPARROW);
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyCheck(DIK_LEFTARROW);
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyCheck(DIK_RIGHTARROW);
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyCheck(DIK_DOWNARROW);
		SINGLETON_INSTANCE(Lib::InputDeviceManager)->KeyCheck(DIK_RETURN);

		SINGLETON_INSTANCE(JoyconManager)->CheckButton(Joycon::RIGHT_CONTROLLER, Joycon::A_BUTTON);

		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->Run();

		SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)->BeginScene(Lib::Dx11::GraphicsDevice::BACKBUFFER_TARGET);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->Run();
		SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)->EndScene();
	}


	//----------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------
	void ResultScene::ReceiveEvent(Lib::EventBase* _pEvent)
	{
		ResultFile resultFile;
		switch (_pEvent->GetEventID())
		{
		case RESULT_MENU_EVENT_ID:
			switch (reinterpret_cast<ResultMenuEvent*>(_pEvent)->GetType())
			{
			case ResultMenuEvent::STAGESELECT_BACK_EVENT:
			{
				m_NextSceneID = Application::SELECT_SCENE_ID;
				m_State = FINAL_STATE;

				resultFile.Open();
				char FileName[256];
				sprintf_s(
					FileName,
					"Resource\\StageSelectScene\\RankingWindow\\RankingData\\Stage%d.csv",
					resultFile.GetStageNum());

				FILE* pFile;
				fopen_s(&pFile, FileName, "r");

				int CSVData;
				int RankingNum = 0;
				while ((CSVData = fgetc(pFile)) != EOF)
				{
					if (CSVData == '\n')
					{
						RankingNum++;
					}
				}

				fseek(pFile, 0, SEEK_SET);
				std::vector<int> Scores;
				Scores.resize(RankingNum);
				std::vector<int> Times;
				Times.resize(RankingNum);
				for (int i = 0; i < RankingNum; i++)
				{
					fscanf_s(pFile, "%d,", &Scores[i]);
					fscanf_s(pFile, "%d", &Times[i]);
				}

				for (int i = 0; i < RankingNum; i++)
				{
					// ランキングファイルはソートされているので.
					// 比較で現在のランキングを取得.
					if (Scores[i] < resultFile.GetScore())
					{
						int Rank = i;
						Scores.insert(Scores.begin() + i, resultFile.GetScore());
						Times.insert(Times.begin() + i, resultFile.GetSeconds() + resultFile.GetMinute() * 60);
						break;
					}
				}
				fclose(pFile);

				fopen_s(&pFile, FileName, "w");
				for (int i = 0; i < RankingNum; i++)
				{
					fprintf(pFile, "%d,%d\n", Scores[i], Times[i]);
				}
				fclose(pFile);

				resultFile.Close();
			}
			break;
			case ResultMenuEvent::RESTART_EVENT:
				m_NextSceneID = Application::GAME_SCENE_ID;
				m_State = FINAL_STATE;

				resultFile.Open();
				char FileName[256];
				sprintf_s(
					FileName,
					"Resource\\StageSelectScene\\RankingWindow\\RankingData\\Stage%d.csv",
					resultFile.GetStageNum());

				FILE* pFile;
				fopen_s(&pFile, FileName, "r");

				int CSVData;
				int RankingNum = 0;
				while ((CSVData = fgetc(pFile)) != EOF)
				{
					if (CSVData == '\n')
					{
						RankingNum++;
					}
				}

				fseek(pFile, 0, SEEK_SET);
				std::vector<int> Scores;
				Scores.resize(RankingNum);
				std::vector<int> Times;
				Times.resize(RankingNum);
				for (int i = 0; i < RankingNum; i++)
				{
					fscanf_s(pFile, "%d,", &Scores[i]);
					fscanf_s(pFile, "%d", &Times[i]);
				}

				for (int i = 0; i < RankingNum; i++)
				{
					// ランキングファイルはソートされているので.
					// 比較で現在のランキングを取得.
					if (Scores[i] < resultFile.GetScore())
					{
						int Rank = i;
						Scores.insert(Scores.begin() + i, resultFile.GetScore());
						Times.insert(Times.begin() + i, resultFile.GetSeconds() + resultFile.GetMinute() * 60);
						break;
					}
				}
				fclose(pFile);

				fopen_s(&pFile, FileName, "w");
				for (int i = 0; i < RankingNum; i++)
				{
					fprintf(pFile, "%d,%d\n", Scores[i], Times[i]);
				}
				fclose(pFile);

				resultFile.Close();
				break;
			}
			break;
		}
	}
}
