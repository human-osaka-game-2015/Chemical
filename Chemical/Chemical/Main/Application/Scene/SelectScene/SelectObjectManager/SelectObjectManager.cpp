/**
 * @file   SelectObjectManager.cpp
 * @brief  SelectObjectManagerクラスの実装
 * @author kotani
 */
#include "SelectObjectManager.h"
#include "SelectBackGround\SelectBackGround.h"
#include "SelectBoard\SelectBoard.h"
#include "Define\Define.h"

namespace Select
{
	ObjectManager::ObjectManager()
	{
	}

	ObjectManager::~ObjectManager()
	{
	}


	//----------------------------------------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------------------------------------

	bool ObjectManager::Initialize()
	{
		m_pObjects.push_back(new BackGround());
		CreateSelectBoard();

		for (auto itr : m_pObjects)
		{
			if (!itr->Initialize())
			{
				Finalize();
				return false;
			}
		}

		return true;
	}

	void ObjectManager::Finalize()
	{
		for (auto itr : m_pObjects)
		{
			itr->Finalize();
			SafeDelete(itr);
		}
	}

	//----------------------------------------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------------------------------------

	void ObjectManager::CreateSelectBoard()
	{
		m_pObjects.push_back(new SelectBoard(&D3DXVECTOR2(332.f, 360.f), 1));

		m_pObjects.push_back(new SelectBoard(&D3DXVECTOR2(750.f, 240.f), 2));

		m_pObjects.push_back(new SelectBoard(&D3DXVECTOR2(1170.f - 0.5f, 240.f), 3));

		m_pObjects.push_back(new SelectBoard(&D3DXVECTOR2(1590.f - 0.5f, 360.f), 4));

		m_pObjects.push_back(new SelectBoard(&D3DXVECTOR2(332.f, 722.f), 5));

		m_pObjects.push_back(new SelectBoard(&D3DXVECTOR2(750.f, 842.f), 6));

		m_pObjects.push_back(new SelectBoard(&D3DXVECTOR2(1170.f - 0.5f, 842.f), 7));

		m_pObjects.push_back(new SelectBoard(&D3DXVECTOR2(1590.f - 0.5f, 722.f), 8));
	}
}
