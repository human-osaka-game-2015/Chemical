/**
 * @file   RankingButton.cpp
 * @brief  RankingReturnButtonクラスの実装
 * @author fujioka
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "RankingButton.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "DirectX11\GraphicsDevice\Dx11GraphicsDevice.h"
#include "TaskManager\TaskManager.h"
#include "InputDeviceManager\InputDeviceManager.h"


namespace Select
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	RankingReturnButton::RankingReturnButton()
	{
		m_Pos = D3DXVECTOR2(1700, 900);
		m_Size = D3DXVECTOR2(200, 100);
	}

	RankingReturnButton::~RankingReturnButton()
	{
	}


	//----------------------------------------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------------------------------------

	bool RankingReturnButton::Initialize()
	{
		if (!CreateVertex2D())
		{
			return false;
		}

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture("Resource\\StageSelectScene\\RankingWindow\\Texture\\RankingButton.bmp", &m_TextureIndex))
		{
			return false;
		}

		m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));

		return true;
	}

	void RankingReturnButton::Finalize()
	{
		ReleaseVertex2D();
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);
	}


	void RankingReturnButton::Update()
	{
	}

}

