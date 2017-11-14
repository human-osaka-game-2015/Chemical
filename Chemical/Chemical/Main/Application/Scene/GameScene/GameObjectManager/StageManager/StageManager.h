/**
 * @file	StageManager.h
 * @brief	ステージ管理クラス定義
 * @author	morimoto
 */
#ifndef GAME_STAGEMANAGER_H
#define GAME_STAGEMANAGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ObjectManagerBase\ObjectBase\ObjectBase.h"
#include "TaskManager\TaskBase\UpdateTask\UpdateTask.h"

#include <D3DX11.h>
#include <D3DX10.h>
#include <vector>


namespace Game
{
	/*** ステージ管理クラス */
	class StageManager : public Lib::ObjectBase
	{
	public:
		/*** コンストラクタ */
		StageManager();

		/*** デストラクタ */
		virtual ~StageManager();

		/**
		 * 初期化処理
		 * @return 初期化に成功したか
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

		/*** オブジェクトの更新 */
		virtual void Update();

	private:
		/*** ステージ管理オブジェクト */
		enum STAGE_OBJECT
		{
			STAGE_BACKGROUND,
			STAGE_CHIP_MANAGER,
			STAGE_GIMMICK_MANAGER,
			STAGE_OBJECT_MAX
		};

		Lib::UpdateTask* m_pUpdateTask;

		ObjectBase* m_pObjects[STAGE_OBJECT_MAX];
		D3DXVECTOR2 m_ScreenPos;	//!< スクリーン座標.
		int m_StageLine;	//!< ステージの行数.
		int m_StageRow;		//!< ステージの列数.

	};
}


#endif // !GAME_STAGEMANAGER_H
