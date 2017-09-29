/**
 * @file	Dx12SwapChain.h
 * @brief	スワップチェインクラス定義
 * @author	morimoto
 */
#ifndef LIB_DX11_SWAPCHAIN_H
#define LIB_DX11_SWAPCHAIN_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "SingletonBase\SingletonBase.h"


namespace Lib
{
	namespace Dx12
	{
		class SwapChain : public SingletonBase<SwapChain>
		{
		public:
			friend SingletonBase<SwapChain>;

		private:
			/**
			 * コンストラクタ
			 */
			SwapChain();

			/**
			 * デストラクタ
			 */
			virtual ~SwapChain();

		};
	}
}


#endif // !LIB_DX11_SWAPCHAIN_H
