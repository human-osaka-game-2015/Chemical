/**
 * @file	StageGimmickBase.cpp
 * @brief	ステージギミック基底クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "StageGimmickBase.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "..\StageGimmickManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	StageGimmickBase::StageGimmickBase(int _id, LPCTSTR _textureName, LPCTSTR _taskName) :
		m_TextureName(_textureName),
		m_TaskName(_taskName),
		m_GimmickNum(0)
	{
	}

	StageGimmickBase::~StageGimmickBase()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool StageGimmickBase::Initialize()
	{
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->AddTask(m_pDrawTask);

		if (!CreateVertex2D()) return false;

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			m_TextureName,
			&m_TextureIndex))
		{
			return false;
		}

		return true;
	}

	void StageGimmickBase::Finalize()
	{
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);

		ReleaseVertex2D();

		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
	}

	void StageGimmickBase::Update()
	{
	}

	void StageGimmickBase::Draw()
	{
	}

	void StageGimmickBase::AddChip(int _x, int _y)
	{
		float X = StageGimmickManager::m_DefaultGimmickSize.x;
		float Y = StageGimmickManager::m_DefaultGimmickSize.y;

		D3DXVECTOR2 Pos(_x * X + X / 2, _y * Y + Y / 2);

		m_GimmickNum++;	// ギミックの個数をカウント.
		m_Positions.emplace_back(Pos);
	}

	void StageGimmickBase::ClearChip()
	{
		m_Positions.clear();
	}

	bool StageGimmickBase::CreateInstanceBuffer()
	{
		// ギミックの数が0なら生成しない.
		if (!m_GimmickNum) return true;

		D3DXMATRIX* pMat = new D3DXMATRIX[m_GimmickNum];
		for (int i = 0; i < m_GimmickNum; i++)	D3DXMatrixIdentity(&pMat[i]);
		m_pMultipleVertex->CreateInstanceBuffer(pMat, m_GimmickNum);

		SafeDeleteArray(pMat);

		m_pMultipleVertex->WriteInstanceBuffer(&m_Positions[0]);

		return true;
	}

	bool StageGimmickBase::CreateCollision()
	{
		return true;
	}

	void StageGimmickBase::ReleaseInstanceBuffer()
	{
		m_pMultipleVertex->ReleaseInstanceBuffer();
	}

	void StageGimmickBase::ReleaseCollision()
	{
	}
}

