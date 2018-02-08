/**
 * @file   RainChemical.cpp
 * @brief  RainChemicalクラスの実装
 * @author kotani
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------

#include "RainChemical.h"
#include "..\..\ChemicalFactory.h"
#include "GameDefine.h"
#include "CollisionManager\CollisionManager.h"
#include "..\..\..\..\..\GameDataManager\GameDataManager.h"
#include "RainChemicalEvent\RainChemicalEvent.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "EventManager\EventManager.h"

#include <iostream>
#include <random>


namespace Game
{
	namespace
	{
		ChemicalBase* CreateRainChemical(int _textureIndex)
		{
			ChemicalBase* pChemical = new RainChemical(_textureIndex);
			pChemical->Initialize();
			return pChemical;
		}

		const bool registered = ChemicalFactory::GetInstance().
			RegisterCreateFunc(
			ChemicalFactory::Types(CHEMICAL_BLUE, CHEMICAL_YELLOW),
			CreateRainChemical);
	}


	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------

	RainChemical::RainChemical(int _textureIndex) :
		ChemicalBase(_textureIndex, CHEMICAL_RAIN),
		m_ParticleNum(1)
	{
		m_Size = D3DXVECTOR2(40,40);
	}

	RainChemical::~RainChemical()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------

	bool RainChemical::Initialize()
	{
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);

		m_pRainChemicalEvent = new RainChemicalEvent(RAIN_EVENT);

		m_pCollisionTask = new CollisionTask();
		m_pCollisionTask->SetObject(this);

		m_pCollision = new ChemicalCollision(m_ChemicalData.Type);

		m_pStartUpTask = new Lib::UpdateStartUpTask();
		m_pStartUpTask->SetObject(this);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddStartUpTask(m_pStartUpTask);

		m_Positions.resize(m_ParticleNum);
		m_Accelerations.resize(m_ParticleNum);
		m_Speeds.resize(m_ParticleNum);
		m_pMultipleVertex = new Lib::Dx11::MultipleVertex2D();

		if (!m_pMultipleVertex->Initialize(SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)))
		{
			OutputErrorLog("2D描画オブジェクトの初期化に失敗しました");
			return false;
		}

		if (!m_pMultipleVertex->CreateVertexBuffer(&m_Size, &D3DXVECTOR2(0, 0), &D3DXVECTOR2(1, 1)))
		{
			OutputErrorLog("頂点バッファの生成に失敗しました");
			return false;
		}

		D3DXMATRIX* pMat = new D3DXMATRIX[m_ParticleNum];
		for (int i = 0; i < m_ParticleNum; i++)	D3DXMatrixIdentity(&pMat[i]);
		m_pMultipleVertex->CreateInstanceBuffer(pMat, m_ParticleNum);
		SafeDeleteArray(pMat);
		m_pMultipleVertex->WriteInstanceBuffer(&m_Positions[0]);

		return true;
	}

	void RainChemical::Finalize()
	{
		if (m_pMultipleVertex != nullptr)
		{
			m_pMultipleVertex->ReleaseInstanceBuffer();
			m_pMultipleVertex->ReleaseVertexBuffer();
			m_pMultipleVertex->Finalize();
			SafeDelete(m_pMultipleVertex);
		}

		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveStartUpTask(m_pStartUpTask);
		SafeDelete(m_pStartUpTask);

		SINGLETON_INSTANCE(CollisionManager)->RemoveCollision(m_pCollision);
		SafeDelete(m_pCollision);

		SINGLETON_INSTANCE(CollisionTaskManager)->RemoveTask(m_pCollisionTask);
		SafeDelete(m_pCollisionTask);

		SafeDelete(m_pRainChemicalEvent);

		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
	}

	void RainChemical::UpdateStartUp()
	{
		if (!m_IsSprinkle) return;

		if (!m_pCollision->GetHit()) return;

		m_IsSprinkle = false;
		m_pRainChemicalEvent->SetRainPos(m_Pos);
		m_pRainChemicalEvent->SetChemicalGrade(m_ChemicalData.Grade);

		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
		SINGLETON_INSTANCE(CollisionTaskManager)->RemoveTask(m_pCollisionTask);
		SINGLETON_INSTANCE(CollisionManager)->RemoveCollision(m_pCollision);

		SINGLETON_INSTANCE(Lib::EventManager)->SendEventMessage(
			m_pRainChemicalEvent,
			TO_STRING(RAIN_EVENT_GROUP));
	}

	void RainChemical::Update()
	{
		m_Acceleration = (std::min)(m_Acceleration, 23.f);

		m_Pos.x += m_IsLeft ? -10.f : 10.f;
		m_Pos.y += (m_Acceleration += m_Gravity);

		for (int i = 0; i < m_ParticleNum; i++)
		{
			m_Positions[i].x += m_IsLeft ? -m_Speeds[i] : m_Speeds[i];
			m_Positions[i].y += (m_Accelerations[i] += m_Gravity);
		}

		RectangleCollisionBase::RECTANGLE Rectangle(
			m_Pos.x - m_Size.x / 2,
			m_Pos.y - m_Size.y / 2,
			m_Pos.x + m_Size.x / 2,
			m_Pos.y + m_Size.y / 2);
		m_pCollision->SetRect(Rectangle);
		m_pCollision->ResetCollision();
	}

	void RainChemical::Draw()
	{
		D3DXVECTOR2 ScreenPos = SINGLETON_INSTANCE(GameDataManager)->GetScreenPos();
		m_pMultipleVertex->WriteConstantBuffer(-ScreenPos);

		m_pMultipleVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pMultipleVertex->DefaultDraw(&m_Positions[0]);
	}

	void RainChemical::Sprinkle(const D3DXVECTOR2& _pos, bool _isLeft)
	{
		if (m_IsSprinkle) return;
		if (m_ChemicalData.Remain <= 0) return;

		m_ChemicalData.Remain -= 10;
		m_ChemicalData.Remain = (std::max)(0.f, m_ChemicalData.Remain);

		for (int i = 0; i < m_ParticleNum; i++)
		{
			m_Speeds[i] = 8;
			m_Positions[i] = _pos;
			m_Accelerations[i] = -8;
		}

		m_Acceleration = -7;
		m_IsLeft = _isLeft;
		m_Pos = _pos;
		m_IsSprinkle = true;

		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->AddTask(m_pDrawTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);
		SINGLETON_INSTANCE(CollisionTaskManager)->AddTask(m_pCollisionTask);
		SINGLETON_INSTANCE(CollisionManager)->AddCollision(m_pCollision);
	}
}
