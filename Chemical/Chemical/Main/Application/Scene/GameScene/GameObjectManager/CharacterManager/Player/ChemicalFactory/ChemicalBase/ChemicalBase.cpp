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

	ChemicalBase::ChemicalBase(int _textureIndex, const D3DXVECTOR2& _pos, bool _isLeft) :
		m_IsLeft(_isLeft)
	{
		m_TextureIndex = _textureIndex;
		m_Pos = _pos;
	}

	ChemicalBase::~ChemicalBase()
	{
	}

	bool ChemicalBase::Initialize()
	{
		if (!CreateVertex2D()) return false;
		m_pVertex->SetUV(&D3DXVECTOR2(0.f, 0.f), &D3DXVECTOR2(1.f, 1.f));
		m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));

		m_pCollisionTask = new CollisionTask();
		m_pCollisionTask->SetObject(this);
		SINGLETON_INSTANCE(CollisionTaskManager)->AddTask(m_pCollisionTask);

		m_pCollision = new ChemicalCollision();
		SINGLETON_INSTANCE(CollisionManager)->AddCollision(m_pCollision);

		return true;
	}

	void ChemicalBase::Finalize()
	{
		SINGLETON_INSTANCE(CollisionManager)->RemoveCollision(m_pCollision);

		ReleaseVertex2D();

		SINGLETON_INSTANCE(CollisionTaskManager)->RemoveTask(m_pCollisionTask);
		SafeDelete(m_pCollisionTask);

		SafeDelete(m_pCollision);
	}

	void ChemicalBase::CollisionTaskUpdate()
	{
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
}
