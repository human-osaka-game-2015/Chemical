/**
 * @file	Dx12GraphicsDevice.cpp
 * @brief	グラフィックスデバイスの管理クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Dx12GraphicsDevice.h"

#include "Debugger\Debugger.h"


namespace Lib
{
	namespace Dx12
	{
		//----------------------------------------------------------------------
		// Constructor	Destructor
		//----------------------------------------------------------------------
		GraphicsDevice::GraphicsDevice() : 
			m_pDevice(nullptr)
		{
		}

		GraphicsDevice::~GraphicsDevice()
		{
		}


		//----------------------------------------------------------------------
		// Public Functions
		//----------------------------------------------------------------------
		bool GraphicsDevice::Initialize()
		{
			MyAssert(m_pDevice != nullptr, "GraphicsDeviceオブジェクトは既に初期化されています");

			if (!CreateDevice())
			{
				return false;
			}

			return true;
		}

		void GraphicsDevice::Finalize()
		{
			ReleaseDevice();
		}


		//----------------------------------------------------------------------
		// Private Functions
		//----------------------------------------------------------------------
		bool GraphicsDevice::CreateDevice()
		{
#ifdef _DEBUG
			// デバッグレイヤの有効化(デバッグ情報を出力するように).
			ID3D12Debug* pDebugController;
			if (SUCCEEDED(D3D12GetDebugInterface(
				__uuidof(*(pDebugController)),
				reinterpret_cast<void**>(&pDebugController))))
			{
				pDebugController->EnableDebugLayer();
				pDebugController->Release();
			}
#endif // _DEBUG

			// DirectX12デバイスの生成.
			if (FAILED(D3D12CreateDevice(
				nullptr,								// Adapterの設定.
				D3D_FEATURE_LEVEL_11_0,					// 最小機能レベルの設定.
				__uuidof(*(m_pDevice)),					// UUIDの設定.
				reinterpret_cast<void**>(&m_pDevice))))	// 生成されるデバイスのポインタ.
			{
				OutputErrorLog("DirectX12デバイスの生成に失敗しました");
				return false;
			}

			return true;
		}

		void GraphicsDevice::ReleaseDevice()
		{
			SafeRelease(m_pDevice);
		}
	}
}