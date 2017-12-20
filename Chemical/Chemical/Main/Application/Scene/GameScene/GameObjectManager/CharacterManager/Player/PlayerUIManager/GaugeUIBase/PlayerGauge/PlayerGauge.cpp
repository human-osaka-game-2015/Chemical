/**
 * @file   PlayerGauge.cpp
 * @brief  PlayerGaugeクラスの実装
 * @author kotani
 */
#include "PlayerGauge.h"
#include "Application\Scene\GameScene\GameDefine.h"

#include "DirectX11\AnimationManager\Dx11AnimationManager.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "InputDeviceManager\InputDeviceManager.h"
#include "InputDeviceManager\KeyDevice\KeyDevice.h"
#include "TaskManager\TaskManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------

	PlayerGauge::PlayerGauge(const Player::PlayerState* _pPlayerState) :
		m_pPlayerState(_pPlayerState)
	{
		m_Size = D3DXVECTOR2(90.f, 20.f);

		m_Pos = m_pPlayerState->Pos;
		m_GaugeMaxValue = m_pPlayerState->Life;
		m_GaugeValue = m_pPlayerState->Life;
	}


	PlayerGauge::~PlayerGauge()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------

	bool PlayerGauge::Initialize()
	{
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->AddTask(m_pDrawTask);
		m_pDrawTask->SetPriority(GAME_DRAW_UI);

		if (!CreateVertex2D()) return false;

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\GameScene\\Texture\\Gauge.png",
			&m_GaugeTextureIndex)) return false;

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\GameScene\\Texture\\GaugeFrame.png",
			&m_FrameTextureIndex)) return false;

		m_pVertex->SetUV(&D3DXVECTOR2(0.f, 0.f), &D3DXVECTOR2(1.f, 1.f));
		m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));

		return true;
	}

	void PlayerGauge::Finalize()
	{
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_FrameTextureIndex);
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_GaugeTextureIndex);

		ReleaseVertex2D();

		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
	}

	void PlayerGauge::Update()
	{
		m_Pos = m_pPlayerState->Pos;
		m_Pos.y -= 130.f;
		m_GaugeValue = m_pPlayerState->Life;
		if (m_GaugeValue < 0)
		{
			m_GaugeValue = 0;
		}
	}

}
