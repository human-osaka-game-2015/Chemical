/**
 * @file	EnemyUI.cpp
 * @brief	エネミーUIクラス実装
 * @author	Fujioka
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EnemyUI.h"
#include "..\..\..\EnemyBase\EnemyBase.h"

#include "Application\Scene\GameScene\GameDefine.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "..\..\..\..\..\GameDataManager\GameDataManager.h"

namespace Game
{
	const int EnemyUI::m_DrawFream = 180;

	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	EnemyUI::EnemyUI(EnemyBase* _pEnemyBase):
		m_Frame(0)
	{
		m_pEnemyBase = _pEnemyBase;
		m_MaxHealth = m_pEnemyBase->GetHealth();
		m_OldHealth = m_MaxHealth;
	}

	EnemyUI::~EnemyUI()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool EnemyUI::Initialize()
	{
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->AddTask(m_pDrawTask);
		m_pDrawTask->SetPriority(GAME_DRAW_CHARACTER);

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\GameScene\\Texture\\EnemyLife.png",
			&m_TextureIndex)) return false;

		if (!CreateVertex2D()) return false;
		m_pVertex->SetUV(&D3DXVECTOR2(0.0f, 0.0f), &D3DXVECTOR2(1.0f, 1.0f));
		m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pVertex->SetVertex(&D3DXVECTOR2(1.0f, 1.0f));

		return true;
	}

	void EnemyUI::Finalize()
	{
		ReleaseVertex2D();
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
	}

	void EnemyUI::Update()
	{
		m_Size = D3DXVECTOR2(m_pEnemyBase->GetHealth()*m_pEnemyBase->GetSize().x / m_MaxHealth, 20.0f);
		m_Pos = m_pEnemyBase->GetPosition();
		m_Pos -= m_pEnemyBase->GetSize() / 2;
		m_Pos.y -= m_Size.y / 2.0f;

		if (m_OldHealth != m_pEnemyBase->GetHealth())
		{
			m_Frame = m_DrawFream;
			m_OldHealth = m_pEnemyBase->GetHealth();
		}
		m_Frame--;
		if (m_Frame<0)
		{
			m_Frame = 0;
		}
	}

	void EnemyUI::Draw()
	{
		if (!m_Frame)
		{
			return;
		}
		m_pVertex->ShaderSetup();
		m_pVertex->WriteVertexBuffer();
		D3DXVECTOR2 Pos = m_Pos;
		Pos.x -= SINGLETON_INSTANCE(GameDataManager)->GetScreenPos().x - m_pEnemyBase->GetHealth() / 2.0f*m_pEnemyBase->GetSize().x / m_MaxHealth;

		m_pVertex->WriteConstantBuffer(&Pos,&m_Size);
		m_pVertex->Draw();

	}
}
