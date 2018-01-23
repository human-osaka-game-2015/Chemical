#include "SelectRankingButton.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "DirectX11\GraphicsDevice\Dx11GraphicsDevice.h"
#include "TaskManager\TaskManager.h"
#include "Application\Application.h"


namespace Select
{
	RankingButton::RankingButton()
	{
		m_Pos.x = static_cast<float>(Application::m_WindowWidth / 2);
		m_Pos.y = static_cast<float>(Application::m_WindowHeight / 2);
	}

	RankingButton::~RankingButton()
	{
	}


	//----------------------------------------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------------------------------------

	bool RankingButton::Initialize()
	{
		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\StageSelectScene\\Texture\\button_ranking.png",
			&m_TextureIndex)) return false;

		if (!CreateVertex2D()) return false;
		m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));

		return true;
	}

	void RankingButton::Finalize()
	{
		ReleaseVertex2D();
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);
	}

	void RankingButton::OnClick()
	{
	}
}
