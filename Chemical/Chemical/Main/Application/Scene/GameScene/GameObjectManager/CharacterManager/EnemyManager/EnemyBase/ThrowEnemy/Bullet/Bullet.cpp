/**
* @file	WalkEnemy.cpp
* @brief	ウォークエネミークラス実装
* @author	fujioka
*/

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Bullet.h"
#include "Application\Scene\GameScene\GameDefine.h"
#include "CollisionManager\CollisionManager.h"
#include "CollisionManager\CollisionBase\EnemyCollision\EnemyCollision.h"
#include "..\..\..\..\..\GameDataManager\GameDataManager.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"

#include "TaskManager\TaskManager.h"

namespace Game
{
	
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	Bullet::Bullet(D3DXVECTOR2* _pPosotion,int* _Speed) :
		m_Frame(0),
		m_Speed(*_Speed),
		m_IsEnable(true)
	{
		m_Pos = *_pPosotion;
		m_Size = D3DXVECTOR2(100.0f, 100.0f);
	}

	Bullet::~Bullet()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool Bullet::Initialize()
	{
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->AddTask(m_pDrawTask);
		m_pDrawTask->SetPriority(GAME_DRAW_CHARACTER);

		m_pCollisionTask = new CollisionTask();
		m_pCollisionTask->SetObject(this);
		SINGLETON_INSTANCE(CollisionTaskManager)->AddTask(m_pCollisionTask);

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\GameScene\\Texture\\Explosion.png",
			&m_TextureIndex)) return false;

		if (!CreateVertex2D()) return false;
		m_pVertex->SetUV(&D3DXVECTOR2(0.0f, 0.0f), &D3DXVECTOR2(1.0f, 1.0f));
		m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));

		m_pCollision = new EnemyCollision();
		SINGLETON_INSTANCE(CollisionManager)->AddCollision(m_pCollision);
		return true;
	}

	void Bullet::Finalize()
	{
		SINGLETON_INSTANCE(CollisionManager)->RemoveCollision(m_pCollision);
		SafeDelete(m_pCollision);

		ReleaseVertex2D();

		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);
		SINGLETON_INSTANCE(CollisionTaskManager)->RemoveTask(m_pCollisionTask);
		SafeDelete(m_pCollisionTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
	}

	void Bullet::CollisionTaskUpdate()
	{
		
		if (m_pCollision->GetCollisionDiff().x != 0)
		{
			m_IsEnable = false;
		}

		if (m_pCollision->GetCollisionDiff().y != 0)
		{
			m_IsEnable = false;
		}

	}

	void Bullet::Update()
	{
		m_Pos.x += m_Speed;
		m_Frame++;

		if (m_Frame > 180)
		{
			m_IsEnable = false;
		}
		
		RectangleCollisionBase::RECTANGLE RectAngle;
		RectAngle.Left = m_Pos.x - m_Size.x / 2;
		RectAngle.Top = m_Pos.y - m_Size.y / 2;
		RectAngle.Right = m_Pos.x + m_Size.x / 2;
		RectAngle.Bottom = m_Pos.y + m_Size.y / 2;
		m_pCollision->SetRect(RectAngle);
		m_pCollision->ResetCollisionDiff();
	}

	void Bullet::Draw()
	{
		//m_pVertex->SetInverse(true);

		m_pVertex->ShaderSetup();
		m_pVertex->WriteVertexBuffer();
		D3DXVECTOR2 Pos = m_Pos;
		Pos.x -= SINGLETON_INSTANCE(GameDataManager)->GetScreenPos().x;
		m_pVertex->WriteConstantBuffer(&Pos);
		m_pVertex->Draw();
	}

	//----------------------------------------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------------------------------------

}
