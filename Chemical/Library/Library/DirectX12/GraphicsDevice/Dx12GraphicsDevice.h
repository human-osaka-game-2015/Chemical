/**
 * @file	Dx12GraphicsDevice.h
 * @brief	グラフィックスデバイスの管理クラス定義
 * @author	morimoto
 */
#ifndef LIB_DX12_GRAPHICSDEVICE_H
#define LIB_DX12_GRAPHICSDEVICE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <D3D12.h>
#include <DXGI1_4.h>
#include <D3DX10.h>

#include "..\..\SingletonBase\SingletonBase.h"


namespace Lib
{
	namespace Dx12
	{
		/**
		 * グラフィックデバイスの管理クラス定義
		 */
		class GraphicsDevice : public SingletonBase<GraphicsDevice>
		{
		public:
			friend SingletonBase<GraphicsDevice>;

			/**
			 * 初期化処理
			 * @return 初期化に成功したらtrue 失敗したらfalse
			 */
			bool Initialize();

			/**
			 * 終了処理
			 */
			void Finalize();

			/**
			 * デバイスの取得
			 * @return DirectX12デバイス
			 */
			inline ID3D12Device* GetDevice()
			{
				return m_pDevice;
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
			 * デバイスの解放関数
			 */
			void ReleaseDevice();


			ID3D12Device*	m_pDevice;	//!< デバイス.

		};
	}
}


#endif // !LIB_DX12_GRAPHICSDEVICE_H
