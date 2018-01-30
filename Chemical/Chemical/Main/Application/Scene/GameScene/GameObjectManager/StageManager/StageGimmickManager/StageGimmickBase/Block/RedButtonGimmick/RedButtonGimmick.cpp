/**
 * @file	RedButtonGimmick.cpp
 * @brief	赤ボタンギミッククラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "RedButtonGimmick.h"

#include "..\..\..\StageGimmickManager.h"
#include "..\..\..\..\..\GameDataManager\GameDataManager.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "CollisionManager\CollisionManager.h"
#include "EventManager\EventManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	RedButtonGimmick::RedButtonGimmick() :
		StageGimmickBase("Resource\\GameScene\\Texture\\Gimmick14.png", "RedButtonGimmick"),
		m_pCollision(new ButtonGimmickCollision(BUTTON_GIMMICK_COLLISION_ID)),
		m_pEvent(new RedButtonGimmickEvent(RED_BUTTON_GIMMICK_EVENT))
	{
	}

	RedButtonGimmick::~RedButtonGimmick()
	{
		SafeDelete(m_pEvent);
		SafeDelete(m_pCollision);
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool RedButtonGimmick::Initialize()
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

		if (!m_pMultipleVertexUV->CreateVertexBuffer(&m_Size, &D3DXVECTOR2(0, 0), &D3DXVECTOR2(0.5, 1)))
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

		m_pReciveFunc = std::bind(&RedButtonGimmick::ReciveEvent, this, std::placeholders::_1);
		m_pEventListener = new Lib::EventListener(&m_pReciveFunc);

		SINGLETON_INSTANCE(Lib::EventManager)->AddEventListener(
			m_pEventListener,
			TO_STRING(BLOCK_EVENT_GROUP));

		SINGLETON_INSTANCE(Lib::EventManager)->AddEventListener(
			m_pEventListener,
			TO_STRING(BUTTON_EVENT_GROUP));

		return true;
	}

	void RedButtonGimmick::Finalize()
	{
		SINGLETON_INSTANCE(Lib::EventManager)->RemoveEventListener(
			m_pEventListener,
			TO_STRING(BUTTON_EVENT_GROUP));

		SINGLETON_INSTANCE(Lib::EventManager)->RemoveEventListener(
			m_pEventListener,
			TO_STRING(BLOCK_EVENT_GROUP));

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

	void RedButtonGimmick::Update()
	{
		D3DXVECTOR2 ScreenPos = SINGLETON_INSTANCE(GameDataManager)->GetScreenPos();
		m_pMultipleVertexUV->WriteConstantBuffer(-ScreenPos);

		while (!m_pCollision->IsCollisionDataEmpty())
		{
			GimmickCollision::COLLISION_DATA Data = m_pCollision->PopCollisionData();
			if (Data.OtherId == PLAYER_COLLISION_ID)
			{
				auto pRectangles = m_pCollision->GetRect();
				for (unsigned int i = 0; i < pRectangles->size(); i++)
				{
					if ((*pRectangles)[i].ID == Data.Id &&
						(*(m_GimmickUV.begin() + i)) != D3DXVECTOR2(0.5f, 0.0f))
					{
						SINGLETON_INSTANCE(Lib::EventManager)->SendEventMessage(
							m_pEvent,
							TO_STRING(BUTTON_EVENT_GROUP));
						(*(m_GimmickUV.begin() + i)) = D3DXVECTOR2(0.5f, 0.0f);
						break;
					}
				}
			}
		}
	}

	void RedButtonGimmick::Draw()
	{
		if (m_GimmickNum == 0) return;
		m_pMultipleVertexUV->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pMultipleVertexUV->DefaultDraw(&m_Positions[0], &m_GimmickUV[0], m_GimmickNum);
	}

	void RedButtonGimmick::AddGimmick(int _x, int _y, int _data)
	{
		float X = StageGimmickManager::m_DefaultGimmickSize.x;
		float Y = StageGimmickManager::m_DefaultGimmickSize.y;

		D3DXVECTOR2 Pos(_x * X + X / 2, _y * Y + Y / 2);

		GIMMICK_RECTANGLE Rect(
			Pos.x - (X - 100) / 2,
			Pos.y - Y / 2,
			Pos.x + (X - 100) / 2,
			Pos.y + Y / 2,
			m_GimmickNum);

		// ギミックの追加.
		m_Positions.emplace_back(Pos);
		m_GimmickUV.emplace_back(D3DXVECTOR2(0.0f, 0.0f));
		m_GimmickData.emplace_back(_data);
		m_pCollision->AddRect(Rect);
		m_GimmickNum++;
	}

	void RedButtonGimmick::ClearChip()
	{
		m_pCollision->ClearRect();
		m_GimmickData.clear();
		m_GimmickUV.clear();
		m_Positions.clear();
	}

	bool RedButtonGimmick::CreateInstanceBuffer()
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

	void RedButtonGimmick::ReleaseInstanceBuffer()
	{
		m_pMultipleVertexUV->ReleaseInstanceBufferUV();
	}


	//----------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------
	void RedButtonGimmick::ReciveEvent(Lib::EventBase* _pEvent)
	{
		if (_pEvent->GetEventID() == RED_BLOCK_GIMMICK_EVENT)
		{
		}
		else if (_pEvent->GetEventID() == BLUE_BUTTON_GIMMICK_EVENT)
		{
			for (auto itr = m_GimmickUV.begin(); itr != m_GimmickUV.end(); itr++)
			{
				(*itr) = D3DXVECTOR2(0.0f, 0.0f);
			}
		}
	}
}
