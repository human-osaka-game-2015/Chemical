/**
 * @file	TlsfAllocator.h
 * @brief	TLSFメモリアロケータクラス定義
 * @author	morimoto
 */
#ifndef LIB_TLSFALLOCATOR_H
#define LIB_TLSFALLOCATOR_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <Windows.h>


namespace Lib
{
	/**
	 * TLSFメモリアロケータクラス
	 */
	class TlsfAllocator
	{
	public:
		/**
		 * コンストラクタ
		 */
		TlsfAllocator();

		/**
		 * デストラクタ
		 */
		~TlsfAllocator();


	private:
		void* m_MemoryPool;	//!< メモリプール.

	};
}


#endif // !LIB_TLSFALLOCATOR_H
