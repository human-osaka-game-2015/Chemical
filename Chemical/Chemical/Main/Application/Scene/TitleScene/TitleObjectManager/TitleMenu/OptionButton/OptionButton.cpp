/**
 * @file	OptionButton.cpp
 * @brief	オプションボタンクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "OptionButton.h"

#include "..\..\..\TitleDefine.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "InputDeviceManager\InputDeviceManager.h"


namespace Title
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	OptionButton::OptionButton()
	{
		m_Pos = D3DXVECTOR2(655, 600);
		m_Size = D3DXVECTOR2(300, 100);
	}

	OptionButton::~OptionButton()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool OptionButton::Initialize()
	{
		if (!CreateVertex2D())	return false;

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\TitleScene\\Texture\\Option.png",
			&m_TextureIndex))
		{
			return false;
		}

		return true;
	}

	void OptionButton::Finalize()
	{
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);

		ReleaseVertex2D();
	}

	void OptionButton::Update()
	{
	}

	void OptionButton::Draw()
	{
		m_pVertex->ShaderSetup();
		m_pVertex->WriteConstantBuffer(&m_Pos);
		m_pVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pVertex->Draw();
	}
}
