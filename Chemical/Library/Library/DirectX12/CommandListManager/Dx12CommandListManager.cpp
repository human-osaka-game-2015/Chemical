/**
 * @file	Dx12CommandListManager.cpp
 * @brief	コマンドリスト管理クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Dx12CommandListManager.h"


namespace Lib
{
	namespace Dx12
	{
		//----------------------------------------------------------------------
		// Constructor	Destructor
		//----------------------------------------------------------------------
		CommandListManager::CommandListManager()
		{
		}

		CommandListManager::~CommandListManager()
		{
		}


		//----------------------------------------------------------------------
		// Public Functions
		//----------------------------------------------------------------------
		bool CommandListManager::Initialize(GraphicsDevice* _pGraphicsDevice)
		{
			m_pGraphicsDevice = _pGraphicsDevice;
			return true;
		}

		void CommandListManager::Finalize()
		{
			for (auto itr = m_pCommandLists.begin(); itr != m_pCommandLists.end(); itr++)
			{
				SafeRelease(*itr);
			}

			m_pGraphicsDevice = nullptr;
		}
	}
}
