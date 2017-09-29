/**
 * @file	Dx11Texture.cpp
 * @brief	テクスチャクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Dx11Texture.h"

#include "..\..\..\Debugger\Debugger.h"
#include "..\..\GraphicsDevice\Dx11GraphicsDevice.h"


namespace Lib
{

	namespace Dx11
	{
		//----------------------------------------------------------------------
		// Constructor	Destructor
		//----------------------------------------------------------------------
		Texture::Texture() :
			m_pGraphicsDevice(nullptr),
			m_pTexture(nullptr)
		{
		}

		Texture::Texture(GraphicsDevice* _pGraphicsDevice, LPCTSTR _pTexturePath) :
			m_pGraphicsDevice(_pGraphicsDevice),
			m_pTexture(nullptr)
		{
			Load(_pTexturePath);
		}

		Texture::~Texture()
		{
			Release();
		}


		//----------------------------------------------------------------------
		// Public Functions
		//----------------------------------------------------------------------
		void Texture::Set(ID3D11ShaderResourceView* _pTexture)
		{
			m_pTexture = _pTexture;
			m_pTexture->AddRef();
		}

		ID3D11ShaderResourceView* Texture::Get() const
		{
			return m_pTexture;
		}


		//----------------------------------------------------------------------
		// Private Functions
		//----------------------------------------------------------------------
		void Texture::Load(LPCTSTR _pTexturePath)
		{
			MyAssert(m_pGraphicsDevice == nullptr, "GraphicsDeviceがありません");


			D3DX11_IMAGE_LOAD_INFO LoadInfo;
			ZeroMemory(&LoadInfo, sizeof(D3DX11_IMAGE_LOAD_INFO));
			LoadInfo.Width = D3DX11_DEFAULT;
			LoadInfo.Height = D3DX11_DEFAULT;
			LoadInfo.Depth = D3DX11_DEFAULT;
			LoadInfo.FirstMipLevel = D3DX11_DEFAULT;
			LoadInfo.MipLevels = 1;
			LoadInfo.Usage = D3D11_USAGE_DEFAULT;
			LoadInfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;
			LoadInfo.CpuAccessFlags = 0;
			LoadInfo.MiscFlags = 0;
			LoadInfo.Format = DXGI_FORMAT_FROM_FILE;
			LoadInfo.Filter = D3DX11_FILTER_POINT;
			LoadInfo.MipFilter = D3DX11_FILTER_POINT;
			LoadInfo.pSrcInfo = nullptr;

			if (FAILED(D3DX11CreateShaderResourceViewFromFile(
				m_pGraphicsDevice->GetDevice(),
				_pTexturePath,
				&LoadInfo,
				nullptr,
				&m_pTexture,
				nullptr)))
			{
				OutputErrorLog("テクスチャの読み込みに失敗しました");
			}
		}

		void Texture::Release()
		{
			SafeRelease(m_pTexture);
		}
	}
}
