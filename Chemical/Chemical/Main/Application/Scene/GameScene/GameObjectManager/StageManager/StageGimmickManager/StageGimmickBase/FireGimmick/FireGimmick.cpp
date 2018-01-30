/**
 * @file	FireGimmick.cpp
 * @brief	炎ギミッククラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "FireGimmick.h"

#include "..\..\StageGimmickManager.h"
#include "..\..\..\..\GameDataManager\GameDataManager.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "CollisionManager\CollisionManager.h"
#include <time.h>


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	FireGimmick::FireGimmick() : 
		StageGimmickBase("Resource\\GameScene\\Texture\\Gimmick0.png", "FireGimmick"),
		m_pCollision(new FireGimmickCollision(FIRE_GIMMICK_COLLISION_ID)),
		m_Time(0)
	{
	}

	FireGimmick::~FireGimmick()
	{
		SafeDelete(m_pCollision);
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool FireGimmick::Initialize()
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

		return true;
	}
	
	void FireGimmick::Finalize()
	{
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

	void FireGimmick::Update()
	{
		D3DXVECTOR2 ScreenPos = SINGLETON_INSTANCE(GameDataManager)->GetScreenPos();
		m_pMultipleVertexUV->WriteConstantBuffer(-ScreenPos);

		// UVアニメーション.
		m_Time++;
		for (auto& UV : m_GimmickUV)
		{
			if (m_Time % 7 == 0)
			{
				if (UV.x >= 0.75f)
					UV = D3DXVECTOR2(0, 0);
				else
					UV.x += 0.25f;
			}
		}

		while (!m_pCollision->IsCollisionDataEmpty())
		{
			GimmickCollision::COLLISION_DATA Data = m_pCollision->PopCollisionData();
			if (Data.OtherId == RAIN_GIMMICK_COLLISION_ID)
			{
				auto pRectangles = m_pCollision->GetRect();
				for (unsigned int i = 0; i < pRectangles->size(); i++)
				{
					if ((*pRectangles)[i].ID == Data.Id)
					{
						pRectangles->erase(pRectangles->begin() + i);	// 当たり判定から削除.
						m_Positions.erase(m_Positions.begin() + i);
						m_GimmickUV.erase(m_GimmickUV.begin() + i);
						m_GimmickNum--;
						break;
					}
				}
			}
		}
	}

	void FireGimmick::Draw()
	{
		if (m_GimmickNum == 0) return;
		m_pMultipleVertexUV->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		m_pMultipleVertexUV->DefaultDraw(&m_Positions[0], &m_GimmickUV[0], m_GimmickNum);
	}

	void FireGimmick::AddGimmick(int _x, int _y, int _data)
	{
		float X = StageGimmickManager::m_DefaultGimmickSize.x;
		float Y = StageGimmickManager::m_DefaultGimmickSize.y;

		D3DXVECTOR2 Pos(_x * X + X / 2, _y * Y + Y / 2);

		GIMMICK_RECTANGLE Rect(
			Pos.x - X / 2,
			Pos.y - Y / 2,
			Pos.x + X / 2,
			Pos.y + Y / 2,
			m_GimmickNum);

		// 初期UV値はランダム.
		D3DXVECTOR2 UV(0, 0);
		srand(unsigned(time(NULL) + m_GimmickNum));
		UV.x = rand() % 4 * 0.25f;

		// ギミックの追加.
		m_Positions.emplace_back(Pos);
		m_GimmickUV.emplace_back(UV);
		m_pCollision->AddRect(Rect);
		m_GimmickNum++;
	}

	void FireGimmick::ClearChip()
	{
		m_pCollision->ClearRect();
		m_GimmickUV.clear();
		m_Positions.clear();
	}

	bool FireGimmick::CreateInstanceBuffer()
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

	void FireGimmick::ReleaseInstanceBuffer()
	{
		m_pMultipleVertexUV->ReleaseInstanceBufferUV();
	}
}
