/**
 * @file	Dx11GraphicsDevice.cpp
 * @brief	グラフィックデバイスの管理クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Dx11GraphicsDevice.h"

#include "Debugger\Debugger.h"


namespace Lib
{
	namespace Dx11
	{
		//----------------------------------------------------------------------
		// Static Public Variables
		//----------------------------------------------------------------------
		const int GraphicsDevice::m_ScreenShotCountMax = 30;


		//----------------------------------------------------------------------
		// Constructor	Destructor
		//----------------------------------------------------------------------
		GraphicsDevice::GraphicsDevice() :
			m_pDevice(nullptr),
			m_pDeviceContext(nullptr),
			m_pDXGI(nullptr),
			m_pAdapter(nullptr),
			m_pDXGIFactory(nullptr),
			m_pDXGISwapChain(nullptr),
			m_pBackBuffer(nullptr),
			m_pDepthStencilBuffer(nullptr),
			m_pRasterizerState(nullptr),
			m_hWnd(nullptr)
		{
			for (int i = 0; i < m_RenderTargetNum; i++)
			{
				m_pRenderTargetView[i] = nullptr;
				m_pDepthStencilView[i] = nullptr;

				for (int j = 0; j < 4; j++)
				{
					m_ClearColor[i][j] = 0.0f;
				}
			}
		}

		GraphicsDevice::~GraphicsDevice()
		{
			Finalize();
		}


		//----------------------------------------------------------------------
		// Public Functions
		//----------------------------------------------------------------------
		bool GraphicsDevice::Initialize(HWND _hWnd)
		{
			MyAssert(m_pDevice != nullptr, "GraphicsDeviceオブジェクトは既に初期化されています");


			m_hWnd = _hWnd;
			GetWindowRect(m_hWnd, &m_WindowRect);

			if (!CreateDevice())
			{
				return false;
			}

			if (!CreateDisplay())
			{
				ReleaseDevice();
				return false;
			}

			return true;
		}

		void GraphicsDevice::Finalize()
		{
			ReleaseDisplay();
			ReleaseDevice();
		}

		void GraphicsDevice::BeginScene(int _stage)
		{
			m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView[_stage], m_ClearColor[_stage]);
			m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView[_stage], D3D11_CLEAR_DEPTH, 1.0f, 0);
			m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView[_stage], m_pDepthStencilView[_stage]);
			m_pDeviceContext->RSSetViewports(1, &m_ViewPort[_stage]);
		}

		void GraphicsDevice::SetScene(int _stage)
		{
			m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView[_stage], m_pDepthStencilView[_stage]);
			m_pDeviceContext->RSSetViewports(1, &m_ViewPort[_stage]);
		}

		void GraphicsDevice::EndScene()
		{
			m_pDXGISwapChain->Present(1, 0);
		}

		bool GraphicsDevice::SetRenderTarget(ID3D11RenderTargetView** _pRenderTarget, int _stage)
		{
			if (_stage > m_RenderTargetNum)
			{
				return false;
			}

			if (_pRenderTarget == nullptr)
			{
				m_pRenderTargetView[_stage] = nullptr;
			}
			else
			{
				m_pRenderTargetView[_stage] = *_pRenderTarget;
			}

			return true;
		}

		bool GraphicsDevice::SetDepthStencil(ID3D11DepthStencilView** _pDepthStencilView, int _stage)
		{
			if (_stage > m_RenderTargetNum)
			{
				return false;
			}

			if (_pDepthStencilView == nullptr)
			{
				m_pDepthStencilView[_stage] = nullptr;
			}
			else
			{
				m_pDepthStencilView[_stage] = *_pDepthStencilView;
			}

			return true;
		}

		bool GraphicsDevice::SetViewPort(const D3D11_VIEWPORT* _pViewPort, int _stage)
		{
			if (_stage > m_RenderTargetNum)
			{
				return false;
			}

			if (_pViewPort == nullptr)
			{
				m_ViewPort[_stage] = m_ViewPort[BACKBUFFER_TARGET];
			}
			else
			{
				m_ViewPort[_stage] = *_pViewPort;
			}

			return true;
		}

		bool GraphicsDevice::SetClearColor(D3DXCOLOR _clearColor, int _stage)
		{
			if (_stage > m_RenderTargetNum)
			{
				return false;
			}

			m_ClearColor[_stage][0] = _clearColor.r;
			m_ClearColor[_stage][1] = _clearColor.g;
			m_ClearColor[_stage][2] = _clearColor.b;
			m_ClearColor[_stage][3] = _clearColor.a;

			return true;
		}

		bool GraphicsDevice::CreateScreenShot(LPCTSTR _filePath)
		{
			if (m_ScreenShotCount >= m_ScreenShotCountMax)
			{
				OutputErrorLog("スクリーンショットの作成数が規定数に達しています");
				return false;
			}

			if (FAILED(D3DX11SaveTextureToFile(m_pDeviceContext, m_pBackBuffer, D3DX11_IFF_PNG, _filePath)))
			{
				OutputErrorLog("スクリーンショットの作成に失敗しました");
				return false;
			}

			m_ScreenShotCount++;

			return true;
		}


		//----------------------------------------------------------------------
		// Private Functions
		//----------------------------------------------------------------------
		bool GraphicsDevice::CreateDevice()
		{
#ifdef _DEBUG
			if (FAILED(D3D11CreateDevice(
				nullptr,
				D3D_DRIVER_TYPE_HARDWARE,
				nullptr,
				D3D11_CREATE_DEVICE_DEBUG,
				nullptr,
				0,
				D3D11_SDK_VERSION,
				&m_pDevice,
				nullptr,
				&m_pDeviceContext)))
			{
				OutputErrorLog("DirectX11デバイスの生成に失敗しました");
				return false;
			}
#else
			if (FAILED(D3D11CreateDevice(
				nullptr,
				D3D_DRIVER_TYPE_HARDWARE,
				nullptr,
				0,
				nullptr,
				0,
				D3D11_SDK_VERSION,
				&m_pDevice,
				nullptr,
				&m_pDeviceContext)))
			{
				OutputErrorLog("DirectX11デバイスの生成に失敗しました");
				return false;
			}
#endif // _DEBUG


			return true;
		}

		bool GraphicsDevice::CreateDisplay()
		{
			// グラフィックインフラストラクチャの取得.
			if (FAILED(m_pDevice->QueryInterface(__uuidof(IDXGIDevice1), reinterpret_cast<void**>(&m_pDXGI))))
			{
				OutputErrorLog("グラフィックインフラストラクチャの取得に失敗しました");
				return false;
			}

			// グラフィックインフラストラクチャアダプタの取得.
			if (FAILED(m_pDXGI->GetAdapter(&m_pAdapter)))
			{
				OutputErrorLog("グラフィックインフラストラクチャアダプタの取得に失敗しました");
				ReleaseDisplay();
				return false;
			}

			// グラフィックインフラストラクチャファクトリの取得.
			if (FAILED(m_pAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&m_pDXGIFactory))))
			{
				OutputErrorLog("グラフィックインフラストラクチャファクトリの取得に失敗しました");
				ReleaseDisplay();
				return false;
			}

			// DXGIにウィンドウメッセージキューの監視を設定.
			if (FAILED(m_pDXGIFactory->MakeWindowAssociation(m_hWnd, 0)))
			{
				OutputErrorLog("ウィンドウメッセージキュー監視設定に失敗しました");
				ReleaseDisplay();
				return false;
			}


			// スワップチェインの設定.
			DXGI_SWAP_CHAIN_DESC SwapChainDesc;
			SwapChainDesc.BufferDesc.Width = m_WindowRect.right - m_WindowRect.left;
			SwapChainDesc.BufferDesc.Height = m_WindowRect.bottom - m_WindowRect.top;
			SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
			SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
			SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
			SwapChainDesc.SampleDesc.Count = 1;
			SwapChainDesc.SampleDesc.Quality = 0;
			SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			SwapChainDesc.BufferCount = 1;
			SwapChainDesc.OutputWindow = m_hWnd;
			SwapChainDesc.Windowed = TRUE;
			SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

			// スワップチェインの生成.
			if (FAILED(m_pDXGIFactory->CreateSwapChain(m_pDevice, &SwapChainDesc, &m_pDXGISwapChain)))
			{
				OutputErrorLog("スワップチェインの作成に失敗しました");
				ReleaseDisplay();
				return false;
			}

			// バックバッファの取得.
			if (FAILED(m_pDXGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&m_pBackBuffer))))
			{
				OutputErrorLog("バックバッファの取得に失敗しました");
				ReleaseDisplay();
				return false;
			}

			m_pDXGISwapChain->SetFullscreenState(false, nullptr); // フルスクリーンモードを切る.


			// レンダーターゲットビューの作成に失敗しました.
			if (FAILED(m_pDevice->CreateRenderTargetView(m_pBackBuffer, nullptr, &m_pRenderTargetView[BACKBUFFER_TARGET])))
			{
				OutputErrorLog("レンダーターゲットビューの作成に失敗しました");
				ReleaseDisplay();
				return false;
			}

			// 深度ステンシルバッファの設定.
			D3D11_TEXTURE2D_DESC DepthDesc;
			DepthDesc.Width = m_WindowRect.right - m_WindowRect.left;
			DepthDesc.Height = m_WindowRect.bottom - m_WindowRect.top;
			DepthDesc.MipLevels = 1;
			DepthDesc.ArraySize = 1;
			DepthDesc.Format = DXGI_FORMAT_D32_FLOAT;
			DepthDesc.SampleDesc.Count = 1;
			DepthDesc.SampleDesc.Quality = 0;
			DepthDesc.Usage = D3D11_USAGE_DEFAULT;
			DepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			DepthDesc.CPUAccessFlags = 0;
			DepthDesc.MiscFlags = 0;

			// 深度ステンシルバッファの生成.
			if (FAILED(m_pDevice->CreateTexture2D(&DepthDesc, nullptr, &m_pDepthStencilBuffer)))
			{
				OutputErrorLog("深度ステンシルバッファの作成に失敗しました");
				ReleaseDisplay();
				return false;
			}

			// 深度ステンシルビューの作成.
			if (FAILED(m_pDevice->CreateDepthStencilView(
				m_pDepthStencilBuffer,
				nullptr,
				&m_pDepthStencilView[BACKBUFFER_TARGET])))
			{
				OutputErrorLog("深度ステンシルビューの作成に失敗しました");
				ReleaseDisplay();
				return false;
			}

			m_pDeviceContext->OMSetRenderTargets(
				1,
				&m_pRenderTargetView[BACKBUFFER_TARGET],
				m_pDepthStencilView[BACKBUFFER_TARGET]); // 描画先に設定.


			// ビューポートの設定.
			ZeroMemory(&m_ViewPort, sizeof(m_ViewPort));
			m_ViewPort[BACKBUFFER_TARGET].TopLeftX = 0;
			m_ViewPort[BACKBUFFER_TARGET].TopLeftY = 0;
			m_ViewPort[BACKBUFFER_TARGET].Width = static_cast<float>(m_WindowRect.right - m_WindowRect.left);
			m_ViewPort[BACKBUFFER_TARGET].Height = static_cast<float>(m_WindowRect.bottom - m_WindowRect.top);
			m_ViewPort[BACKBUFFER_TARGET].MinDepth = 0.0f;
			m_ViewPort[BACKBUFFER_TARGET].MaxDepth = 1.0f;
			m_pDeviceContext->RSSetViewports(1, &m_ViewPort[BACKBUFFER_TARGET]);


			// ラスタライザステートの設定.
			D3D11_RASTERIZER_DESC RasterizerDesc;
			RasterizerDesc.FillMode = D3D11_FILL_SOLID;
			RasterizerDesc.CullMode = D3D11_CULL_NONE;	// カリングをオフ.
			RasterizerDesc.FrontCounterClockwise = FALSE;
			RasterizerDesc.DepthBias = 0;
			RasterizerDesc.DepthBiasClamp = 0.0f;
			RasterizerDesc.SlopeScaledDepthBias = 0.0f;
			RasterizerDesc.DepthClipEnable = FALSE;
			RasterizerDesc.ScissorEnable = FALSE;
			RasterizerDesc.MultisampleEnable = FALSE;
			RasterizerDesc.AntialiasedLineEnable = FALSE;

			// ラスタライザステートの生成.
			if (FAILED(m_pDevice->CreateRasterizerState(&RasterizerDesc, &m_pRasterizerState)))
			{
				OutputErrorLog("ラスタライザステートの作成に失敗しました");
				ReleaseDisplay();
				return false;
			}

			m_pDeviceContext->RSSetState(m_pRasterizerState);	// ラスタライザステートをセット.

			return true;
		}

		void GraphicsDevice::ReleaseDevice()
		{
			SafeRelease(m_pDeviceContext);
			SafeRelease(m_pDevice);
		}

		void GraphicsDevice::ReleaseDisplay()
		{
			SafeRelease(m_pRasterizerState);
			SafeRelease(m_pDepthStencilView[BACKBUFFER_TARGET]);
			SafeRelease(m_pDepthStencilBuffer);
			SafeRelease(m_pRenderTargetView[BACKBUFFER_TARGET]);
			SafeRelease(m_pBackBuffer);
			SafeRelease(m_pDXGISwapChain);
			SafeRelease(m_pDXGIFactory);
			SafeRelease(m_pAdapter);
			SafeRelease(m_pDXGI);
		}
	}
}

