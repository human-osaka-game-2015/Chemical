/**
 * @file   RankingWindow.cpp
 * @brief  RankingWindowクラスの実装
 * @author fujioka
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "RankingWindow.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "DirectX11\GraphicsDevice\Dx11GraphicsDevice.h"
#include "TaskManager\TaskManager.h"


namespace Select
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	RankingWindow::RankingWindow(int _stageNum) :
		m_StageNum(_stageNum)
	{
		m_Pos = D3DXVECTOR2(960, 540);
		m_Size = D3DXVECTOR2(1920, 1080);
	}

	RankingWindow::~RankingWindow()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool RankingWindow::Initialize()
	{
		if (!CreateVertex2D())
		{
			return false;
		}

		char FilePath[256];
		sprintf_s(FilePath, 256, "Resource\\StageSelectScene\\RankingWindow\\Texture\\%d.png", m_StageNum);

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			FilePath,
			&m_TextureIndex)) return false;

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

