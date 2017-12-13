/**
 * @file	MushroomGimmick.cpp
 * @brief	キノコギミッククラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "MushroomGimmick.h"

#include "..\..\StageGimmickManager.h"
#include "CollisionManager\CollisionManager.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "..\..\..\..\GameDataManager\GameDataManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Static Private Variables
	//----------------------------------------------------------------------
	const D3DXVECTOR2 MushroomGimmick::m_MushroomSize = D3DXVECTOR2(120, 240);


	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	MushroomGimmick::MushroomGimmick() :
		StageGimmickBase("Resource\\GameScene\\Texture\\Gimmick1.png", "MushroomGimmick"),
		m_pCollision(new MushroomGimmickCollision(MUSHROOM_GIMMICK_COLLISION_ID)),
		m_pCollision2(new MushroomGimmickCollision(MUSHROOM_GIMMICK_COLLISION_ID)),
		m_GimmickNum2(0)
	{
	}

	MushroomGimmick::~MushroomGimmick()
	{
		SafeDelete(m_pCollision2);
		SafeDelete(m_pCollision);
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool MushroomGimmick::Initialize()
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

		if (!m_pMultipleVertexUV->CreateVertexBuffer(&m_MushroomSize, &D3DXVECTOR2(0, 0), &D3DXVECTOR2(0.5f, 1)))
		{
			OutputErrorLog("頂点バッファの生成に失敗しました");
			return false;
		}

		m_pMultipleVertexUV2 = new Lib::Dx11::MultipleVertex2DUV();
		if (!m_pMultipleVertexUV2->Initialize(SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice)))
		{
			OutputErrorLog("2D描画オブジェクトの初期化に失敗しました");
			return false;
		}

		if (!m_pMultipleVertexUV2->CreateVertexBuffer(&m_MushroomSize, &D3DXVECTOR2(0.5f, 0), &D3DXVECTOR2(1, 1)))
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
		SINGLETON_INSTANCE(CollisionManager)->AddCollision(m_pCollision2);

		return true;
	}

	void MushroomGimmick::Finalize()
	{
		SINGLETON_INSTANCE(CollisionManager)->RemoveCollision(m_pCollision2);
		SINGLETON_INSTANCE(CollisionManager)->RemoveCollision(m_pCollision);
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);

		if (m_pMultipleVertexUV2 != nullptr)
		{
			m_pMultipleVertexUV2->ReleaseVertexBuffer();
			m_pMultipleVertexUV2->Finalize();
			SafeDelete(m_pMultipleVertexUV2);
		}

		if (m_pMultipleVertexUV != nullptr)
		{
			m_pMultipleVertexUV->ReleaseVertexBuffer();
			m_pMultipleVertexUV->Finalize();
			SafeDelete(m_pMultipleVertexUV);
		}

		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
	}

	void MushroomGimmick::Update()
	{
		D3DXVECTOR2 ScreenPos = SINGLETON_INSTANCE(GameDataManager)->GetScreenPos();
		m_pMultipleVertexUV->WriteConstantBuffer(-ScreenPos);
		m_pMultipleVertexUV2->WriteConstantBuffer(-ScreenPos);

		// 小さいキノコの衝突処理.
		while (!m_pCollision->IsCollisionDataEmpty())
		{
			GimmickCollision::COLLISION_DATA Data = m_pCollision->PopCollisionData();
			if (Data.OtherId == WATER_COLLISION_ID)
			{
				auto pRectangles = m_pCollision->GetRect();
				for (unsigned int i = 0; i < pRectangles->size(); i++)
				{
					if ((*pRectangles)[i].ID == Data.Id)
					{
						///@todo テストのためプレイヤーと衝突したら状態を変える.
						GIMMICK_RECTANGLE Rectangle = (*pRectangles)[i];
						Rectangle.Top -= m_MushroomSize.y / 2;
						m_pCollision2->AddRect(Rectangle);
						m_Positions2.push_back(m_Positions[i]);
						m_GimmickUV2.push_back(m_GimmickUV[i]);
						m_GimmickNum2++;

						pRectangles->erase(pRectangles->begin() + i);	// 当たり判定から削除.
						m_Positions.erase(m_Positions.begin() + i);
						m_GimmickUV.erase(m_GimmickUV.begin() + i);
						m_GimmickNum--;
						break;
					}
				}
			}
		}

		// 大きいキノコの衝突処理.
		while (!m_pCollision2->IsCollisionDataEmpty())
		{
			GimmickCollision::COLLISION_DATA Data = m_pCollision2->PopCollisionData();
		}
	}

	void MushroomGimmick::Draw()
	{
		if (m_GimmickNum != 0)
		{
			m_pMultipleVertexUV->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
			m_pMultipleVertexUV->DefaultDraw(&m_Positions[0], &m_GimmickUV[0], m_GimmickNum);
		}

		if (m_GimmickNum2 != 0)
		{
			m_pMultipleVertexUV2->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
			m_pMultipleVertexUV2->DefaultDraw(&m_Positions2[0], &m_GimmickUV2[0], m_GimmickNum2);
		}
	}

	void MushroomGimmick::AddGimmick(int _x, int _y, int _data)
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

		// キノコはギミック二つ分なので座標を調整.
		Pos.y -= StageGimmickManager::m_DefaultGimmickSize.y / 2;

		// ギミックの追加.
		m_Positions.emplace_back(Pos);
		m_GimmickUV.emplace_back(0.f, 0.f);
		m_pCollision->AddRect(Rect);
		m_GimmickNum++;
	}

	void MushroomGimmick::ClearChip()
	{
		m_pCollision->ClearRect();
		m_GimmickUV.clear();
		m_Positions.clear();
	}

	bool MushroomGimmick::CreateInstanceBuffer()
	{
		// ギミックの数が0なら生成しない.
		if (!m_GimmickNum) return true;

		D3DXMATRIX* pMat = new D3DXMATRIX[m_GimmickNum];
		D3DXVECTOR2* pUV = new D3DXVECTOR2[m_GimmickNum];
		for (int i = 0; i < m_GimmickNum; i++)	D3DXMatrixIdentity(&pMat[i]);
		for (int i = 0; i < m_GimmickNum; i++)	pUV[i] = D3DXVECTOR2(1, 1);
		m_pMultipleVertexUV->CreateInstanceBufferUV(pMat, pUV, m_GimmickNum);
		m_pMultipleVertexUV2->CreateInstanceBufferUV(pMat, pUV, m_GimmickNum);	// 最大インスタンス数は同じ.

		SafeDeleteArray(pUV);
		SafeDeleteArray(pMat);

		m_pMultipleVertexUV->WriteInstanceBuffer(&m_Positions[0], &m_GimmickUV[0]);

		return true;
	}

	void MushroomGimmick::ReleaseInstanceBuffer()
	{
		m_pMultipleVertexUV2->ReleaseInstanceBufferUV();
		m_pMultipleVertexUV->ReleaseInstanceBufferUV();
	}
}
