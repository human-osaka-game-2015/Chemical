/**
 * @file   ChemicalGauge.cpp
 * @brief  ChemicalGaugeクラスの実装
 * @author kotani
 */
#include "ChemicalGauge.h"
#include "Application\Scene\GameScene\GameDefine.h"

#include "DirectX11\AnimationManager\Dx11AnimationManager.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "InputDeviceManager\InputDeviceManager.h"
#include "InputDeviceManager\KeyDevice\KeyDevice.h"
#include "TaskManager\TaskManager.h"

namespace Game
{
	ChemicalGauge::ChemicalGauge(const D3DXVECTOR2* _pos, const float* _chemicalRemain) :
		m_pChemicaRemain(_chemicalRemain)
	{
		m_GaugeMaxValue = 100;
		m_Size = D3DXVECTOR2(60.f, 180.f);
		m_Pos = *_pos;
	}

	ChemicalGauge::~ChemicalGauge()
	{
	}

	bool ChemicalGauge::Initialize()
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

	void ChemicalGauge::Finalize()
	{
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_FrameTextureIndex);
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_GaugeTextureIndex);

		ReleaseVertex2D();

		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
	}

	void ChemicalGauge::Update()
	{
		m_GaugeValue = *m_pChemicaRemain;
	}

}
