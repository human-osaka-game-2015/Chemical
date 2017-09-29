/**
 * @file	Dx11ShaderManager.cpp
 * @brief	シェーダーの管理クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Dx11ShaderManager.h"

#include "..\GraphicsDevice\Dx11GraphicsDevice.h"
#include "..\..\Debugger\Debugger.h"


namespace Lib
{
	namespace Dx11
	{
		//----------------------------------------------------------------------
		// Static Public Variables
		//----------------------------------------------------------------------
		const int ShaderManager::m_InvalidIndex = 0;


		//----------------------------------------------------------------------
		// Constructor	Destructor
		//----------------------------------------------------------------------
		ShaderManager::ShaderManager() :
			m_pGraphicsDevice(nullptr)
		{
			// 読み込みに失敗した際に参照する値としてnullptrを追加.
			m_pVertexShader.push_back(nullptr);
			m_pPixelShader.push_back(nullptr);
			m_pCompiledVertexShader.push_back(nullptr);
			m_pCompiledPixelShader.push_back(nullptr);
		}

		ShaderManager::~ShaderManager()
		{
			Finalize();
		}

		//----------------------------------------------------------------------
		// Public Functions
		//----------------------------------------------------------------------
		bool ShaderManager::Initialize(GraphicsDevice* _pGraphicsDevice)
		{
			m_pGraphicsDevice = _pGraphicsDevice;
			return true;
		}

		void ShaderManager::Finalize()
		{
			ReleaseVertexShader();
			ReleasePixelShader();
		}

		bool ShaderManager::LoadVertexShader(LPCTSTR _pFilePath, LPCTSTR _pFuncName, int* _pIndex)
		{
			if (m_pGraphicsDevice == nullptr)
			{
				OutputErrorLog("グラフィックデバイスがありません");
				return false;
			}


			UINT Flag1 = D3D10_SHADER_ENABLE_STRICTNESS;
#ifdef _DEBUG
			Flag1 |= D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#else
			Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
#endif // _DEBUG

			ID3D11VertexShader* pVertexShader = nullptr;
			ID3DBlob* pShaderErrors = nullptr;
			ID3DBlob* pCompiledShader = nullptr;
			if (FAILED(D3DX11CompileFromFile(
				_pFilePath,
				nullptr,
				nullptr,
				_pFuncName,
				"vs_5_0",
				Flag1,
				0,
				nullptr,
				&pCompiledShader,
				&pShaderErrors,
				nullptr)))
			{
				OutputErrorLog("fxファイルの読み込みに失敗しました");
				SafeRelease(pShaderErrors);
				*_pIndex = m_InvalidIndex;
				return false;
			}

			SafeRelease(pShaderErrors);


			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateVertexShader(
				pCompiledShader->GetBufferPointer(),
				pCompiledShader->GetBufferSize(),
				nullptr,
				&pVertexShader)))
			{
				OutputErrorLog("頂点シェーダーの生成に失敗しました");
				SafeRelease(pCompiledShader);
				*_pIndex = m_InvalidIndex;
				return false;
			}

			*_pIndex = m_pVertexShader.size();
			m_pVertexShader.push_back(pVertexShader);
			m_pCompiledVertexShader.push_back(pCompiledShader);

			return true;
		}

		bool ShaderManager::LoadPixelShader(LPCTSTR _pFilePath, LPCTSTR _pFuncName, int* _pIndex)
		{
			if (m_pGraphicsDevice == nullptr)
			{
				OutputErrorLog("グラフィックデバイスがありません");
				return false;
			}


			UINT Flag1 = D3D10_SHADER_ENABLE_STRICTNESS;
#ifdef _DEBUG
			Flag1 |= D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#else
			Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
#endif // _DEBUG

			ID3D11PixelShader* pPixelShader = nullptr;
			ID3DBlob* pShaderErrors = nullptr;
			ID3DBlob* pCompiledShader = nullptr;
			if (FAILED(D3DX11CompileFromFile(
				_pFilePath,
				nullptr,
				nullptr,
				_pFuncName,
				"ps_5_0",
				Flag1,
				0,
				nullptr,
				&pCompiledShader,
				&pShaderErrors,
				nullptr)))
			{
				OutputErrorLog("fxファイルの読み込みに失敗しました");
				SafeRelease(pShaderErrors);
				*_pIndex = m_InvalidIndex;
				return false;
			}

			SafeRelease(pShaderErrors);

			if (FAILED(m_pGraphicsDevice->GetDevice()->CreatePixelShader(
				pCompiledShader->GetBufferPointer(),
				pCompiledShader->GetBufferSize(),
				nullptr,
				&pPixelShader)))
			{
				OutputErrorLog("ピクセルシェーダーの生成に失敗しました");
				SafeRelease(pCompiledShader);
				*_pIndex = m_InvalidIndex;
				return false;
			}

			*_pIndex = m_pPixelShader.size();
			m_pPixelShader.push_back(pPixelShader);
			m_pCompiledPixelShader.push_back(pCompiledShader);

			return true;
		}


		bool ShaderManager::LoadGeometryShader(LPCTSTR _pFilePath, LPCTSTR _pFuncName, int* _pIndex)
		{
			if (m_pGraphicsDevice == nullptr)
			{
				OutputErrorLog("グラフィックデバイスがありません");
				return false;
			}


			UINT Flag1 = D3D10_SHADER_ENABLE_STRICTNESS;
#ifdef _DEBUG
			Flag1 |= D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#else
			Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
#endif // _DEBUG

			ID3D11GeometryShader* pGeometryShader = nullptr;
			ID3DBlob* pShaderErrors = nullptr;
			ID3DBlob* pCompiledShader = nullptr;
			if (FAILED(D3DX11CompileFromFile(
				_pFilePath,
				nullptr,
				nullptr,
				_pFuncName,
				"gs_5_0",
				Flag1,
				0,
				nullptr,
				&pCompiledShader,
				&pShaderErrors,
				nullptr)))
			{
				OutputErrorLog("fxファイルの読み込みに失敗しました");
				SafeRelease(pShaderErrors);
				*_pIndex = m_InvalidIndex;
				return false;
			}

			SafeRelease(pShaderErrors);

			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateGeometryShader(
				pCompiledShader->GetBufferPointer(),
				pCompiledShader->GetBufferSize(),
				nullptr,
				&pGeometryShader)))
			{
				OutputErrorLog("ジオメトリシェーダーの生成に失敗しました");
				SafeRelease(pCompiledShader);
				*_pIndex = m_InvalidIndex;
				return false;
			}

			*_pIndex = m_pGeometryShader.size();
			m_pGeometryShader.push_back(pGeometryShader);
			m_pCompiledGeometryShader.push_back(pCompiledShader);

			return true;
		}

		bool ShaderManager::LoadHullShader(LPCTSTR _pFilePath, LPCTSTR _pFuncName, int* _pIndex)
		{
			if (m_pGraphicsDevice == nullptr)
			{
				OutputErrorLog("グラフィックデバイスがありません");
				return false;
			}


			UINT Flag1 = D3D10_SHADER_ENABLE_STRICTNESS;
#ifdef _DEBUG
			Flag1 |= D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#else
			Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
#endif // _DEBUG

			ID3D11HullShader* pHullShader = nullptr;
			ID3DBlob* pShaderErrors = nullptr;
			ID3DBlob* pCompiledShader = nullptr;
			if (FAILED(D3DX11CompileFromFile(
				_pFilePath,
				nullptr,
				nullptr,
				_pFuncName,
				"hs_5_0",
				Flag1,
				0,
				nullptr,
				&pCompiledShader,
				&pShaderErrors,
				nullptr)))
			{
				OutputErrorLog("fxファイルの読み込みに失敗しました");
				SafeRelease(pShaderErrors);
				*_pIndex = m_InvalidIndex;
				return false;
			}

			SafeRelease(pShaderErrors);

			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateHullShader(
				pCompiledShader->GetBufferPointer(),
				pCompiledShader->GetBufferSize(),
				nullptr,
				&pHullShader)))
			{
				OutputErrorLog("ハルシェーダーの生成に失敗しました");
				SafeRelease(pCompiledShader);
				*_pIndex = m_InvalidIndex;
				return false;
			}

			*_pIndex = m_pHullShader.size();
			m_pHullShader.push_back(pHullShader);
			m_pCompiledHullShader.push_back(pCompiledShader);

			return true;
		}

		bool ShaderManager::LoadDomainShader(LPCTSTR _pFilePath, LPCTSTR _pFuncName, int* _pIndex)
		{
			if (m_pGraphicsDevice == nullptr)
			{
				OutputErrorLog("グラフィックデバイスがありません");
				return false;
			}


			UINT Flag1 = D3D10_SHADER_ENABLE_STRICTNESS;
#ifdef _DEBUG
			Flag1 |= D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#else
			Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
#endif // _DEBUG

			ID3D11DomainShader* pDomainShader = nullptr;
			ID3DBlob* pShaderErrors = nullptr;
			ID3DBlob* pCompiledShader = nullptr;
			if (FAILED(D3DX11CompileFromFile(
				_pFilePath,
				nullptr,
				nullptr,
				_pFuncName,
				"ds_5_0",
				Flag1,
				0,
				nullptr,
				&pCompiledShader,
				&pShaderErrors,
				nullptr)))
			{
				OutputErrorLog("fxファイルの読み込みに失敗しました");
				SafeRelease(pShaderErrors);
				*_pIndex = m_InvalidIndex;
				return false;
			}

			SafeRelease(pShaderErrors);

			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateDomainShader(
				pCompiledShader->GetBufferPointer(),
				pCompiledShader->GetBufferSize(),
				nullptr,
				&pDomainShader)))
			{
				OutputErrorLog("ドメインシェーダーの生成に失敗しました");
				SafeRelease(pCompiledShader);
				*_pIndex = m_InvalidIndex;
				return false;
			}

			*_pIndex = m_pDomainShader.size();
			m_pDomainShader.push_back(pDomainShader);
			m_pCompiledDomainShader.push_back(pCompiledShader);

			return true;
		}

		bool ShaderManager::LoadComputeShader(LPCTSTR _pFilePath, LPCTSTR _pFuncName, int* _pIndex)
		{
			if (m_pGraphicsDevice == nullptr)
			{
				OutputErrorLog("グラフィックデバイスがありません");
				return false;
			}


			UINT Flag1 = D3D10_SHADER_ENABLE_STRICTNESS;
#ifdef _DEBUG
			Flag1 |= D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#else
			Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
#endif // _DEBUG

			ID3D11ComputeShader* pComputeShader = nullptr;
			ID3DBlob* pShaderErrors = nullptr;
			ID3DBlob* pCompiledShader = nullptr;
			if (FAILED(D3DX11CompileFromFile(
				_pFilePath,
				nullptr,
				nullptr,
				_pFuncName,
				"cs_5_0",
				Flag1,
				0,
				nullptr,
				&pCompiledShader,
				&pShaderErrors,
				nullptr)))
			{
				OutputErrorLog("fxファイルの読み込みに失敗しました");
				SafeRelease(pShaderErrors);
				*_pIndex = m_InvalidIndex;
				return false;
			}

			SafeRelease(pShaderErrors);

			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateComputeShader(
				pCompiledShader->GetBufferPointer(),
				pCompiledShader->GetBufferSize(),
				nullptr,
				&pComputeShader)))
			{
				OutputErrorLog("コンピュートシェーダの生成に失敗しました");
				SafeRelease(pCompiledShader);
				*_pIndex = m_InvalidIndex;
				return false;
			}

			*_pIndex = m_pComputeShader.size();
			m_pComputeShader.push_back(pComputeShader);
			m_pCompiledComputeShader.push_back(pCompiledShader);

			return true;
		}

		void ShaderManager::ReleaseVertexShader(int _index)
		{
			SafeRelease(m_pVertexShader[_index]);
			SafeRelease(m_pCompiledVertexShader[_index]);
		}

		void ShaderManager::ReleaseVertexShader()
		{
			for (auto itr = m_pVertexShader.begin(); itr != m_pVertexShader.end(); itr++)
			{
				SafeRelease(*itr);
			}

			for (auto itr = m_pCompiledVertexShader.begin(); itr != m_pCompiledVertexShader.end(); itr++)
			{
				SafeRelease(*itr);
			}
		}

		void ShaderManager::ReleasePixelShader(int _index)
		{
			SafeRelease(m_pPixelShader[_index]);
			SafeRelease(m_pCompiledPixelShader[_index]);
		}

		void ShaderManager::ReleasePixelShader()
		{
			for (auto itr = m_pPixelShader.begin(); itr != m_pPixelShader.end(); itr++)
			{
				SafeRelease(*itr);
			}

			for (auto itr = m_pCompiledPixelShader.begin(); itr != m_pCompiledPixelShader.end(); itr++)
			{
				SafeRelease(*itr);
			}
		}

		void ShaderManager::ReleaseGeometryShader(int _index)
		{
			SafeRelease(m_pGeometryShader[_index]);
			SafeRelease(m_pCompiledGeometryShader[_index]);
		}

		void ShaderManager::ReleaseGeometryShader()
		{
			for (auto itr = m_pGeometryShader.begin(); itr != m_pGeometryShader.end(); itr++)
			{
				SafeRelease(*itr);
			}

			for (auto itr = m_pCompiledGeometryShader.begin(); itr != m_pCompiledGeometryShader.end(); itr++)
			{
				SafeRelease(*itr);
			}
		}

		void ShaderManager::ReleaseHullShader(int _index)
		{
			SafeRelease(m_pHullShader[_index]);
			SafeRelease(m_pCompiledHullShader[_index]);
		}

		void ShaderManager::ReleaseHullShader()
		{
			for (auto itr = m_pHullShader.begin(); itr != m_pHullShader.end(); itr++)
			{
				SafeRelease(*itr);
			}

			for (auto itr = m_pCompiledHullShader.begin(); itr != m_pCompiledHullShader.end(); itr++)
			{
				SafeRelease(*itr);
			}
		}

		void ShaderManager::ReleaseDomainShader(int _index)
		{
			SafeRelease(m_pDomainShader[_index]);
			SafeRelease(m_pCompiledDomainShader[_index]);
		}

		void ShaderManager::ReleaseDomainShader()
		{
			for (auto itr = m_pDomainShader.begin(); itr != m_pDomainShader.end(); itr++)
			{
				SafeRelease(*itr);
			}

			for (auto itr = m_pCompiledDomainShader.begin(); itr != m_pCompiledDomainShader.end(); itr++)
			{
				SafeRelease(*itr);
			}
		}

		void ShaderManager::ReleaseComputeShader(int _index)
		{
			SafeRelease(m_pComputeShader[_index]);
			SafeRelease(m_pCompiledComputeShader[_index]);
		}

		void ShaderManager::ReleaseComputeShader()
		{
			for (auto itr = m_pComputeShader.begin(); itr != m_pComputeShader.end(); itr++)
			{
				SafeRelease(*itr);
			}

			for (auto itr = m_pCompiledComputeShader.begin(); itr != m_pCompiledComputeShader.end(); itr++)
			{
				SafeRelease(*itr);
			}
		}
	}
}

