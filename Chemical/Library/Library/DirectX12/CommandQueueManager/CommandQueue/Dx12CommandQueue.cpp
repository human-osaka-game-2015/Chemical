/**
 * @file	Dx12CommandQueue.cpp
 * @brief	コマンドキュークラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Dx12CommandQueue.h"

#include "Debugger\Debugger.h"


namespace Lib
{
	namespace Dx12
	{
		//----------------------------------------------------------------------
		// Constructor	Destructor
		//----------------------------------------------------------------------
		CommandQueue::CommandQueue(CommandList::COMMAND_LIST_TYPE _type, int _priority) :
			m_pCommandQueue(nullptr),
			//m_pFence(nullptr),
			//m_FenceValue(0),
			//m_FenceEventHandle(nullptr),
			m_Type(_type),
			m_Priority(_priority)
		{
			CreateCommandQueue();
		}

		CommandQueue::~CommandQueue()
		{
			ReleaseCommandQueue();
		}


		//----------------------------------------------------------------------
		// Public Functions
		//----------------------------------------------------------------------
		ID3D12CommandQueue* CommandQueue::Get() const
		{
			return m_pCommandQueue;
		}


		//----------------------------------------------------------------------
		// Private Functions
		//----------------------------------------------------------------------
		void CommandQueue::CreateCommandQueue()
		{
			D3D12_COMMAND_QUEUE_DESC CommandQueueDesc;
			ZeroMemory(&CommandQueueDesc, sizeof(CommandQueueDesc));
			CommandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
			CommandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
			if (FAILED(SINGLETON_INSTANCE(Lib::Dx12::GraphicsDevice)->GetDevice()->CreateCommandQueue(
				&CommandQueueDesc,
				__uuidof(*(m_pCommandQueue)),
				reinterpret_cast<void**>(&m_pCommandQueue))))
			{
				OutputErrorLog("コマンドキューの生成に失敗しました");
			}


			///@todo フェンスの作成を行うか検討中.


		}

		void CommandQueue::ReleaseCommandQueue()
		{
			SafeRelease(m_pCommandQueue);
		}
	}
}
