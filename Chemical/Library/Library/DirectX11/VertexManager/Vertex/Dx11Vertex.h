/**
 * @file	Dx11Vertex.h
 * @brief	頂点クラス定義
 * @author	morimoto
 */
#ifndef LIB_DX11_VERTEX_H
#define LIB_DX11_VERTEX_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\IVertex\Dx11IVertex.h"


namespace Lib
{
	namespace Dx11
	{
		/**
		 * 頂点クラス
		 */
		class Vertex : public IVertex
		{
		public:
			/**
			 * コンストラクタ
			 */
			Vertex();

			/**
			 * デストラクタ
			 */
			virtual ~Vertex();

		};
	}
}


#endif // !LIB_DX11_VERTEX_H
