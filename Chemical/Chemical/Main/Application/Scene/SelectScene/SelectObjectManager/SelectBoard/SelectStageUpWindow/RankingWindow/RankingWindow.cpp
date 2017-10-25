/**
 * @file   RankingWindow.cpp
 * @brief  RankingWindowクラスの実装
 * @author fujioka
 */
#include "RankingWindow.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "DirectX11\GraphicsDevice\Dx11GraphicsDevice.h"
#include "TaskManager\TaskManager.h"

namespace Select
{
	RankingWindow::RankingWindow()
	{
		m_Pos = D3DXVECTOR2(640, 360);
		m_Size = D3DXVECTOR2(1280, 720);
	}

	RankingWindow::~RankingWindow()
	{
	}


	//----------------------------------------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------------------------------------

	bool RankingWindow::Initialize()
	{
		if (!CreateVertex2D())
		{
			return false;
		}

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture("Resource\\StageSelectScene\\RankingWindow\\Texture\\RankingWindow.bmp", &m_TextureIndex))
		{
			return false;
		}

		m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));

		return true;
	}

	void RankingWindow::Finalize()
	{	
		ReleaseVertex2D();

		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);
	}

	
	void RankingWindow::Update()
	{
	}

	
}

