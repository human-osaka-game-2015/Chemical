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
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------

	ChemicalGauge::ChemicalGauge(const D3DXVECTOR2* _pPos,
		const ChemicalBase::ChemicalData* _pChemicalData, 
		std::array<int, CHEMICAL_EMPTY> _pTextureIndexs) :
		m_pChemicaData(_pChemicalData)
	{
		m_GaugeMaxValue = 100;
		m_Size = D3DXVECTOR2(60.f, 180.f);
		m_Pos = *_pPos;

		for (int i = 0; i < CHEMICAL_EMPTY; i++)
		{
			m_TextureIndexs[i] = _pTextureIndexs[i];
		}
	}

	ChemicalGauge::~ChemicalGauge()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------

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
		m_GaugeValue = m_pChemicaData->Remain;
	}

	void ChemicalGauge::Draw()
	{
		D3DXVECTOR2 Vertex[4];
		Vertex[0] = D3DXVECTOR2(-m_Size.x / 2, -m_Size.y / 2);
		Vertex[1] = D3DXVECTOR2(m_Size.x / 2, -m_Size.y / 2);
		Vertex[2] = D3DXVECTOR2(-m_Size.x / 2, m_Size.y / 2);
		Vertex[3] = D3DXVECTOR2(m_Size.x / 2, m_Size.y / 2);

		Vertex[0].y += m_Size.y - ((m_GaugeValue / m_GaugeMaxValue) * m_Size.y);
		Vertex[1].y = Vertex[0].y;

		m_pVertex->ShaderSetup();
		m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndexs[m_pChemicaData->Type]));
		m_pVertex->SetVertexPos(Vertex);
		m_pVertex->WriteVertexBuffer();
		m_pVertex->WriteConstantBuffer(&m_Pos);

		m_pVertex->Draw();

		Vertex[0] = D3DXVECTOR2(-m_Size.x / 2, -m_Size.y / 2);
		Vertex[1] = D3DXVECTOR2(m_Size.x / 2, -m_Size.y / 2);
		m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_FrameTextureIndex));
		m_pVertex->SetVertexPos(Vertex);
		m_pVertex->WriteVertexBuffer();
		m_pVertex->WriteConstantBuffer(&m_Pos);

		m_pVertex->Draw();
	}
}
