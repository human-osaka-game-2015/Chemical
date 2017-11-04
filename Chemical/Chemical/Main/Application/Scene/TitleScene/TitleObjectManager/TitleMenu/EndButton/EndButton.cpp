/**
 * @file	EndButton.cpp
 * @brief	終了ボタンクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EndButton.h"

#include "..\..\..\TitleDefine.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "InputDeviceManager\InputDeviceManager.h"


namespace Title
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	EndButton::EndButton()
	{
		m_Pos = D3DXVECTOR2(1005, 850);
		m_Size = D3DXVECTOR2(300, 100);
	}

	EndButton::~EndButton()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool EndButton::Initialize()
	{
		if (!CreateVertex2D())	return false;

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\TitleScene\\Texture\\End.png",
			&m_TextureIndex))
		{
			return false;
		}

		return true;
	}

	void EndButton::Finalize()
	{
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);

		ReleaseVertex2D();
	}

	void EndButton::Update()
	{
	}

	void EndButton::Draw()
	{
		m_pVertex->ShaderSetup();
		m_pVertex->WriteConstantBuffer(&m_Pos);
		m_pVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pVertex->Draw();
	}
}
