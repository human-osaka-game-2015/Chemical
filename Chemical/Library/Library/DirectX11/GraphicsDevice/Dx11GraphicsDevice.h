/**
 * @file	Dx11GraphicsDevice.h
 * @brief	グラフィックデバイスの管理クラス定義
 * @author	morimoto
 */
#ifndef LIB_DX11_GRAPHICSDEVICE_H
#define LIB_DX11_GRAPHICSDEVICE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <D3DX11.h>
#include <D3DX10.h>

#include "..\..\SingletonBase\SingletonBase.h"


namespace Lib
{
	namespace Dx11
	{
		/**
		 * グラフィックデバイスの管理クラス定義
		 */
		class GraphicsDevice : public SingletonBase<GraphicsDevice>
		{
		public:
			friend SingletonBase<GraphicsDevice>;

			static const int m_RenderTargetNum = D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT;	//!< 描画先の最大設定数.
			static const int m_ScreenShotCountMax;	//!< スクリーンショットの最大作成数.


			/**
			 * レンダーターゲットの識別子
			 */
			enum RENDER_TARGET
			{
				BACKBUFFER_TARGET = 0	//!< バックバッファ.
			};

			/**
			 * 初期化処理
			 * @param[in] _hWnd GraphicsDeviceが対応するウィンドウのハンドル
			 * @return 初期化に成功したらtrue 失敗したらfalse
			 */
			bool Initialize(HWND _hWnd);

			/**
			 * 終了処理
			 */
			void Finalize();

			/**
			 * 描画前処理
			 * @param[in] _stage 初期化するステージ
			 */
			void BeginScene(int _stage);

			/**
			 * シーンの切り替えを行う
			 */
			void SetScene(int _stage);

			/**
			 * 描画後処理
			 */
			void EndScene();

			/**
			 * レンダーターゲットの割り当て
			 * @param[in] _pRenderTarget 割り当てるレンダーターゲット
			 * @param[in] _stage レンダーターゲットを割り当てるステージ
			 * @return 割り当てに成功したらtrue 失敗したらfalse
			 */
			bool SetRenderTarget(ID3D11RenderTargetView** _pRenderTarget, int _stage);

			/**
			 * 深度ステンシルの割り当て
			 * @param[in] _pRenderTarget 割り当てる深度ステンシル
			 * @param[in] _stage 深度ステンシルを割り当てるステージ
			 * @return 割り当てに成功したらtrue 失敗したらfalse
			 */
			bool SetDepthStencil(ID3D11DepthStencilView** _pDepthStencilView, int _stage);

			/**
			 * ビューポートの割り当て
			 * @param[in] _pViewPort 割り当てるビューポート
			 * @param[in] _stage ビューポートを割り当てるステージ
			 * @return 割り当てに成功したらtrue 失敗したらfalse
			 */
			bool SetViewPort(const D3D11_VIEWPORT* _pViewPort, int _stage);

			/**
			 * クリアカラーの割り当て
			 * @param[in] _clearColor 割り当てるカラー値
			 * @param[in] _stage カラー値を割り当てるステージ
			 * @return 割り当てに成功したらtrue 失敗したらfalse
			 */
			bool SetClearColor(D3DXCOLOR _clearColor, int _stage);

			/**
			 * バックバッファのスクリーンショット作成(png形式のみ対応)
			 * @param[in] _filePath 生成したファイルのパス
			 * @return スクリーンショットの作成に成功したらtrue 失敗したらfalse
			 */
			bool CreateScreenShot(LPCTSTR _filePath);

			/**
			 * DirectXデバイスの取得
			 * @return DirectXデバイス
			 */
			inline ID3D11Device* GetDevice() const
			{
				return m_pDevice;
			}

			/**
			 * デバイスコンテキストの取得
			 * @return デバイスコンテキスト
			 */
			inline ID3D11DeviceContext* GetDeviceContext() const
			{
				return m_pDeviceContext;
			}

			/**
			 * GraphicsDeviceに結びついているウィンドウのハンドルを取得する
			 * @return ウィンドウハンドル
			 */
			inline HWND GetMainWindowHandle() const
			{
				return m_hWnd;
			}

			/**
			 * GraphicsDeviceに結びついているウィンドウのサイズを取得する
			 * @return ウィンドウサイズ
			 */
			inline const RECT* GetMainWindowRect() const
			{
				return &m_WindowRect;
			}

			/**
			 * バックバッファの取得
			 * @return バックバッファ
			 */
			inline ID3D11Texture2D* GetBackBuffer() const
			{
				return m_pBackBuffer;
			}

			/**
			 * 深度バッファの取得
			 * @return 深度バッファ
			 */
			inline ID3D11Texture2D* GetDepthStencil() const
			{
				return m_pDepthStencilBuffer;
			}

			/**
			 * フルスクリーン設定を行う
			 * @param[in] _isFullScreenState フルスクリーンの設定
			 */
			inline void SetFullScreen(bool _isFullScreenState)
			{
				m_pDXGISwapChain->SetFullscreenState(_isFullScreenState, nullptr);
			}

		private:
			/**
			 * コンストラクタ
			 */
			GraphicsDevice();

			/**
			 * デストラクタ
			 */
			virtual ~GraphicsDevice();

			/**
			 * デバイスの初期化関数
			 * @return 初期化に成功したらtrue 失敗したらfalse
			 */
			bool CreateDevice();

			/**
			 * ディスプレイ系の初期化関数
			 * @return 初期化に成功したらtrue 失敗したらfalse
			 */
			bool CreateDisplay();

			/**
			 * デバイスの解放関数
			 */
			void ReleaseDevice();

			/**
			 * ディスプレイ系の解放関数
			 */
			void ReleaseDisplay();


			ID3D11Device*			m_pDevice;				//!< DirectX11デバイス.
			ID3D11DeviceContext*	m_pDeviceContext;		//!< DirectX11デバイスコンテキスト.
			IDXGIDevice1*			m_pDXGI;				//!< DirectX11グラフィックインストラクチャ.
			IDXGIAdapter*			m_pAdapter;				//!< DXGIのアダプタ.
			IDXGIFactory*			m_pDXGIFactory;			//!< DXGIのファクトリ.
			IDXGISwapChain*			m_pDXGISwapChain;		//!< スワップチェイン.
			ID3D11Texture2D*		m_pBackBuffer;			//!< バックバッファテクスチャ.

			float					m_ClearColor[m_RenderTargetNum][4];		//!< バッファをクリアするときのカラー値.
			ID3D11RenderTargetView* m_pRenderTargetView[m_RenderTargetNum];	//!< バックバッファのレンダーターゲットビュー.
			ID3D11Texture2D*		m_pDepthStencilBuffer;					//!< 深度ステンシルバッファテクスチャ.
			ID3D11DepthStencilView* m_pDepthStencilView[m_RenderTargetNum];	//!< 深度ステンシルビュー.
			D3D11_VIEWPORT			m_ViewPort[m_RenderTargetNum];			//!< ビューポート.

			ID3D11RasterizerState*  m_pRasterizerState;		//!< ラスタライザステート.
			HWND					m_hWnd;					//!< 対応するウィンドウハンドル.
			RECT					m_WindowRect;			//!< ウィンドウの矩形情報.

			int						m_ScreenShotCount;		//!< スクリーンショットの作成数.


			DISALLOW_COPY_AND_ASSIGN(GraphicsDevice);

		};
	}
}


#endif // !LIB_DX11_GRAPHICSDEVICE_H
