/**
 * @file   ChemicalBase.cpp
 * @brief  ChemicalBaseクラスの実装
 * @author kotani
 */
#include "ChemicalBase.h"
#include "..\..\..\..\GameDataManager\GameDataManager.h"
#include "Application\Scene\GameScene\CollisionManager\CollisionManager.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"

namespace Game
{
	const float ChemicalBase::m_Gravity = 0.4f;

	ChemicalBase::ChemicalBase(int _textureIndex, CHEMICAL_TYPE _chemicalType) :
		m_ChemicalType(_chemicalType),
		m_IsSprinkle(false),
		m_Remain(100)
	{
		m_TextureIndex = _textureIndex;
	}

	ChemicalBase::~ChemicalBase()
	{
	}

	bool ChemicalBase::Initialize()
	{
		if (!CreateVertex2D()) return false;
		m_pVertex->SetUV(&D3DXVECTOR2(0.f, 0.f), &D3DXVECTOR2(1.f, 1.f));
		m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);

		m_pCollisionTask = new CollisionTask();
		m_pCollisionTask->SetObject(this);

		m_pCollision = new ChemicalCollision(m_ChemicalType);

		m_pStartUpTask = new Lib::UpdateStartUpTask();
		m_pStartUpTask->SetObject(this);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddStartUpTask(m_pStartUpTask);

		return true;
	}

	void ChemicalBase::Finalize()
	{
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveStartUpTask(m_pStartUpTask);
		SafeDelete(m_pStartUpTask);

		SINGLETON_INSTANCE(CollisionManager)->RemoveCollision(m_pCollision);
		SafeDelete(m_pCollision);

		SINGLETON_INSTANCE(CollisionTaskManager)->RemoveTask(m_pCollisionTask);
		SafeDelete(m_pCollisionTask);

		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);

		ReleaseVertex2D();
	}

	void ChemicalBase::CollisionTaskUpdate()
	{
	}

	void ChemicalBase::UpdateStartUp()
	{
		if (!m_IsSprinkle) return;
		if (m_pCollision->GetHit())
		{
			m_IsSprinkle = false;

			SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
			SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
			SINGLETON_INSTANCE(CollisionTaskManager)->RemoveTask(m_pCollisionTask);
			SINGLETON_INSTANCE(CollisionManager)->RemoveCollision(m_pCollision);
		}
	}

	void ChemicalBase::Update()
	{
	}

	void ChemicalBase::Draw()
	{
		D3DXVECTOR2 Pos = m_Pos;
		Pos.x -= SINGLETON_INSTANCE(GameDataManager)->GetScreenPos().x;
		
		m_pVertex->ShaderSetup();
		m_pVertex->WriteVertexBuffer();
		m_pVertex->WriteConstantBuffer(&Pos);
		m_pVertex->Draw();
	}

	void ChemicalBase::Sprinkle(const D3DXVECTOR2& _pos, bool _isLeft)
	{
		if (m_IsSprinkle) return;
		m_Remain -= 10;

		if (m_Remain < 0)
		{
			m_Remain = 0;
		}
		else
		{
			m_IsLeft = _isLeft;
			m_Pos = _pos;
			m_Acceleration = -7;
			m_IsSprinkle = true;
			SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->AddTask(m_pDrawTask);
			SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);
			SINGLETON_INSTANCE(CollisionTaskManager)->AddTask(m_pCollisionTask);
			SINGLETON_INSTANCE(CollisionManager)->AddCollision(m_pCollision);
		}

	}
}
