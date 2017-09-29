/**
 * @file	Dx11IVertex.h
 * @brief	頂点インターフェース定義
 * @author	morimoto
 */
#ifndef LIB_DX11_IVERTEX_H
#define LIB_DX11_IVERTEX_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <Windows.h>

#include "..\..\..\Define\Define.h"


namespace Lib
{
	namespace Dx11
	{
		/**
		 * 頂点インターフェース
		 */
		interface IVertex
		{
		public:
			/**
			 * コンストラクタ
			 */
			IVertex();

			/**
			 * デストラクタ
			 */
			virtual ~IVertex();

		};
	}
}


#endif // !LIB_DX11_IVERTEX_H
