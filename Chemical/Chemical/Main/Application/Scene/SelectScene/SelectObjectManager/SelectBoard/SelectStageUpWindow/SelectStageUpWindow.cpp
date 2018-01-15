/**
 * @file   SelectStageUpWindow.cpp
 * @brief  StageUpWindowクラスの実装
 * @author kotani
 */
#include "SelectStageUpWindow.h"
#include "Application\Scene\SelectScene\SelectDefine.h"
#include "..\..\..\SelectManager\SelectManager.h"
#include "SelectButtonBase\SelectStartButton\SelectStartButton.h"
#include "SelectButtonBase\SelectRankingButton\SelectRankingButton.h"
#include "SelectButtonBase\SelectReturnButton\SelectReturnButton.h"
#include "ScoreRanking\ScoreRanking.h"
#include "RankingWindow\RankingWindow.h"
#include "RankingButton\RankingButton.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "DirectX11\GraphicsDevice\Dx11GraphicsDevice.h"
#include "TaskManager\TaskManager.h"
#include "InputDeviceManager\InputDeviceManager.h"

namespace Select
{
	StageUpWindow::StageUpWindow(int _stageNum) :
		m_IsEnable(false),
		m_StageNum(_stageNum),
		m_Alpha(0),
		m_IsRankingDraw(false),
		m_ButtonState(NONE_BUTTON)
	{
		m_Size = D3DXVECTOR2(960, 480);
		m_Pos = D3DXVECTOR2(960, 540);
		m_pDrawTask->SetPriority(SELECT_DRAW_STAGEUP_WINDOW);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->AddTask(m_pDrawTask);
	}

	StageUpWindow::~StageUpWindow()
	{
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
	}


	//----------------------------------------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------------------------------------

	bool StageUpWindow::Initialize()
	{
		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\StageSelectScene\\Texture\\StageUp.png",
			&m_TextureIndex)) return false;
		
		if (!CreateVertex2D()) return false;
		m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));

		m_pButtons[START_BUTTON] = new StartButton(m_StageNum);
		if (!m_pButtons[START_BUTTON]->Initialize()) return false;

		m_pButtons[RANKING_BUTTON] = new RankingButton();
		if (!m_pButtons[RANKING_BUTTON]->Initialize()) return false;

		m_pButtons[RETURN_BUTTON] = new ReturnButton();
		if (!m_pButtons[RETURN_BUTTON]->Initialize()) return false;

		m_pScoreRanking = new ScoreRanking(m_StageNum);
		if (!m_pScoreRanking->Initialize()) return false;

		m_pRankingButton = new RankingReturnButton();
		if (!m_pRankingButton->Initialize()) return false;

		m_pRankingWindow = new RankingWindow();
		if (!m_pRankingWindow->Initialize()) return false;

		return true;
	}

	void StageUpWindow::Finalize()
	{
		m_pRankingWindow->Finalize();
		SafeDelete(m_pRankingWindow);

		m_pRankingButton->Finalize();
		SafeDelete(m_pRankingButton);

		m_pScoreRanking->Finalize();
		SafeDelete(m_pScoreRanking);

		for (auto itr : m_pButtons)
		{
			itr->Finalize();
			SafeDelete(itr);
		}
		ReleaseVertex2D();
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);
	}

	void StageUpWindow::Update()
	{
		if (!m_IsEnable) return;
		const Lib::KeyDevice::KEYSTATE* KeyState = SINGLETON_INSTANCE(Lib::InputDeviceManager)->GetKeyState();

		m_Alpha += 0.009f;
		if (m_Alpha > 1) m_Alpha = 1;
		else if (m_Alpha != 1) return;

		if (m_ButtonState != NONE_BUTTON) m_pButtons[m_ButtonState]->OnCusor();
		

		for (auto itr : m_pButtons)
		{
			itr->Update();
		}

		if (m_IsRankingDraw)
		{
			if (KeyState[DIK_RETURN] == Lib::KeyDevice::KEY_PUSH)
			{
				m_IsRankingDraw = false;
			}
			m_pRankingWindow->Update();
			m_pScoreRanking->Update();
			m_pRankingButton->Update();
		}
		else
		{
			if (KeyState[DIK_LEFT] == Lib::KeyDevice::KEY_PUSH)
			{
				if (m_ButtonState > 0) m_ButtonState--;
				else m_ButtonState = RETURN_BUTTON;
			}

			if (KeyState[DIK_RIGHT] == Lib::KeyDevice::KEY_PUSH)
			{
				if (m_ButtonState < RETURN_BUTTON) m_ButtonState++;
				else m_ButtonState = START_BUTTON;
			}

			if (KeyState[DIK_RETURN] == Lib::KeyDevice::KEY_PUSH &&
				!m_IsRankingDraw)
			{
				switch (m_ButtonState)
				{
				case START_BUTTON:
					m_pButtons[START_BUTTON]->OnClick();
					m_Alpha = 0.f;
					m_ButtonState = NONE_BUTTON;
					break;
				case RANKING_BUTTON:
					m_pButtons[RANKING_BUTTON]->OnClick();
					m_IsRankingDraw = true;
					m_Alpha = 0.f;
					SINGLETON_INSTANCE(SelectManager)->SetSelectState(SelectManager::RANKING_SELECT);
					m_ButtonState = NONE_BUTTON;
					break;
				case RETURN_BUTTON:
					m_pButtons[RETURN_BUTTON]->OnClick();
					m_Alpha = 0.f;
					SINGLETON_INSTANCE(SelectManager)->SetSelectState(SelectManager::STAGE_BOARD_SELECT);
					m_IsEnable = false;
					m_ButtonState = NONE_BUTTON;
					break;
				default:
					break;
				}
			}
		}
	}

	void StageUpWindow::Draw()
	{
		if (!m_IsEnable) return;

		m_pVertex->SetColor(&D3DXCOLOR(1, 1, 1, m_Alpha));
		m_pVertex->ShaderSetup();
		m_pVertex->WriteVertexBuffer();
		m_pVertex->WriteConstantBuffer(&m_Pos);
		m_pVertex->Draw();

		for (auto itr : m_pButtons)
		{
			itr->Draw(m_Alpha);
		}

		if (m_IsRankingDraw)
		{
			m_pRankingWindow->Draw();
			m_pScoreRanking->Draw();
			m_pRankingButton->Draw();
		}
	}
}
