/**
 * @file   Dx11FbxFileManager.cpp
 * @brief  FbxFileManagerクラスの実装
 * @author morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Dx11FbxFileManager.h"

#include "DirectX11\GraphicsDevice\Dx11GraphicsDevice.h"
#include "Debugger\Debugger.h"
#include "FbxLoader\Dx11FbxLoader.h"


namespace Lib
{
	namespace Dx11
	{
		//----------------------------------------------------------------------------------------------------
		// Static Public Variables
		//----------------------------------------------------------------------------------------------------
		const int FbxFileManager::m_InvalidIndex = 0;


		//----------------------------------------------------------------------------------------------------
		// Constructor	Destructor
		//----------------------------------------------------------------------------------------------------
		FbxFileManager::FbxFileManager() :
			m_pFbxLoader(nullptr)
		{
			m_pFbxModel.push_back(nullptr);	// 読み込みに失敗した際に参照する値としてnullptrを追加.
		}

		FbxFileManager::~FbxFileManager()
		{
		}


		//----------------------------------------------------------------------------------------------------
		// Public Functions
		//----------------------------------------------------------------------------------------------------
		bool FbxFileManager::Initialize(GraphicsDevice* _pGraphicsDevice)
		{
			MyAssert(m_pFbxLoader != nullptr, "FbxFileManagerオブジェクトは既に初期化されています");

			m_pGraphicsDevice = _pGraphicsDevice;
			m_pFbxLoader = new FbxLoader(m_pGraphicsDevice);

			return m_pFbxLoader->Initialize();
		}

		void FbxFileManager::Finalize()
		{
			if (m_pFbxLoader != nullptr)
			{
				m_pFbxLoader->Finalize();
				SafeDelete(m_pFbxLoader);
			}
		}

		bool FbxFileManager::LoadFbxModel(LPCTSTR _pFileName, int* _pIndex)
		{
			FbxModel* pModel = new FbxModel(m_pGraphicsDevice);
			if (!m_pFbxLoader->LoadFbxModel(pModel, _pFileName))
			{
				OutputErrorLog("Fbxモデルの読み込みに失敗しました");

				*_pIndex = m_InvalidIndex;
				SafeDelete(pModel);

				return false;
			}

			if (!pModel->Initialize())
			{
				OutputErrorLog("Fbxモデルの初期化に失敗しました");

				pModel->Finalize();
				SafeDelete(pModel);

				return false;
			}

			*_pIndex = m_pFbxModel.size();
			m_pFbxModel.push_back(pModel);

			return true;
		}

		void FbxFileManager::ReleaseFbxModel(int _index)
		{
			if (m_pFbxModel[_index] != nullptr)
			{
				m_pFbxModel[_index]->Finalize();
				SafeDelete(m_pFbxModel[_index]);
			}
		}
	}
}
