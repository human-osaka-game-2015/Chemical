/**
 * @file   SelectBackGround.cpp
 * @brief  BackGroundクラスの実装
 * @author kotani
 */
#include "SelectBackGround.h"
#include "Application\Scene\SelectScene\SelectDefine.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "DirectX11\GraphicsDevice\Dx11GraphicsDevice.h"
#include "TaskManager\TaskManager.h"
#include "..\..\SelectManager\SelectManager.h"


namespace Select
{
	BackGround::BackGround()
	{
		m_Pos = D3DXVECTOR2(960, 540);
		m_Size = D3DXVECTOR2(1920, 1080);
		m_pDrawTask->SetPriority(SELECT_DRAW_BACKGROUND);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->AddTask(m_pDrawTask);
	}

	BackGround::~BackGround()
	{
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
	}

	bool BackGround::Initialize()
	{

		char FilePath[256];

		for (int i = 0; i < 8; i++)
		{
			sprintf_s(FilePath, 256, "Resource\\StageSelectScene\\Texture\\BackGround\\%d.png", i+1);

			if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
				FilePath,
				&m_TextureIndexs[i])) return false;
		}
		
		if (!CreateVertex2D()) return false;

		m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(
			m_TextureIndexs[SINGLETON_INSTANCE(SelectManager)->GetSelectStageNum() - 1]));

		return true;
	}

	void BackGround::Finalize()
	{
		ReleaseVertex2D();
		for (int i = 0; i < 8; i++)
		{
			SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndexs[i]);
		}
	}

	void BackGround::Update()
	{
	}

	void BackGround::Draw()
	{
		m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(
			m_TextureIndexs[SINGLETON_INSTANCE(SelectManager)->GetSelectStageNum() - 1]));

		m_pVertex->ShaderSetup();
		m_pVertex->WriteConstantBuffer(&m_Pos);
		m_pVertex->Draw();
	}
}

