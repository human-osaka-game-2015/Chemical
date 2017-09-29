/**
 * @file	Dx12CommandQueueManager.h
 * @brief	コマンドキュー管理クラス定義
 * @author	morimoto
 */
#ifndef LIB_DX12_COMMANDQUEUEMANAGER_H
#define LIB_DX12_COMMANDQUEUEMANAGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\SingletonBase\SingletonBase.h"

#include <D3D12.h>
#include <vector>
#include "..\GraphicsDevice\Dx12GraphicsDevice.h"
#include "..\CommandListManager\Dx12CommandListManager.h"


namespace Lib
{
	namespace Dx12
	{
		class CommandQueue;

		/**
		 * コマンドキューの管理クラス
		 */
		class CommandQueueManager : public SingletonBase<CommandQueueManager>
		{
		public:
			friend SingletonBase<CommandQueueManager>;

			static const int m_InvalidIndex;	//!< CommandQueueManagerクラスがとるインデックスエラー値.

			/**
			 * 初期化処理
			 * @param[in] _pGraphicsDevice コマンドキュー作成用グラフィックデバイス
			 * @return 成功したらtrue 失敗したらfalse
			 */
			bool Initialize(GraphicsDevice* _pGraphicsDevice);

			/**
			 * 終了処理
			 */
			void Finalize();

			/**
			 * コマンドキューの作成
			 * @param[out] _pindex 作成したコマンドキューのインデックス
			 * @param[in] _type 作成するコマンドキューの種類
			 * @param[in] _priority コマンドキューの優先度
			 * @return 成功したらtrue 失敗したらfalse
			 */
			bool CreateCommandQueue(
				int* _pIndex,
				CommandList::COMMAND_LIST_TYPE _type = CommandList::COMMAND_LIST_TYPE_DIRECT,
				int _priority = 0);

			/**
			 * コマンドキューの解放
			 * @param[in] _index 解放するコマンドキューのインデックス
			 */
			void ReleaseCommandQueue(int _index);

		private:
			/**
			 * コンストラクタ
			 */
			CommandQueueManager();

			/**
			 * デストラクタ
			 */
			virtual ~CommandQueueManager();


			GraphicsDevice*				m_pGraphicsDevice;	//!< グラフィックデバイス.
			std::vector<CommandQueue*>	m_pCommandQueues;	//!< コマンドキュー.

		};
	}
}


#endif // !LIB_DX12_COMMANDQUEUEMANAGER_H
