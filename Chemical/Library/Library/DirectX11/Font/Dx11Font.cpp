/**
 * @file	Dx11Font.cpp
 * @brief	フォントクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Dx11Font.h"

#include "Debugger\Debugger.h"


namespace Lib
{
	namespace Dx11
	{
		//----------------------------------------------------------------------
		// Static Private Variables
		//----------------------------------------------------------------------
		const float Font::m_FontTu = 1.0f / 95;
		const int Font::m_SpaceAsciiCode = 32;

		//----------------------------------------------------------------------
		// Constructor	Destructor
		//----------------------------------------------------------------------
		Font::Font() :
			m_pGraphicsDevice(nullptr),
			m_pVertexShader(nullptr),
			m_pVertexCompiledShader(nullptr),
			m_pVertexLayout(nullptr),
			m_pPixelShader(nullptr),
			m_pPixelCompiledShader(nullptr),
			m_pBlendState(nullptr),
			m_pSamplerState(nullptr),
			m_pVertexBuffer(nullptr),
			m_pConstantBuffer(nullptr),
			m_pShaderResource(nullptr),
			m_WindowWidth(0),
			m_WindowHeight(0),
			m_IsAlignmentRight(true),
			m_pDrawFunc(&Font::AlignmentRightDraw)
		{
		}

		Font::~Font()
		{
		}


		//----------------------------------------------------------------------
		// Public Functions
		//----------------------------------------------------------------------
		bool Font::Initialize(GraphicsDevice* _pGraphicsDevice)
		{
			if (m_pGraphicsDevice != nullptr)
			{
				OutputErrorLog("フォントオブジェクトは既に初期化されています");
				return false;
			}

			m_pGraphicsDevice = _pGraphicsDevice;

			RECT WindowRect;
			GetWindowRect(m_pGraphicsDevice->GetMainWindowHandle(), &WindowRect);
			m_WindowWidth = static_cast<float>(WindowRect.right - WindowRect.left);
			m_WindowHeight = static_cast<float>(WindowRect.bottom - WindowRect.top);


			if (!CreateVertexShader())
			{
				return false;
			}

			if (!CreateVertexLayout())
			{
				ReleaseVertexShader();
				return false;
			}

			if (!CreatePixelShader())
			{
				ReleaseVertexLayout();
				ReleaseVertexShader();
				return false;
			}

			if (!CreateState())
			{
				ReleasePixelShader();
				ReleaseVertexLayout();
				ReleaseVertexShader();
				return false;
			}

			if (!CreateResourceView())
			{
				ReleaseState();
				ReleasePixelShader();
				ReleaseVertexLayout();
				ReleaseVertexShader();
				return false;
			}

			return true;
		}

		void Font::Finalize()
		{
			ReleaseResourceView();
			ReleaseState();
			ReleasePixelShader();
			ReleaseVertexLayout();
			ReleaseVertexShader();
		}

		bool Font::CreateVertexBuffer(const D3DXVECTOR2* _pSize, const D3DXCOLOR* _pColor)
		{
			m_FontSize = *_pSize;
			FONT_VERTEX FontVertex[] =
			{
				D3DXVECTOR3(-m_FontSize.x / 2, -m_FontSize.y / 2, 0), D3DXVECTOR2(0, 0), *_pColor,
				D3DXVECTOR3(m_FontSize.x / 2, -m_FontSize.y / 2, 0), D3DXVECTOR2(m_FontTu, 0), *_pColor,
				D3DXVECTOR3(-m_FontSize.x / 2, m_FontSize.y / 2, 0), D3DXVECTOR2(0, 1), *_pColor,
				D3DXVECTOR3(m_FontSize.x / 2, m_FontSize.y / 2, 0), D3DXVECTOR2(m_FontTu, 1), *_pColor,
			};

			// 頂点バッファの設定.
			D3D11_BUFFER_DESC BufferDesc;
			ZeroMemory(&BufferDesc, sizeof(BufferDesc));
			BufferDesc.ByteWidth = sizeof(FontVertex);
			BufferDesc.Usage = D3D11_USAGE_DEFAULT;
			BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			BufferDesc.CPUAccessFlags = 0;
			BufferDesc.MiscFlags = 0;

			// 頂点バッファに格納するデータの設定.
			D3D11_SUBRESOURCE_DATA ResourceData;
			ZeroMemory(&ResourceData, sizeof(ResourceData));
			ResourceData.pSysMem = reinterpret_cast<void*>(FontVertex);
			ResourceData.SysMemPitch = 0;
			ResourceData.SysMemSlicePitch = 0;

			// 頂点バッファの生成.
			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateBuffer(&BufferDesc, &ResourceData, &m_pVertexBuffer)))
			{
				OutputErrorLog("頂点バッファの生成に成功しました");
				return false;
			}

			return true;
		}

		void Font::ReleaseVertexBuffer()
		{
			SafeRelease(m_pVertexBuffer);
		}

		void Font::Draw(const D3DXVECTOR2* _pDrawPos, LPCTSTR _pStr)
		{
			(this->*m_pDrawFunc)(_pDrawPos, _pStr);
		}

		//----------------------------------------------------------------------
		// Private Functions
		//----------------------------------------------------------------------
		bool Font::CreateVertexShader()
		{
			// fxファイルの読み込み.
			ID3DBlob* pShaderErrors = nullptr;
			if (FAILED(D3DX11CompileFromFile(
				TEXT("Library\\DirectX11\\Font\\Effect\\Font.fx"),
				nullptr,
				nullptr,
				"VS",
				"vs_5_0",
				D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION,
				0,
				nullptr,
				&m_pVertexCompiledShader,
				&pShaderErrors,
				nullptr)))
			{
				SafeRelease(pShaderErrors);
				return false;
			}

			SafeRelease(pShaderErrors);

			// 頂点シェーダーの生成.
			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateVertexShader(
				m_pVertexCompiledShader->GetBufferPointer(),
				m_pVertexCompiledShader->GetBufferSize(),
				nullptr,
				&m_pVertexShader)))
			{
				SafeRelease(m_pVertexCompiledShader);
				return false;
			}

			return true;
		}

		bool Font::CreateVertexLayout()
		{
			// 頂点入力レイアウトの設定.
			D3D11_INPUT_ELEMENT_DESC InputElementDesc[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 }
			};

			// 頂点入力レイアウトの生成.
			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateInputLayout(
				InputElementDesc,
				sizeof(InputElementDesc) / sizeof(InputElementDesc[0]),
				m_pVertexCompiledShader->GetBufferPointer(),
				m_pVertexCompiledShader->GetBufferSize(),
				&m_pVertexLayout)))
			{
				return false;
			}

			return true;
		}

		bool Font::CreatePixelShader()
		{
			// fxファイルの読み込み.
			ID3DBlob* pShaderErrors = nullptr;
			if (FAILED(D3DX11CompileFromFile(
				TEXT("Library\\DirectX11\\Font\\Effect\\Font.fx"),
				nullptr,
				nullptr,
				"PS",
				"ps_5_0",
				D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION,
				0,
				nullptr,
				&m_pPixelCompiledShader,
				&pShaderErrors,
				nullptr)))
			{
				SafeRelease(pShaderErrors);
				return false;
			}

			SafeRelease(pShaderErrors);

			// ピクセルシェーダーの生成.
			if (FAILED(m_pGraphicsDevice->GetDevice()->CreatePixelShader(
				m_pPixelCompiledShader->GetBufferPointer(),
				m_pPixelCompiledShader->GetBufferSize(),
				nullptr,
				&m_pPixelShader)))
			{
				SafeRelease(m_pPixelCompiledShader);
				return false;
			}

			return true;
		}

		bool Font::CreateState()
		{
			// ブレンドステートの設定.
			D3D11_BLEND_DESC BlendDesc;
			ZeroMemory(&BlendDesc, sizeof(D3D11_BLEND_DESC));
			BlendDesc.AlphaToCoverageEnable = false;
			BlendDesc.IndependentBlendEnable = false;
			BlendDesc.RenderTarget[0].BlendEnable = true;
			BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

			// ブレンドステートの生成.
			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateBlendState(&BlendDesc, &m_pBlendState)))
			{
				ReleaseState();
				return false;
			}

			// サンプラステートの設定.
			D3D11_SAMPLER_DESC SamplerDesc;
			ZeroMemory(&SamplerDesc, sizeof(D3D11_SAMPLER_DESC));
			SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

			// サンプラステートの生成.
			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateSamplerState(&SamplerDesc, &m_pSamplerState)))
			{
				ReleaseState();
				return false;
			}

			// 定数バッファの設定.
			D3D11_BUFFER_DESC ConstantBufferDesc;
			ZeroMemory(&ConstantBufferDesc, sizeof(D3D11_BUFFER_DESC));
			ConstantBufferDesc.ByteWidth = sizeof(CONSTANT_BUFFER);
			ConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			ConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			ConstantBufferDesc.MiscFlags = 0;
			ConstantBufferDesc.StructureByteStride = 0;

			// 定数バッファの生成.
			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateBuffer(&ConstantBufferDesc, nullptr, &m_pConstantBuffer)))
			{
				ReleaseState();
				return false;
			}

			return true;
		}

		bool Font::CreateResourceView()
		{
			// テクスチャ読み込みの設定.
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

			// テクスチャ読み込み.
			if (FAILED(D3DX11CreateShaderResourceViewFromFile(
				m_pGraphicsDevice->GetDevice(),
				TEXT("Library\\DirectX11\\Font\\Texture\\Font.png"),
				&LoadInfo,
				nullptr,
				&m_pShaderResource,
				nullptr)))
			{
				OutputErrorLog("テクスチャの読み込みに失敗しました");
				return false;
			}

			return true;
		}

		void Font::ReleaseVertexShader()
		{
			SafeRelease(m_pVertexShader);
			SafeRelease(m_pVertexCompiledShader);
		}

		void Font::ReleaseVertexLayout()
		{
			SafeRelease(m_pVertexLayout);
		}

		void Font::ReleasePixelShader()
		{
			SafeRelease(m_pPixelShader);
			SafeRelease(m_pPixelCompiledShader);
		}

		void Font::ReleaseState()
		{
			SafeRelease(m_pConstantBuffer);
			SafeRelease(m_pSamplerState);
			SafeRelease(m_pBlendState);
		}

		void Font::ReleaseResourceView()
		{
			SafeRelease(m_pShaderResource);
		}

		void Font::AlignmentRightDraw(const D3DXVECTOR2* _pDrawPos, LPCTSTR _pStr)
		{
			m_pGraphicsDevice->GetDeviceContext()->VSSetShader(m_pVertexShader, nullptr, 0);
			m_pGraphicsDevice->GetDeviceContext()->PSSetShader(m_pPixelShader, nullptr, 0);

			m_pGraphicsDevice->GetDeviceContext()->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
			m_pGraphicsDevice->GetDeviceContext()->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

			m_pGraphicsDevice->GetDeviceContext()->IASetInputLayout(m_pVertexLayout);
			m_pGraphicsDevice->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

			m_pGraphicsDevice->GetDeviceContext()->PSSetSamplers(0, 1, &m_pSamplerState);
			m_pGraphicsDevice->GetDeviceContext()->PSSetShaderResources(0, 1, &m_pShaderResource);

			m_pGraphicsDevice->GetDeviceContext()->OMSetBlendState(m_pBlendState, nullptr, 0xffffffff);

			UINT Stride = sizeof(FONT_VERTEX);
			UINT Offset = 0;
			m_pGraphicsDevice->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &Stride, &Offset);


			D3DXMATRIX MatWorld, MatTranslate, MatRotate;
			D3DXMatrixIdentity(&MatWorld);
			D3DXMatrixScaling(&MatWorld, 1.0f, 1.0f, 1.0f);
			D3DXMatrixRotationZ(&MatRotate, 0.0f);
			D3DXMatrixMultiply(&MatWorld, &MatWorld, &MatRotate);
			D3DXMatrixTranslation(&MatTranslate, _pDrawPos->x, _pDrawPos->y, 0.0f);
			D3DXMatrixMultiply(&MatWorld, &MatWorld, &MatTranslate);

			int StrLength = static_cast<int>(strlen(_pStr));
			for (int i = 0; i < StrLength; i++)
			{
				D3D11_MAPPED_SUBRESOURCE MappedResource;
				CONSTANT_BUFFER ConstantBuffer;
				m_pGraphicsDevice->GetDeviceContext()->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);

				ConstantBuffer.MatWorld = MatWorld;
				D3DXMatrixTranspose(&ConstantBuffer.MatWorld, &ConstantBuffer.MatWorld);

				ConstantBuffer.WindowSize.x = m_WindowWidth;
				ConstantBuffer.WindowSize.y = m_WindowHeight;

				ConstantBuffer.TexelOffset.x = static_cast<float>(_pStr[i] - m_SpaceAsciiCode) * m_FontTu;
				ConstantBuffer.TexelOffset.y = 0.0f;
				ConstantBuffer.TexelOffset.z = 0.0f;
				ConstantBuffer.TexelOffset.w = 0.0f;

				ConstantBuffer.PosOffset.x = i * m_FontSize.x - StrLength * m_FontSize.x;
				ConstantBuffer.PosOffset.y = 0;
				ConstantBuffer.PosOffset.z = 0;
				ConstantBuffer.PosOffset.w = 0;

				memcpy_s(
					MappedResource.pData,
					MappedResource.RowPitch,
					reinterpret_cast<void*>(&ConstantBuffer),
					sizeof(ConstantBuffer));

				m_pGraphicsDevice->GetDeviceContext()->Unmap(m_pConstantBuffer, 0);

				m_pGraphicsDevice->GetDeviceContext()->Draw(VERTEX_NUM, 0);
			}
		}

		void Font::AlignmentLeftDraw(const D3DXVECTOR2* _pDrawPos, LPCTSTR _pStr)
		{
			m_pGraphicsDevice->GetDeviceContext()->VSSetShader(m_pVertexShader, nullptr, 0);
			m_pGraphicsDevice->GetDeviceContext()->PSSetShader(m_pPixelShader, nullptr, 0);

			m_pGraphicsDevice->GetDeviceContext()->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
			m_pGraphicsDevice->GetDeviceContext()->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

			m_pGraphicsDevice->GetDeviceContext()->IASetInputLayout(m_pVertexLayout);
			m_pGraphicsDevice->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

			m_pGraphicsDevice->GetDeviceContext()->PSSetSamplers(0, 1, &m_pSamplerState);
			m_pGraphicsDevice->GetDeviceContext()->PSSetShaderResources(0, 1, &m_pShaderResource);

			m_pGraphicsDevice->GetDeviceContext()->OMSetBlendState(m_pBlendState, nullptr, 0xffffffff);

			UINT Stride = sizeof(FONT_VERTEX);
			UINT Offset = 0;
			m_pGraphicsDevice->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &Stride, &Offset);


			D3DXMATRIX MatWorld, MatTranslate, MatRotate;
			D3DXMatrixIdentity(&MatWorld);
			D3DXMatrixScaling(&MatWorld, 1.0f, 1.0f, 1.0f);
			D3DXMatrixRotationZ(&MatRotate, 0.0f);
			D3DXMatrixMultiply(&MatWorld, &MatWorld, &MatRotate);
			D3DXMatrixTranslation(&MatTranslate, _pDrawPos->x, _pDrawPos->y, 0.0f);
			D3DXMatrixMultiply(&MatWorld, &MatWorld, &MatTranslate);

			for (int i = 0; i < static_cast<int>(strlen(_pStr)); i++)
			{
				D3D11_MAPPED_SUBRESOURCE MappedResource;
				CONSTANT_BUFFER ConstantBuffer;
				m_pGraphicsDevice->GetDeviceContext()->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);

				ConstantBuffer.MatWorld = MatWorld;
				D3DXMatrixTranspose(&ConstantBuffer.MatWorld, &ConstantBuffer.MatWorld);

				ConstantBuffer.WindowSize.x = m_WindowWidth;
				ConstantBuffer.WindowSize.y = m_WindowHeight;

				ConstantBuffer.TexelOffset.x = static_cast<float>(_pStr[i] - m_SpaceAsciiCode) * m_FontTu;
				ConstantBuffer.TexelOffset.y = 0.0f;
				ConstantBuffer.TexelOffset.z = 0.0f;
				ConstantBuffer.TexelOffset.w = 0.0f;

				ConstantBuffer.PosOffset.x = i * m_FontSize.x;
				ConstantBuffer.PosOffset.y = 0;
				ConstantBuffer.PosOffset.z = 0;
				ConstantBuffer.PosOffset.w = 0;

				memcpy_s(
					MappedResource.pData,
					MappedResource.RowPitch,
					reinterpret_cast<void*>(&ConstantBuffer),
					sizeof(ConstantBuffer));

				m_pGraphicsDevice->GetDeviceContext()->Unmap(m_pConstantBuffer, 0);

				m_pGraphicsDevice->GetDeviceContext()->Draw(VERTEX_NUM, 0);
			}
		}
	}
}
