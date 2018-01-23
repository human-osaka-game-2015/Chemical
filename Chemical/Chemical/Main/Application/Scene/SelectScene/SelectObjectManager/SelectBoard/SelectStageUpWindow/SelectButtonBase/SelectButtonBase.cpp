/**
 * @file   SelectButtonBase.cpp
 * @brief  ButtonBaseクラスの実装
 * @author kotani
 */
#include "SelectButtonBase.h"

namespace Select
{
	ButtonBase::ButtonBase() :
		m_OnCursor(false)
	{
		m_Size = D3DXVECTOR2(1920,1080);
		m_DefaultSize = m_Size;
		m_OnCursorSize.x = m_DefaultSize.x + 20.f;
		m_OnCursorSize.y = m_DefaultSize.y + 20.f;
		//m_Pos.y = 680.f;
	}

	ButtonBase::~ButtonBase()
	{
	}


	//----------------------------------------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------------------------------------

	void ButtonBase::Update()
	{
	}

	void ButtonBase::Draw(float _alpha)
	{
		if (m_OnCursor)
		{
			m_pVertex->ShaderSetup();
			m_pVertex->WriteConstantBuffer(&m_Pos);
			m_pVertex->WriteVertexBuffer();
			m_pVertex->Draw();
			m_OnCursor = false;
		}
	}
}
