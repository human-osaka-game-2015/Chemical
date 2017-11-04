/**
 * @file	TitleMenuButtonBase.cpp
 * @brief	タイトルメニューアイテム基底クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "TitleMenuButtonBase.h"

#include "..\..\..\TitleDefine.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "InputDeviceManager\InputDeviceManager.h"


namespace Title
{
	//----------------------------------------------------------------------
	// Static Private Variables
	//----------------------------------------------------------------------
	const float MenuButtonBase::m_MoveSpeed = 15.f;
	const float MenuButtonBase::m_UpPos = 750.f;
	const float MenuButtonBase::m_DownPos = 850.f;
	const float MenuButtonBase::m_LeftPos = 960.f;
	const float MenuButtonBase::m_RightPos = 1005.f;
	const float MenuButtonBase::m_LeftCenterPos = 975.f;
	const float MenuButtonBase::m_RightCenterPos = 990.f;


	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	MenuButtonBase::MenuButtonBase()
	{
	}

	MenuButtonBase::~MenuButtonBase()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool MenuButtonBase::Initialize()
	{
		return true;
	}

	void MenuButtonBase::Finalize()
	{
	}

	void MenuButtonBase::Update()
	{
	}

	void MenuButtonBase::Draw()
	{
	}

	bool MenuButtonBase::MoveUp()
	{
		m_Pos.y -= m_MoveSpeed;
		if (m_Pos.y <= m_UpPos)
		{
			m_Pos.y = m_UpPos;
			return true;
		}

		return false;
	}

	bool MenuButtonBase::MoveDown()
	{
		m_Pos.y += m_MoveSpeed;
		if (m_Pos.y >= m_DownPos)
		{
			m_Pos.y = m_DownPos;
			return true;
		}

		return false;
	}

	bool MenuButtonBase::MoveLeft()
	{
		m_Pos.x -= m_MoveSpeed;
		if (m_Pos.x <= m_LeftPos)
		{
			m_Pos.x = m_LeftPos;
			return true;
		}

		return false;
	}

	bool MenuButtonBase::MoveRight()
	{
		m_Pos.x += m_MoveSpeed;
		if (m_Pos.x >= m_RightPos)
		{
			m_Pos.x = m_RightPos;
			return true;
		}

		return false;
	}

	bool MenuButtonBase::MoveLeftCenter()
	{
		if (m_Pos.x > m_LeftCenterPos)
		{
			m_Pos.x -= m_MoveSpeed;
			if (m_Pos.x <= m_LeftCenterPos)
			{
				m_Pos.x = m_LeftCenterPos;
				return true;
			}

			return false;
		}
		else
		{
			m_Pos.x += m_MoveSpeed;
			if (m_Pos.x >= m_LeftCenterPos)
			{
				m_Pos.x = m_LeftCenterPos;
				return true;
			}

			return false;
		}

		return true;
	}

	bool MenuButtonBase::MoveRightCenter()
	{
		if (m_Pos.x > m_RightCenterPos)
		{
			m_Pos.x -= m_MoveSpeed;
			if (m_Pos.x <= m_RightCenterPos)
			{
				m_Pos.x = m_RightCenterPos;
				return true;
			}

			return false;
		}
		else
		{
			m_Pos.x += m_MoveSpeed;
			if (m_Pos.x >= m_RightCenterPos)
			{
				m_Pos.x = m_RightCenterPos;
				return true;
			}

			return false;
		}

		return true;
	}
}
