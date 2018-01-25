/**
* @file		GameClip.cpp
* @brief	ゲームクリッピングクラス実装
* @author	morimoto
*/

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "GameClip.h"

#include "Debugger\Debugger.h"
#include "DirectX11\GraphicsDevice\Dx11GraphicsDevice.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "DirectX11\ShaderManager\Dx11ShaderManager.h"
#include "InputDeviceManager\InputDeviceManager.h"
#include "EventManager\EventBase\EventBase.h"
#include "EventManager\EventManager.h"
#include "GameDefine.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	GameClip::GameClip()
	{
		m_Pos = D3DXVECTOR2(960, 540);
		m_Size = D3DXVECTOR2(1920, 1080);
	}

	GameClip::~GameClip()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool GameClip::Initialize()
	{
		m_pDrawTask->SetPriority(GAME_DRAW_CLIP);

		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->AddTask(m_pDrawTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);

		if (!CreateVertex2D())
		{
			return false;
		}

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\TitleScene\\Cliping.png",
			&m_TextureIndex))
		{
			return false;
		}

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\TitleScene\\Cliping2.png",
			&m_TextureIndex2))
		{
			return false;
		}

		if (!SINGLETON_INSTANCE(Lib::Dx11::ShaderManager)->LoadVertexShader(
			"Resource\\TitleScene\\ClipEffect.fx",
			"VS",
			&m_VertexShaderIndex))
		{
			return false;
		}

		if (!SINGLETON_INSTANCE(Lib::Dx11::ShaderManager)->LoadPixelShader(
			"Resource\\TitleScene\\ClipEffect.fx",
			"PS",
			&m_PixelShaderIndex))
		{
			return false;
		}

		if (!SINGLETON_INSTANCE(Lib::Dx11::ShaderManager)->LoadVertexShader(
			"Resource\\TitleScene\\TextureCreateEffect.fx",
			"VS",
			&m_CreateTextureVertexShaderIndex))
		{
			return false;
		}

		if (!SINGLETON_INSTANCE(Lib::Dx11::ShaderManager)->LoadPixelShader(
			"Resource\\TitleScene\\TextureCreateEffect.fx",
			"PS",
			&m_CreateTexturePixelShaderIndex))
		{
			return false;
		}

		D3D11_TEXTURE2D_DESC ClipTextureDesc;
		ZeroMemory(&ClipTextureDesc, sizeof(ClipTextureDesc));
		ClipTextureDesc.Width = static_cast<UINT>(1280);
		ClipTextureDesc.Height = static_cast<UINT>(1280);
		ClipTextureDesc.MipLevels = 1;
		ClipTextureDesc.ArraySize = 1;
		ClipTextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		ClipTextureDesc.SampleDesc.Count = 1;
		ClipTextureDesc.SampleDesc.Quality = 0;
		ClipTextureDesc.Usage = D3D11_USAGE_DEFAULT;
		ClipTextureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		ClipTextureDesc.CPUAccessFlags = 0;
		ClipTextureDesc.MiscFlags = 0;

		if (FAILED(SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)->GetDevice()->CreateTexture2D(
			&ClipTextureDesc,
			nullptr,
			&m_pClipTexture)))
		{
			OutputErrorLog("マップ生成に失敗しました");
			return false;
		}

		if (FAILED(SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)->GetDevice()->CreateRenderTargetView(
			m_pClipTexture,
			nullptr,
			&m_pClipRenderTarget)))
		{
			OutputErrorLog("マップのレンダーターゲットビューの設定に失敗しました");
			return false;
		}

		if (FAILED(SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)->GetDevice()->CreateShaderResourceView(
			m_pClipTexture,
			nullptr,
			&m_pClipShaderResourceView)))
		{
			OutputErrorLog("マップのシェーダーリソースビューの生成に失敗しました");
			return false;
		}


		D3D11_TEXTURE2D_DESC DepthStencilDesc;
		DepthStencilDesc.Width = static_cast<UINT>(1280);
		DepthStencilDesc.Height = static_cast<UINT>(1280);
		DepthStencilDesc.MipLevels = 1;
		DepthStencilDesc.ArraySize = 1;
		DepthStencilDesc.Format = DXGI_FORMAT_D32_FLOAT;
		DepthStencilDesc.SampleDesc.Count = 1;
		DepthStencilDesc.SampleDesc.Quality = 0;
		DepthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		DepthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		DepthStencilDesc.CPUAccessFlags = 0;
		DepthStencilDesc.MiscFlags = 0;

		if (FAILED(SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)->GetDevice()->CreateTexture2D(
			&DepthStencilDesc,
			nullptr,
			&m_pClipDepthStencilTexture)))
		{
			OutputErrorLog("深度ステンシルテクスチャ生成に失敗しました");
			return false;
		}

		if (FAILED(SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)->GetDevice()->CreateDepthStencilView(
			m_pClipDepthStencilTexture,
			nullptr,
			&m_pClipDepthStencilView)))
		{
			OutputErrorLog("深度ステンシルテクスチャのデプスステンシルビューの生成に失敗しました");
			return false;
		}

		m_ViewPort.TopLeftX = 0;
		m_ViewPort.TopLeftY = 0;
		m_ViewPort.Width = 1280;
		m_ViewPort.Height = 1280;
		m_ViewPort.MinDepth = 0.0f;
		m_ViewPort.MaxDepth = 1.0f;


		D3D11_SAMPLER_DESC SamplerDesc;
		ZeroMemory(&SamplerDesc, sizeof(D3D11_SAMPLER_DESC));
		SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		if (FAILED(SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)->GetDevice()->CreateSamplerState(
			&SamplerDesc,
			&m_pSamplerState)))
		{
			OutputErrorLog("サンプラステートの生成に失敗しました");
			return false;
		}

		m_ClipSize = D3DXVECTOR2(0, 0);
		m_IsClip = true;
		m_IsFadeIn = true;

		m_pEvent = new GameClipEvent(NEXT_SCENE_EVENT);

		m_ReceiveFunc = std::bind(&GameClip::ReceiveEvent, this, std::placeholders::_1);
		m_pEventListener = new Lib::EventListener(&m_ReceiveFunc);

		SINGLETON_INSTANCE(Lib::EventManager)->AddEventListener(
			m_pEventListener, 
			TO_STRING(CURRENT_SCENE_EVENT_GROUP));

		return true;
	}

	void GameClip::Finalize()
	{
		SINGLETON_INSTANCE(Lib::EventManager)->RemoveEventListener(
			m_pEventListener,
			TO_STRING(CURRENT_SCENE_EVENT_GROUP));

		SafeDelete(m_pEventListener);

		SafeDelete(m_pEvent);

		m_pSamplerState->Release();

		m_pClipDepthStencilView->Release();
		m_pClipDepthStencilTexture->Release();

		m_pClipShaderResourceView->Release();
		m_pClipRenderTarget->Release();
		m_pClipTexture->Release();

		SINGLETON_INSTANCE(Lib::Dx11::ShaderManager)->ReleasePixelShader(m_CreateTexturePixelShaderIndex);
		SINGLETON_INSTANCE(Lib::Dx11::ShaderManager)->ReleaseVertexShader(m_CreateTextureVertexShaderIndex);
		SINGLETON_INSTANCE(Lib::Dx11::ShaderManager)->ReleasePixelShader(m_PixelShaderIndex);
		SINGLETON_INSTANCE(Lib::Dx11::ShaderManager)->ReleaseVertexShader(m_VertexShaderIndex);

		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex2);
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);
		ReleaseVertex2D();

		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
	}

	void GameClip::Update()
	{
		if (m_IsClip)
		{
			if (m_IsFadeIn)
			{
				m_ClipSize = D3DXVECTOR2(m_ClipSize.x + 30, m_ClipSize.y + 30);
				if (m_ClipSize.x > 2500)
				{
					m_ClipSize = D3DXVECTOR2(2500, 2500);
				}
			}
			else
			{
				m_ClipSize = D3DXVECTOR2(m_ClipSize.x - 20, m_ClipSize.y - 20);
				if (m_ClipSize.x < 0)
				{
					SINGLETON_INSTANCE(Lib::EventManager)->SendEventMessage(
						m_pEvent,
						TO_STRING(CURRENT_SCENE_EVENT_GROUP));
					m_ClipSize = D3DXVECTOR2(0, 0);
				}
			}
		}
	}

	void GameClip::Draw()
	{
		Lib::Dx11::GraphicsDevice* pGraphicsDevice = SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice);
		ID3D11DeviceContext* pContext = SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)->GetDeviceContext();
		Lib::Dx11::ShaderManager*	pShaderManager = SINGLETON_INSTANCE(Lib::Dx11::ShaderManager);

		pGraphicsDevice->SetRenderTarget(&m_pClipRenderTarget, 2);
		pGraphicsDevice->SetDepthStencil(&m_pClipDepthStencilView, 2);
		pGraphicsDevice->SetClearColor(D3DXCOLOR(0, 0, 0, 0), 2);
		pGraphicsDevice->SetViewPort(&m_ViewPort, 2);
		pGraphicsDevice->BeginScene(2);


		// ベースの描画.
		m_pVertex->SetVertex(&m_Size);
		m_pVertex->WriteVertexBuffer();
		m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex2));

		pContext->VSSetShader(
			SINGLETON_INSTANCE(Lib::Dx11::ShaderManager)->GetVertexShader(m_CreateTextureVertexShaderIndex),
			nullptr,
			0);
		pContext->PSSetShader(
			SINGLETON_INSTANCE(Lib::Dx11::ShaderManager)->GetPixelShader(m_CreateTexturePixelShaderIndex),
			nullptr,
			0);
		pContext->GSSetShader(nullptr, nullptr, 0);
		pContext->HSSetShader(nullptr, nullptr, 0);
		pContext->DSSetShader(nullptr, nullptr, 0);
		pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		m_pVertex->WriteConstantBuffer(&m_Pos);
		m_pVertex->Draw();

		// クリッピング範囲の描画
		m_pVertex->SetVertex(&m_ClipSize);
		m_pVertex->WriteVertexBuffer();
		m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));

		pContext->VSSetShader(
			SINGLETON_INSTANCE(Lib::Dx11::ShaderManager)->GetVertexShader(m_CreateTextureVertexShaderIndex),
			nullptr,
			0);
		pContext->PSSetShader(
			SINGLETON_INSTANCE(Lib::Dx11::ShaderManager)->GetPixelShader(m_CreateTexturePixelShaderIndex),
			nullptr,
			0);
		pContext->GSSetShader(nullptr, nullptr, 0);
		pContext->HSSetShader(nullptr, nullptr, 0);
		pContext->DSSetShader(nullptr, nullptr, 0);
		pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		m_pVertex->WriteConstantBuffer(&m_Pos);
		m_pVertex->Draw();

		// クリッピング.
		pGraphicsDevice->SetScene(Lib::Dx11::GraphicsDevice::BACKBUFFER_TARGET);

		m_pVertex->SetVertex(&m_Size);
		m_pVertex->WriteVertexBuffer();
		m_pVertex->SetTexture(nullptr);
		pContext->PSSetSamplers(0, 1, &m_pSamplerState);
		pContext->PSSetShaderResources(0, 1, &m_pClipShaderResourceView);

		pContext->VSSetShader(
			SINGLETON_INSTANCE(Lib::Dx11::ShaderManager)->GetVertexShader(m_VertexShaderIndex),
			nullptr,
			0);
		pContext->PSSetShader(
			SINGLETON_INSTANCE(Lib::Dx11::ShaderManager)->GetPixelShader(m_PixelShaderIndex),
			nullptr,
			0);
		pContext->GSSetShader(nullptr, nullptr, 0);
		pContext->HSSetShader(nullptr, nullptr, 0);
		pContext->DSSetShader(nullptr, nullptr, 0);
		pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		m_pVertex->WriteConstantBuffer(&m_Pos);
		m_pVertex->Draw();
	}

	void GameClip::ReceiveEvent(Lib::EventBase* _pEvent)
	{
		switch (_pEvent->GetEventID())
		{
		case CURRENT_SCENE_EVENT:
			m_IsClip = true;
			m_IsFadeIn = false;
			break;
		}
	}
}


