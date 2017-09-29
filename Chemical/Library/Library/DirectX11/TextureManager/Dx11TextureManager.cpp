/**
 * @file	Dx11TextureManager.cpp
 * @brief	テクスチャ管理クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Dx11TextureManager.h"

#include "..\GraphicsDevice\Dx11GraphicsDevice.h"
#include "Texture\Dx11Texture.h"


namespace Lib
{
	namespace Dx11
	{
		//----------------------------------------------------------------------
		// Static Public Variables
		//----------------------------------------------------------------------
		const int TextureManager::m_InvalidIndex = 0;


		//----------------------------------------------------------------------
		// Constructor	Destructor
		//----------------------------------------------------------------------
		TextureManager::TextureManager() :
			m_pGraphicsDevice(nullptr)
		{
			// 読み込みに失敗した際に参照する値としてnullptrを追加.
			m_pTextures.push_back(nullptr);
		}

		TextureManager::~TextureManager()
		{
			Finalize();
		}


		//----------------------------------------------------------------------
		// Public Functions
		//----------------------------------------------------------------------
		bool TextureManager::Initialize(GraphicsDevice* _pGraphicsDevice)
		{
			m_pGraphicsDevice = _pGraphicsDevice;
			return true;
		}

		void TextureManager::Finalize()
		{
			for (auto itr = m_pTextures.begin(); itr != m_pTextures.end(); itr++)
			{
				SafeDelete(*itr);
			}
		}

		bool TextureManager::LoadTexture(LPCTSTR _pTexturePath, int* _pIndex)
		{
			Texture* pTexture = new Texture(m_pGraphicsDevice, _pTexturePath);

			if (pTexture->Get() == nullptr)
			{
				SafeDelete(pTexture);
				*_pIndex = m_InvalidIndex;
				return false;
			}

			*_pIndex = m_pTextures.size();
			m_pTextures.push_back(pTexture);

			return true;
		}

		void TextureManager::ReleaseTexture(int _index)
		{
			SafeDelete(m_pTextures[_index]);
		}

		ITexture* TextureManager::GetTexture(int _index) const
		{
			return m_pTextures[_index];
		}

		void TextureManager::ClearBuffer()
		{
			m_pTextures.clear();
		}
	}
}

