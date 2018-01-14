/**
 * @file	GateGimmickRight.cpp
 * @brief	門ギミック右側クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "GateGimmickRight.h"

#include "..\..\..\StageGimmickManager.h"
#include "..\..\..\..\..\GameDataManager\GameDataManager.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "CollisionManager\CollisionManager.h"
#include "EventManager\EventManager.h"
#include "..\..\ButtonGimmick\ButtonGimmickEvent\ButtonGimmickEvent.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Static Private Variables
	//----------------------------------------------------------------------
	const D3DXVECTOR2 GateGimmickRight::m_GateGimmickSize = D3DXVECTOR2(240, 320);


	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	GateGimmickRight::GateGimmickRight() :
		StageGimmickBase("Resource\\GameScene\\Texture\\Gimmick6_2.png", "GateGimmick"),
		m_pCollision(new GateGimmickCollision(GATE_GIMMICK_COLLISION_ID))
	{
		m_Size = m_GateGimmickSize;
	}

	GateGimmickRight::~GateGimmickRight()
	{
		SafeDelete(m_pCollision);
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool GateGimmickRight::Initialize()
	{
		m_pUpdateTask->SetName(m_TaskName);
		m_pDrawTask->SetName(m_TaskName);

		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->AddTask(m_pDrawTask);

		m_pMultipleVertexUV = new Lib::Dx11::MultipleVertex2DUV();
		if (!m_pMultipleVertexUV->Initialize(SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)))
		{
			OutputErrorLog("2D描画オブジェクトの初期化に失敗しました");
			return false;
		}

		if (!m_pMultipleVertexUV->CreateVertexBuffer(&m_Size, &D3DXVECTOR2(0, 0), &D3DXVECTOR2(0.25, 1)))
		{
			OutputErrorLog("頂点バッファの生成に失敗しました");
			return false;
		}

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			m_TextureName,
			&m_TextureIndex))
		{
			return false;
		}

		SINGLETON_INSTANCE(CollisionManager)->AddCollision(m_pCollision);

		m_pReciveFunc = std::bind(&GateGimmickRight::ReciveEvent, this, std::placeholders::_1);
		m_pEventListener = new Lib::EventListener(&m_pReciveFunc);

		SINGLETON_INSTANCE(Lib::EventManager)->AddEventListener(
			m_pEventListener,
			TO_STRING(BUTTON_EVENT_GROUP));

		return true;
	}

	void GateGimmickRight::Finalize()
	{
		SINGLETON_INSTANCE(Lib::EventManager)->RemoveEventListener(
			m_pEventListener,
			TO_STRING(BUTTON_EVENT_GROUP));

		SafeDelete(m_pEventListener);

		SINGLETON_INSTANCE(CollisionManager)->RemoveCollision(m_pCollision);
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);

		if (m_pMultipleVertexUV != nullptr)
		{
			m_pMultipleVertexUV->ReleaseVertexBuffer();
			m_pMultipleVertexUV->Finalize();
			SafeDelete(m_pMultipleVertexUV);
		}

		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
	}

	void GateGimmickRight::Update()
	{
		D3DXVECTOR2 ScreenPos = SINGLETON_INSTANCE(GameDataManager)->GetScreenPos();
		m_pMultipleVertexUV->WriteConstantBuffer(-ScreenPos);

		while (!m_pCollision->IsCollisionDataEmpty())
		{
			GimmickCollision::COLLISION_DATA Data = m_pCollision->PopCollisionData();
		}

		for (unsigned int i = 0; i < m_IsOpened.size(); i++)
		{
			if (m_IsOpened[i] == 1)
			{
				m_TimeSpentInOpen[i]++;
				if (m_TimeSpentInOpen[i] >= 20)
				{
					m_GimmickUV[i] = D3DXVECTOR2(0.5f, 0.0f);
				}
			}
		}
	}

	void GateGimmickRight::Draw()
	{
		if (m_GimmickNum == 0) return;
		m_pMultipleVertexUV->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pMultipleVertexUV->DefaultDraw(&m_Positions[0], &m_GimmickUV[0], m_GimmickNum);
	}

	void GateGimmickRight::AddGimmick(int _x, int _y, int _data)
	{
		float X = StageGimmickManager::m_DefaultGimmickSize.x;
		float Y = StageGimmickManager::m_DefaultGimmickSize.y;

		D3DXVECTOR2 Pos(_x * X + X, _y * Y - m_GateGimmickSize.y / 2 + Y);

		GIMMICK_RECTANGLE Rect(
			Pos.x - X / 2,
			Pos.y - Y / 2,
			Pos.x + X / 2,
			Pos.y + Y / 2,
			m_GimmickNum);

		// ギミックの追加.
		m_Positions.emplace_back(Pos);
		m_GimmickUV.emplace_back(D3DXVECTOR2(0.0f, 0.0f));
		m_GimmickData.emplace_back(_data);
		m_IsOpened.emplace_back(0);
		m_TimeSpentInOpen.emplace_back(0);
		m_pCollision->AddRect(Rect);
		m_pCollision->AddIsActive(1);
		m_GimmickNum++;
	}

	void GateGimmickRight::ClearChip()
	{
		m_pCollision->ClearIsActive();
		m_pCollision->ClearRect();
		m_TimeSpentInOpen.clear();
		m_IsOpened.clear();
		m_GimmickData.clear();
		m_GimmickUV.clear();
		m_Positions.clear();
	}

	bool GateGimmickRight::CreateInstanceBuffer()
	{
		// ギミックの数が0なら生成しない.
		if (!m_GimmickNum) return true;

		D3DXMATRIX* pMat = new D3DXMATRIX[m_GimmickNum];
		D3DXVECTOR2* pUV = new D3DXVECTOR2[m_GimmickNum];
		for (int i = 0; i < m_GimmickNum; i++)	D3DXMatrixIdentity(&pMat[i]);
		for (int i = 0; i < m_GimmickNum; i++)	pUV[i] = D3DXVECTOR2(1, 1);
		m_pMultipleVertexUV->CreateInstanceBufferUV(pMat, pUV, m_GimmickNum);

		SafeDeleteArray(pUV);
		SafeDeleteArray(pMat);

		m_pMultipleVertexUV->WriteInstanceBuffer(&m_Positions[0], &m_GimmickUV[0]);

		return true;
	}

	void GateGimmickRight::ReleaseInstanceBuffer()
	{
		m_pMultipleVertexUV->ReleaseInstanceBufferUV();
	}


	//----------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------
	void GateGimmickRight::ReciveEvent(Lib::EventBase* _pEvent)
	{
		if (_pEvent->GetEventID() == BUTTON_GIMMICK_EVENT)
		{
			ButtonGimmickEvent* pEvent = reinterpret_cast<ButtonGimmickEvent*>(_pEvent);

			for (int i = 0; i != m_GimmickData.size(); i++)
			{
				if (m_GimmickData[i] == pEvent->GetOpenGateId())
				{
					(*m_pCollision->GetIsActive())[i] = 0;
					m_IsOpened[i] = 1;
					m_TimeSpentInOpen[i] = 0;
					m_GimmickUV[i] = D3DXVECTOR2(0.25f, 0.0f);
				}
			}
		}
	}
}
