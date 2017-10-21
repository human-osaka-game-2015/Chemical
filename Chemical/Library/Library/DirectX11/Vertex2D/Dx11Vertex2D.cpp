/**
 * @file	Dx11Vertex2D.cpp
 * @brief	2Dポリゴンの描画クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Dx11Vertex2D.h"

#include "..\AnimationManager\Animation\Dx11Animation.h"
#include "..\TextureManager\Texture\Dx11Texture.h"
#include "..\..\Debugger\Debugger.h"


namespace Lib
{
	namespace Dx11
	{
		//----------------------------------------------------------------------
		// Constructor	Destructor
		//----------------------------------------------------------------------
		Vertex2D::Vertex2D() :
			m_pGraphicsDevice(nullptr),
			m_pVertexShader(nullptr),
			m_pVertexCompiledShader(nullptr),
			m_pVertexLayout(nullptr),
			m_pPixelShader(nullptr),
			m_pPixelCompiledShader(nullptr),
			m_pBlendState(nullptr),
			m_pSamplerState(nullptr),
			m_pDepthStencilState(nullptr),
			m_pUserDepthStencilState(nullptr),
			m_pVertexBuffer(nullptr),
			m_pConstantBuffer(nullptr),
			m_pTexture(nullptr),
			m_pAnimation(nullptr),
			m_WindowWidth(0),
			m_WindowHeight(0),
			m_IsInverse(false)
		{
		}

		Vertex2D::~Vertex2D()
		{
			Finalize();
		}


		//----------------------------------------------------------------------
		// Public Functions
		//----------------------------------------------------------------------
		bool Vertex2D::Initialize(GraphicsDevice* _pGraphicsDevice)
		{
			if (m_pGraphicsDevice != nullptr)
			{
				OutputErrorLog("このオブジェクトは既に初期化されています");
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
				ReleaseState();
				ReleasePixelShader();
				ReleaseVertexLayout();
				ReleaseVertexShader();
				return false;
			}

			return true;
		}

		void Vertex2D::Finalize()
		{
			ReleaseVertexBuffer();
			ReleaseState();
			ReleasePixelShader();
			ReleaseVertexLayout();
			ReleaseVertexShader();
		}

		bool Vertex2D::CreateVertexBuffer(
			const D3DXVECTOR2* _pSize,
			const D3DXVECTOR2* _pMinUV,
			const D3DXVECTOR2* _pMaxUV, 
			const D3DXCOLOR* _pColor)
		{
			if (m_pVertexBuffer != nullptr)
			{
				OutputErrorLog("頂点バッファはすでに生成されています");
				return false;
			}

			VERTEX VertexData[VERTEX_NUM] =
			{
				VERTEX{ D3DXVECTOR3(-_pSize->x / 2, -_pSize->y / 2, 0), D3DXVECTOR2(_pMinUV->x, _pMinUV->y), *_pColor },
				VERTEX{ D3DXVECTOR3(_pSize->x / 2, -_pSize->y / 2, 0), D3DXVECTOR2(_pMaxUV->x, _pMinUV->y), *_pColor },
				VERTEX{ D3DXVECTOR3(-_pSize->x / 2, _pSize->y / 2, 0), D3DXVECTOR2(_pMinUV->x, _pMaxUV->y), *_pColor },
				VERTEX{ D3DXVECTOR3(_pSize->x / 2, _pSize->y / 2, 0), D3DXVECTOR2(_pMaxUV->x, _pMaxUV->y), *_pColor }
			};

			for (int i = 0; i < VERTEX_NUM; i++)
			{
				m_pVertexData[i].Pos = VertexData[i].Pos;
				m_pVertexData[i].UV = VertexData[i].UV;
				m_pVertexData[i].Color = VertexData[i].Color;
			}

			// 頂点バッファの設定.
			D3D11_BUFFER_DESC BufferDesc;
			ZeroMemory(&BufferDesc, sizeof(D3D11_BUFFER_DESC));
			BufferDesc.ByteWidth = sizeof(VERTEX) * VERTEX_NUM;
			BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			BufferDesc.MiscFlags = 0;
			BufferDesc.StructureByteStride = 0;

			// 頂点バッファに格納するデータの設定.
			D3D11_SUBRESOURCE_DATA ResourceData;
			ZeroMemory(&ResourceData, sizeof(D3D11_SUBRESOURCE_DATA));
			ResourceData.pSysMem = m_pVertexData;

			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateBuffer(&BufferDesc, &ResourceData, &m_pVertexBuffer)))
			{
				OutputErrorLog("頂点バッファの生成に失敗しました");
				return false;
			}

			return true;
		}

		void Vertex2D::ReleaseVertexBuffer()
		{
			SafeRelease(m_pVertexBuffer);
		}

		bool Vertex2D::WriteVertexBuffer()
		{
			D3D11_MAPPED_SUBRESOURCE MappedResource;
			if (SUCCEEDED(m_pGraphicsDevice->GetDeviceContext()->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource)))
			{
				memcpy_s(
					MappedResource.pData,
					MappedResource.RowPitch,
					m_pVertexData,
					sizeof(VERTEX) * VERTEX_NUM);
				m_pGraphicsDevice->GetDeviceContext()->Unmap(m_pVertexBuffer, 0);

				return true;
			}

			return false;
		}

		void Vertex2D::SetVertexPos(const D3DXVECTOR2* _pVertex)
		{
			m_pVertexData[0].Pos.x = _pVertex[0].x;
			m_pVertexData[0].Pos.y = _pVertex[0].y;
			m_pVertexData[1].Pos.x = _pVertex[1].x;
			m_pVertexData[1].Pos.y = _pVertex[1].y;
			m_pVertexData[2].Pos.x = _pVertex[2].x;
			m_pVertexData[2].Pos.y = _pVertex[2].y;
			m_pVertexData[3].Pos.x = _pVertex[3].x;
			m_pVertexData[3].Pos.y = _pVertex[3].y;
		}

		void Vertex2D::SetVertex(const D3DXVECTOR2* _pSize)
		{
			m_pVertexData[0].Pos.x = -_pSize->x / 2;
			m_pVertexData[0].Pos.y = -_pSize->y / 2;
			m_pVertexData[1].Pos.x = _pSize->x / 2;
			m_pVertexData[1].Pos.y = -_pSize->y / 2;
			m_pVertexData[2].Pos.x = -_pSize->x / 2;
			m_pVertexData[2].Pos.y = _pSize->y / 2;
			m_pVertexData[3].Pos.x = _pSize->x / 2;
			m_pVertexData[3].Pos.y = _pSize->y / 2;
		}

		void Vertex2D::SetUV(const D3DXVECTOR2* _pMinUV, const D3DXVECTOR2* _pMaxUV)
		{
			m_pVertexData[0].UV.x = _pMinUV->x;
			m_pVertexData[0].UV.y = _pMinUV->y;
			m_pVertexData[1].UV.x = _pMaxUV->x;
			m_pVertexData[1].UV.y = _pMinUV->y;
			m_pVertexData[2].UV.x = _pMinUV->x;
			m_pVertexData[2].UV.y = _pMaxUV->y;
			m_pVertexData[3].UV.x = _pMaxUV->x;
			m_pVertexData[3].UV.y = _pMaxUV->y;
		}

		void Vertex2D::SetColor(const D3DXCOLOR* _pColor)
		{
			for (int i = 0; i < VERTEX_NUM; i++)
			{
				m_pVertexData[i].Color = *_pColor;
			}
		}

		bool Vertex2D::WriteConstantBuffer(
			const D3DXVECTOR2* _pDrawPos, 
			const D3DXVECTOR2* _pScale, 
			const D3DXVECTOR3* _pAngle)
		{
			D3DXMATRIX MatWorld, MatTranslate, MatRotate;
			D3DXMatrixIdentity(&MatWorld);
			D3DXMatrixScaling(&MatWorld, _pScale->x, _pScale->y, 1.0f);

			D3DXMatrixRotationX(&MatRotate, static_cast<float>(D3DXToRadian(_pAngle->x)));
			D3DXMatrixMultiply(&MatWorld, &MatWorld, &MatRotate);

			D3DXMatrixRotationY(&MatRotate, static_cast<float>(D3DXToRadian(_pAngle->y)));
			D3DXMatrixMultiply(&MatWorld, &MatWorld, &MatRotate);

			D3DXMatrixRotationZ(&MatRotate, static_cast<float>(D3DXToRadian(_pAngle->z)));
			D3DXMatrixMultiply(&MatWorld, &MatWorld, &MatRotate);

			D3DXMatrixTranslation(&MatTranslate, _pDrawPos->x, _pDrawPos->y, 0.0f);
			D3DXMatrixMultiply(&MatWorld, &MatWorld, &MatTranslate);

			D3D11_MAPPED_SUBRESOURCE MappedResource;
			if (SUCCEEDED(m_pGraphicsDevice->GetDeviceContext()->Map(
				m_pConstantBuffer, 
				0,
				D3D11_MAP_WRITE_DISCARD,
				0, 
				&MappedResource)))
			{
				CONSTANT_BUFFER ConstantBuffer;
				ConstantBuffer.MatWorld = MatWorld;
				D3DXMatrixTranspose(&ConstantBuffer.MatWorld, &ConstantBuffer.MatWorld);

				ConstantBuffer.WindowSize.x = m_WindowWidth;
				ConstantBuffer.WindowSize.y = m_WindowHeight;

				memcpy_s(
					MappedResource.pData,
					MappedResource.RowPitch,
					reinterpret_cast<void*>(&ConstantBuffer),
					sizeof(ConstantBuffer));
				m_pGraphicsDevice->GetDeviceContext()->Unmap(m_pConstantBuffer, 0);

				return true;
			}

			return false;
		}

		void Vertex2D::ShaderSetup()
		{
			m_pGraphicsDevice->GetDeviceContext()->VSSetShader(m_pVertexShader, nullptr, 0);
			m_pGraphicsDevice->GetDeviceContext()->PSSetShader(m_pPixelShader, nullptr, 0);
			m_pGraphicsDevice->GetDeviceContext()->GSSetShader(nullptr, nullptr, 0);
			m_pGraphicsDevice->GetDeviceContext()->HSSetShader(nullptr, nullptr, 0);
			m_pGraphicsDevice->GetDeviceContext()->DSSetShader(nullptr, nullptr, 0);
			m_pGraphicsDevice->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		}

		void Vertex2D::Draw()
		{
			// アニメーションインターフェースがあればアニメーションを行う.
			if (m_pAnimation != nullptr)
			{
				Animation::ANIMATION_FRAME* pFrame = m_pAnimation->GetCurrentFrame();
				if (m_IsInverse)
					SetUV(
					&D3DXVECTOR2(pFrame->MaxTu, pFrame->MinTv),
					&D3DXVECTOR2(pFrame->MinTu, pFrame->MaxTv));
				else
					SetUV(
					&D3DXVECTOR2(pFrame->MinTu, pFrame->MinTv),
					&D3DXVECTOR2(pFrame->MaxTu, pFrame->MaxTv));

				WriteVertexBuffer();
			}

			m_pGraphicsDevice->GetDeviceContext()->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
			m_pGraphicsDevice->GetDeviceContext()->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

			m_pGraphicsDevice->GetDeviceContext()->IASetInputLayout(m_pVertexLayout);

			// テクスチャインターフェースがあれば、テクスチャを貼り付ける.
			if (m_pTexture != nullptr)
			{
				ID3D11ShaderResourceView* pTextureResource = m_pTexture->Get();
				m_pGraphicsDevice->GetDeviceContext()->PSSetSamplers(0, 1, &m_pSamplerState);
				m_pGraphicsDevice->GetDeviceContext()->PSSetShaderResources(0, 1, &pTextureResource);
			}

			if (m_pUserDepthStencilState == nullptr)
				m_pGraphicsDevice->GetDeviceContext()->OMSetDepthStencilState(m_pDepthStencilState, 0);
			else
				m_pGraphicsDevice->GetDeviceContext()->OMSetDepthStencilState(m_pUserDepthStencilState, 0);

			m_pGraphicsDevice->GetDeviceContext()->OMSetBlendState(m_pBlendState, nullptr, 0xffffffff);

			UINT Stride = sizeof(VERTEX);
			UINT Offset = 0;
			m_pGraphicsDevice->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &Stride, &Offset);

			m_pGraphicsDevice->GetDeviceContext()->Draw(VERTEX_NUM, 0);
		}


		//----------------------------------------------------------------------
		// Private Functions
		//----------------------------------------------------------------------
		bool Vertex2D::CreateVertexShader()
		{
			UINT Flag1 = D3D10_SHADER_ENABLE_STRICTNESS;
#ifdef _DEBUG
			Flag1 |= D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#else
			Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
#endif // _DEBUG

			ID3DBlob* pShaderErrors = nullptr;
			if (FAILED(D3DX11CompileFromFile(
				TEXT("Library\\DirectX11\\Vertex2D\\Effect\\Vertex2D.fx"),
				nullptr,
				nullptr,
				"VS",
				"vs_5_0",
				Flag1,
				0,
				nullptr,
				&m_pVertexCompiledShader,
				&pShaderErrors,
				nullptr)))
			{
				OutputErrorLog("頂点シェーダーの読み込みに失敗しました");
				SafeRelease(pShaderErrors);
				return false;
			}

			SafeRelease(pShaderErrors);

			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateVertexShader(
				m_pVertexCompiledShader->GetBufferPointer(),
				m_pVertexCompiledShader->GetBufferSize(),
				nullptr,
				&m_pVertexShader)))
			{
				OutputErrorLog("頂点シェーダーの生成に失敗しました");
				SafeRelease(m_pVertexCompiledShader);
				return false;
			}

			return true;
		}

		bool Vertex2D::CreateVertexLayout()
		{
			D3D11_INPUT_ELEMENT_DESC InputElementDesc[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 }
			};

			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateInputLayout(
				InputElementDesc,
				sizeof(InputElementDesc) / sizeof(InputElementDesc[0]),
				m_pVertexCompiledShader->GetBufferPointer(),
				m_pVertexCompiledShader->GetBufferSize(),
				&m_pVertexLayout)))
			{
				OutputErrorLog("入力レイアウトの生成に失敗しました");
				return false;
			}

			return true;
		}

		bool Vertex2D::CreatePixelShader()
		{
			UINT Flag1 = D3D10_SHADER_ENABLE_STRICTNESS;
#ifdef _DEBUG
			Flag1 |= D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#else
			Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
#endif // _DEBUG

			ID3DBlob* pShaderErrors = nullptr;
			if (FAILED(D3DX11CompileFromFile(
				TEXT("Library\\DirectX11\\Vertex2D\\Effect\\Vertex2D.fx"),
				nullptr,
				nullptr,
				"PS",
				"ps_5_0",
				Flag1,
				0,
				nullptr,
				&m_pPixelCompiledShader,
				&pShaderErrors,
				nullptr)))
			{
				OutputErrorLog("ピクセルシェーダーの読み込みに失敗しました");
				SafeRelease(pShaderErrors);
				return false;
			}

			SafeRelease(pShaderErrors);

			if (FAILED(m_pGraphicsDevice->GetDevice()->CreatePixelShader(
				m_pPixelCompiledShader->GetBufferPointer(),
				m_pPixelCompiledShader->GetBufferSize(),
				nullptr,
				&m_pPixelShader)))
			{
				OutputErrorLog("ピクセルシェーダーの生成に失敗しました");
				SafeRelease(m_pPixelCompiledShader);
				return false;
			}

			return true;
		}

		bool Vertex2D::CreateState()
		{
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
			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateBlendState(
				&BlendDesc,
				&m_pBlendState)))
			{
				OutputErrorLog("ブレンドステートの生成に失敗しました");
				ReleaseState();
				return false;
			}

			D3D11_SAMPLER_DESC SamplerDesc;
			ZeroMemory(&SamplerDesc, sizeof(D3D11_SAMPLER_DESC));
			SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateSamplerState(
				&SamplerDesc,
				&m_pSamplerState)))
			{
				OutputErrorLog("サンプラステートの生成に失敗しました");
				ReleaseState();
				return false;
			}

			D3D11_DEPTH_STENCIL_DESC DepthStencilDesc;
			ZeroMemory(&DepthStencilDesc, sizeof(DepthStencilDesc));
			DepthStencilDesc.DepthEnable = TRUE;
			DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			DepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
			DepthStencilDesc.StencilEnable = FALSE;
			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateDepthStencilState(
				&DepthStencilDesc,
				&m_pDepthStencilState)))
			{
				OutputErrorLog("深度ステンシルステートの生成に失敗しました");
				ReleaseState();
				return false;
			}

			D3D11_BUFFER_DESC ConstantBufferDesc;
			ZeroMemory(&ConstantBufferDesc, sizeof(D3D11_BUFFER_DESC));
			ConstantBufferDesc.ByteWidth = sizeof(CONSTANT_BUFFER);
			ConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			ConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			ConstantBufferDesc.MiscFlags = 0;
			ConstantBufferDesc.StructureByteStride = 0;
			if (FAILED(m_pGraphicsDevice->GetDevice()->CreateBuffer(
				&ConstantBufferDesc,
				nullptr,
				&m_pConstantBuffer)))
			{
				OutputErrorLog("定数バッファの生成に失敗しました");
				ReleaseState();
				return false;
			}

			return true;
		}

		void Vertex2D::ReleaseVertexShader()
		{
			SafeRelease(m_pVertexShader);
			SafeRelease(m_pVertexCompiledShader);
		}

		void Vertex2D::ReleaseVertexLayout()
		{
			SafeRelease(m_pVertexLayout);
		}

		void Vertex2D::ReleasePixelShader()
		{
			SafeRelease(m_pPixelShader);
			SafeRelease(m_pPixelCompiledShader);
		}

		void Vertex2D::ReleaseState()
		{
			SafeRelease(m_pConstantBuffer);
			SafeRelease(m_pDepthStencilState);
			SafeRelease(m_pSamplerState);
			SafeRelease(m_pBlendState);
		}
	}
}

