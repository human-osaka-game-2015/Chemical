/**
 * @file	TlsfAllocator.cpp
 * @brief	TLSFメモリアロケータクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "TlsfAllocator.h"


namespace Lib
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	TlsfAllocator::TlsfAllocator() :
		m_MemoryPool(nullptr)
	{
	}

	TlsfAllocator::~TlsfAllocator()
	{
	}
}
