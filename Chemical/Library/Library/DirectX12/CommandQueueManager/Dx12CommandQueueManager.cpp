/**
 * @file	Dx12CommandQueueManager.cpp
 * @brief	コマンドキュークラス実装.
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Dx12CommandQueueManager.h"

#include "CommandQueue\Dx12CommandQueue.h"
#include "Debugger\Debugger.h"


namespace Lib
{
	namespace Dx12
	{
		//----------------------------------------------------------------------
		// Static Public Variables
		//----------------------------------------------------------------------
		const int CommandQueueManager::m_InvalidIndex = 0;


		//----------------------------------------------------------------------
		// Constructor	Destructor
		//----------------------------------------------------------------------
		CommandQueueManager::CommandQueueManager()
		{
			// 生成に失敗した際に参照する値としてnullptrを追加.
			m_pCommandQueues.push_back(nullptr);
		}

		CommandQueueManager::~CommandQueueManager()
		{
		}


		//----------------------------------------------------------------------
		// Public Functions
		//----------------------------------------------------------------------
		bool CommandQueueManager::Initialize(GraphicsDevice* _pGraphicsDevice)
		{
			m_pGraphicsDevice = _pGraphicsDevice;
			return true;
		}

		void CommandQueueManager::Finalize()
		{
			for (auto itr = m_pCommandQueues.begin(); itr != m_pCommandQueues.end(); itr++)
			{
				SafeDelete(*itr);
			}

			m_pGraphicsDevice = nullptr;
		}

		bool CommandQueueManager::CreateCommandQueue(
			int* _pIndex,
			CommandList::COMMAND_LIST_TYPE _type,
			int _priority)
		{
			CommandQueue* pCommandQueue = new CommandQueue(_type, _priority);

			if (pCommandQueue->Get() == nullptr)
			{
				SafeDelete(pCommandQueue);
				*_pIndex = m_InvalidIndex;
				return false;
			}

			*_pIndex = m_pCommandQueues.size();
			m_pCommandQueues.push_back(pCommandQueue);

			return true;
		}

		void CommandQueueManager::ReleaseCommandQueue(int _index)
		{
			SafeDelete(m_pCommandQueues[_index]);
		}
	}
}
