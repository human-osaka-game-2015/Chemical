/**
 * @file	Dx11VertexManager.cpp
 * @brief	頂点管理クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Dx11VertexManager.h"

#include "..\GraphicsDevice\Dx11GraphicsDevice.h"
#include "Vertex\Dx11Vertex.h"


namespace Lib
{
	namespace Dx11
	{
		//----------------------------------------------------------------------
		// Constructor	Destructor
		//----------------------------------------------------------------------
		VertexManager::VertexManager()
		{
		}

		VertexManager::~VertexManager()
		{
		}


		//----------------------------------------------------------------------
		// Public Functions
		//----------------------------------------------------------------------
		bool VertexManager::Initialize(GraphicsDevice* _pGraphicsDevice)
		{
			m_pGraphicDevice = _pGraphicsDevice;
			return true;
		}

		void VertexManager::Finalize()
		{
			for (auto itr = m_pVertexs.begin(); itr != m_pVertexs.end(); itr++)
			{
				SafeDelete(*itr);
			}
		}
	}
}
