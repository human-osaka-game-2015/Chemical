/**
 * @file   SelectBoard.cpp
 * @brief  SelectBoardクラスの実装
 * @author kotani
 */
#include "SelectBoard.h"
#include "Application\Scene\SelectScene\SelectDefine.h"
#include "..\..\SelectManager\SelectManager.h"
#include "SelectStageUpWindow\SelectStageUpWindow.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "DirectX11\GraphicsDevice\Dx11GraphicsDevice.h"
#include "TaskManager\TaskManager.h"
#include "Math\Math.h"


namespace Select
{
	SelectBoard::SelectBoard(D3DXVECTOR2* _defaultPos, int _stageNum) :
		m_DefaultPos(*_defaultPos),
		m_StageNum(_stageNum),
		m_SpinSpeed(10.f),
		m_MoveSpeed(6.f),
		m_IsReverse(false),
		m_OnSelect(false),
		m_IsSelectControl(false),
		m_Scale(D3DXVECTOR2(1.f,1.f)),
		m_SpinCount(1),
		m_Alpha(1.f),
		m_MoveDistance(0.f)
	{
		m_Size = D3DXVECTOR2(200, 160);
		m_Pos = m_DefaultPos;

		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->AddTask(m_pDrawTask);
		SINGLETON_INSTANCE(SelectManager)->AddSelectBoard(this);

		m_TargetDistance = sqrt(pow(960.f - m_DefaultPos.x, 2) + pow(540.f - m_DefaultPos.y, 2));
	}
	
	SelectBoard::~SelectBoard()
	{
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
	}


	//----------------------------------------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------------------------------------

	bool SelectBoard::Initialize()
	{
		auto LoadTexture = [this](LPCTSTR _pTexturePath, int* _pIndex)
		{
			if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
				_pTexturePath,
				_pIndex))
			{
				return false;
			}
			return true;
		};

		if (!LoadTexture(
			"Resource\\StageSelectScene\\Texture\\StageBoard.png",
			&m_TextureIndex)) return false;
		
		if (!LoadTexture(
			"Resource\\StageSelectScene\\Texture\\StageBoard2.png",
			&m_BackTextureIndex)) return false;

		if (!LoadTexture(
			"Resource\\StageSelectScene\\Texture\\StageBoard2.png",
			&m_SelectFrameTextureIndex)) return false;

		if (!CreateVertex2D()) return false;
		m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		
		m_VertexPos[0] = D3DXVECTOR2(-m_Size.x / 2, -m_Size.y / 2);
		m_VertexPos[1] = D3DXVECTOR2(m_Size.x / 2, -m_Size.y / 2);
		m_VertexPos[2] = D3DXVECTOR2(-m_Size.x / 2, m_Size.y / 2);
		m_VertexPos[3] = D3DXVECTOR2(m_Size.x / 2, m_Size.y / 2);
		m_pVertex->SetVertexPos(m_VertexPos);

		m_pStageUpWindow = new StageUpWindow(m_StageNum);
		if (!m_pStageUpWindow->Initialize()) return false;
		m_pStageUpWindow->SetEneble(false);

		m_pSelectFrameVertex = new Lib::Dx11::Vertex2D();
		if (!m_pSelectFrameVertex->Initialize(SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice))) return false;

		m_pSelectFrameVertex->CreateVertexBuffer(&D3DXVECTOR2(220, 180));
		m_pSelectFrameVertex->WriteVertexBuffer();
		m_pSelectFrameVertex->WriteConstantBuffer(&D3DXVECTOR2(640, 360));
		m_pSelectFrameVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_SelectFrameTextureIndex));
		m_pSelectFrameVertex->ShaderSetup();
		m_pSelectFrameVertex->SetVertex(&D3DXVECTOR2(220,180));
		
		return true;
	}

	void SelectBoard::Finalize()
	{
		m_pSelectFrameVertex->ReleaseVertexBuffer();
		m_pSelectFrameVertex->Finalize();
		SafeDelete(m_pSelectFrameVertex);

		m_pStageUpWindow->Finalize();
		SafeDelete(m_pStageUpWindow);
		ReleaseVertex2D();
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_SelectFrameTextureIndex);
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_BackTextureIndex);
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex);
	}

	void SelectBoard::Update()
	{
		auto GetAngle = [](const D3DXVECTOR2& _pos1, const D3DXVECTOR2& _pos2)
		{
			return atan2(_pos2.y - _pos1.y, _pos2.x - _pos1.x);
		};

		auto GetAngleMovePos = [](float _movement, float _angle)
		{
			D3DXVECTOR2 returnVar = { 0.f, 0.f };
			returnVar.x = _movement * cos(_angle);
			returnVar.y = _movement * sin(_angle);
			return returnVar;
		};

		if (m_IsSelectControl)
		{
			if (m_TargetDistance > m_MoveDistance && !m_pStageUpWindow->GetEneble())
			{
				SpinControl();
				m_MoveDistance += m_MoveSpeed;
				m_Scale += D3DXVECTOR2(0.03f, 0.03f);
				m_Pos += GetAngleMovePos(m_MoveSpeed, GetAngle(m_Pos, D3DXVECTOR2(960, 540)));
				m_Alpha -= 0.01f;
			}
			else
			{
				m_MoveDistance = 0.f;
				m_pDrawTask->SetPriority(SELECT_DRAW_SELECT_BOARD);
				m_Size = D3DXVECTOR2(200, 160);
				m_Scale = D3DXVECTOR2(1, 1);
				m_Pos = m_DefaultPos;
				m_pStageUpWindow->SetEneble(true);
				m_SpinCount = 1;
				m_IsReverse = false;
				m_IsSelectControl = false;
				m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
				m_Alpha = 1.f;
				m_VertexPos[0].x = -m_Size.x / 2;
				m_VertexPos[1].x = m_Size.x / 2;
				m_VertexPos[2].x = -m_Size.x / 2;
				m_VertexPos[3].x = m_Size.x / 2;
				m_pVertex->SetVertexPos(m_VertexPos);
			}
		}
	}

	void SelectBoard::Draw()
	{
		if (m_OnSelect)
		{
			m_pSelectFrameVertex->ShaderSetup();
			m_pSelectFrameVertex->WriteVertexBuffer();
			m_pSelectFrameVertex->WriteConstantBuffer(&m_Pos);
			m_pSelectFrameVertex->Draw();
		}
		m_pVertex->SetColor(&D3DXCOLOR(1,1,1,m_Alpha));
		m_pVertex->ShaderSetup();
		m_pVertex->WriteVertexBuffer();
		m_pVertex->WriteConstantBuffer(&m_Pos, &m_Scale);
		m_pVertex->Draw();
		m_OnSelect = false;
	}

	void SelectBoard::Select()
	{
		m_IsSelectControl = true;
		m_pDrawTask->SetPriority(SELECT_DRAW_ONSELECT_BOARD);
	}


	//----------------------------------------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------------------------------------

	void SelectBoard::SpinControl()
	{
		float old_x = m_VertexPos[0].x;
		if (m_IsReverse)
		{
			m_VertexPos[0].x -= m_SpinSpeed;
			m_VertexPos[1].x += m_SpinSpeed;
			m_VertexPos[2].x -= m_SpinSpeed;
			m_VertexPos[3].x += m_SpinSpeed;
		}
		else
		{
			m_VertexPos[0].x += m_SpinSpeed;
			m_VertexPos[1].x -= m_SpinSpeed;
			m_VertexPos[2].x += m_SpinSpeed;
			m_VertexPos[3].x -= m_SpinSpeed;
		}

		if (m_SpinCount == 0)
		{
			m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_BackTextureIndex));
			m_pVertex->SetUV(&D3DXVECTOR2(1.f, 0.f), &D3DXVECTOR2(0.f, 1.f));
		}
		else if (m_SpinCount == 1)
		{
			m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex));
		}
		else if (m_SpinCount == 2)
		{
			m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_BackTextureIndex));
		}

		if (m_VertexPos[0].x >= 0.f && old_x < 0.f ||
			m_VertexPos[0].x <= 0.f && old_x > 0.f)
		{
			if (m_SpinCount == 2)
			{
				m_SpinCount = 0;
			}
			m_SpinCount++;
		}

		if (abs(m_VertexPos[0].x - m_VertexPos[1].x) >= 200.f)
		{
			if (m_IsReverse)
			{
				m_VertexPos[0].x = -m_Size.x / 2;
				m_VertexPos[1].x = m_Size.x / 2;
				m_VertexPos[2].x = -m_Size.x / 2;
				m_VertexPos[3].x = m_Size.x / 2;
			}
			else
			{
				m_VertexPos[0].x = m_Size.x / 2;
				m_VertexPos[1].x = -m_Size.x / 2;
				m_VertexPos[2].x = m_Size.x / 2;
				m_VertexPos[3].x = -m_Size.x / 2;
			}
			m_IsReverse = !m_IsReverse;
		}

		m_pVertex->SetVertexPos(m_VertexPos);
	}
}
