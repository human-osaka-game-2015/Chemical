/**
 * @file   GaugeUIBase.cpp
 * @brief  GaugeUIBaseクラスの実装
 * @author kotani
 */
#include "GaugeUIBase.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"


namespace Game
{
	GaugeUIBase::GaugeUIBase() :
		m_GaugeMaxValue(100.f),
		m_GaugeValue(100.f)
	{
	}

	GaugeUIBase::~GaugeUIBase()
	{
	}

	bool GaugeUIBase::Initialize()
	{
		return true;
	}

	void GaugeUIBase::Finalize()
	{
	}

	void GaugeUIBase::Update()
	{
	}

	void GaugeUIBase::Draw()
	{
		D3DXVECTOR2 Vertex[4];
		Vertex[0] = D3DXVECTOR2(-m_Size.x / 2, -m_Size.y / 2);
		Vertex[1] = D3DXVECTOR2(m_Size.x / 2, -m_Size.y / 2);
		Vertex[2] = D3DXVECTOR2(-m_Size.x / 2, m_Size.y / 2);
		Vertex[3] = D3DXVECTOR2(m_Size.x / 2, m_Size.y / 2);

		Vertex[1].x -= m_Size.x - ((m_GaugeValue / m_GaugeMaxValue) * m_Size.x);
		Vertex[3].x = Vertex[1].x;

		m_pVertex->ShaderSetup();
		m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_GaugeTextureIndex));
		m_pVertex->SetVertexPos(Vertex);
		m_pVertex->WriteVertexBuffer();
		m_pVertex->WriteConstantBuffer(&m_Pos);

		m_pVertex->Draw();

		Vertex[1] = D3DXVECTOR2(m_Size.x / 2, -m_Size.y / 2);
		Vertex[3] = D3DXVECTOR2(m_Size.x / 2, m_Size.y / 2);
		m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_FrameTextureIndex));
		m_pVertex->SetVertexPos(Vertex);
		m_pVertex->WriteVertexBuffer();
		m_pVertex->WriteConstantBuffer(&m_Pos);

		m_pVertex->Draw();
	}
}
