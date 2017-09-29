#ifndef LIB_DX12_COMMANDLIST_H
#define LIB_DX12_COMMANDLIST_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\Dx12CommandListManager.h"


namespace Lib
{
	namespace Dx12
	{
		class CommandList
		{
		public:
			/**
			 * コマンドリストの種類
			 */
			enum COMMAND_LIST_TYPE
			{
				COMMAND_LIST_TYPE_DIRECT = 0,	//!< 描画関係のコマンド.
				COMMAND_LIST_TYPE_BUNDLE = 1,	//!< バンドル用コマンド.
				COMMAND_LIST_TYPE_COMPUTE = 2,	//!< コンピュートシェーダー用コマンド.
				COMMAND_LIST_TYPE_COPY = 3,		//!< リソースコピー用コマンド.
				COMMAND_LIST_TYPE_MAX			//!< コマンド種類数.
			};

			/**
			 * コンストラクタ
			 */
			CommandList();

			/**
			 * デストラクタ
			 */
			~CommandList();

		private:


		};
	}
}


#endif // !LIB_DX12_COMMANDLIST_H
