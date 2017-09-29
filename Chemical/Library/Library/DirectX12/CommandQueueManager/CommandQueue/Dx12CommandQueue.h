/**
 * @file	Dx12CommandQueue.h
 * @brief	コマンドキュークラス定義
 * @author	morimoto
 */
#ifndef LIB_DX12_COMMANDQUEUE_H
#define LIB_DX12_COMMANDQUEUE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <D3D12.h>
#include <DXGI1_4.h>

#include "..\Dx12CommandQueueManager.h"


namespace Lib
{
	namespace Dx12
	{
		/**
		 * コマンドキュー
		 */
		class CommandQueue
		{
		public:
			enum PRIORITY_TYPE
			{
				PRIORITY_NORMAL = 1,	//!< 通常優先度.
				PRIORITY_HIGH = 100		//!< 高優先度.
			};

			/**
			 * コンストラクタ
			 * @param[in] _type 作成するコマンドキューの種類
			 * @param[in] _priority コマンドキューの優先度
			 */
			CommandQueue(
				CommandList::COMMAND_LIST_TYPE _type = CommandList::COMMAND_LIST_TYPE_DIRECT,
				int _priority = 0);

			/**
			 * デストラクタ
			 */
			~CommandQueue();

			/**
			 * コマンドキューの取得
			 * @return コマンドキュー
			 */
			ID3D12CommandQueue* Get() const;

		private:
			/**
			 * コマンドキュー生成
			 */
			void CreateCommandQueue();

			/**
			 * コマンドキュー解放
			 */
			void ReleaseCommandQueue();


			ID3D12CommandQueue*				m_pCommandQueue;	//!< コマンドキュー.
			//ID3D12Fence*					m_pFence;			//!< フェンス.
			//int								m_FenceValue;		//!< フェンス値.
			//HANDLE							m_FenceEventHandle;	//!< フェンスのイベントハンドル.
			CommandList::COMMAND_LIST_TYPE	m_Type;				//!< コマンドキューの種類.
			int								m_Priority;			//!< コマンドキューの優先度.

		};
	}
}


#endif // !LIB_DX12_COMMANDQUEUE_H
