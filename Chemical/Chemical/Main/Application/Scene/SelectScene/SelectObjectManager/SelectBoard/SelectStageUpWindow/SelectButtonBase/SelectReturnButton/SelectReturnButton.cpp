/**
 * @file   SelectReturnButton.cpp
 * @brief  ReturnButtonクラスの実装
 * @author kotani
 */
#include "SelectReturnButton.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "DirectX11\GraphicsDevice\Dx11GraphicsDevice.h"
#include "TaskManager\TaskManager.h"


namespace Select
{
	ReturnButton::ReturnButton()
	{
		m_Pos.x = 830.f + m_Size.x / 2;
	}

	ReturnButton::~ReturnButton()
	{
	}


	//----------------------------------------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------------------------------------

	bool ReturnButton::Initialize()
	{
		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\StageSelectScene\\Texture\\ReturnButton.png",
			&m_TextureIndex)) return false;

		if (!CreateVertex2D()) return false;
		m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));

		return true;
	}

	void ReturnButton::Finalize()
	{
		ReleaseVertex2D();
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);
	}

	void ReturnButton::OnClick()
	{
	}
}
