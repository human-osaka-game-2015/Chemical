/**
 * @file   SelectStartButton.cpp
 * @brief  StartButtonクラスの実装
 * @author kotani
 */
#include "SelectStartButton.h"
#include "Application\Scene\SelectScene\SelectGameStartEvent\SelectGameStartEvent.h"
#include "Application\GamePlayFile\GamePlayFile.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "DirectX11\GraphicsDevice\Dx11GraphicsDevice.h"
#include "EventManager\EventManager.h"
#include "TaskManager\TaskManager.h"


namespace Select
{
	StartButton::StartButton(int _stageNum) :
		m_StageNum(_stageNum)
	{
		m_Pos.x = 450.f - m_Size.x / 2;
	}


	StartButton::~StartButton()
	{
	}


	//----------------------------------------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------------------------------------

	bool StartButton::Initialize()
	{
		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\StageSelectScene\\Texture\\StartButton.png",
			&m_TextureIndex)) return false;

		if (!CreateVertex2D()) return false;
		m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));

		return true;
	}

	void StartButton::Finalize()
	{
		ReleaseVertex2D();
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);
	}

	void StartButton::OnClick()
	{
		GamePlayFile file;
		file.Open();
		file.SetStageNum(m_StageNum);
		file.Write();
		file.Close();

		GameStartEvent Event(GameStartEvent::START_BUTTON_PUSH);
		Event.SetEventType(GameStartEvent::START_BUTTON_PUSH);
		SINGLETON_INSTANCE(Lib::EventManager)->SendEventMessage(&Event,"");
	}

}
