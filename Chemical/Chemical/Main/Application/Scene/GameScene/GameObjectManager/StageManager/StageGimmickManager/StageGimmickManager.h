/**
 * @file	StageGimmickManager.h
 * @brief	ステージギミック管理クラス定義
 * @author	morimoto
 */
#ifndef GAME_STAGEGIMMICKMANAGER_H
#define GAME_STAGEGIMMICKMANAGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ObjectManagerBase\ObjectBase\ObjectBase.h"
#include "StageGimmickBase\StageGimmickBase.h"
#include "CsvFile\CsvFile.h"

class GamePlayFile;

namespace Game
{
	/*** ステージギミック管理クラス */
	class StageGimmickManager : public Lib::ObjectBase
	{
	public:
		/*** ステージのギミックID */
		enum STAGE_GIMMICK
		{
			NONE_GIMMICK,
			FIRE_GIMMICK,
			MUSHROOM_GIMMICK,
			STAGE_GIMMICK_MAX
		};

		static const D3DXVECTOR2 m_DefaultGimmickSize;	//!< ギミックのデフォルトサイズ.

		/*** コンストラクタ */
		StageGimmickManager();

		/*** デストラクタ */
		virtual ~StageGimmickManager();

		/**
		 * 初期化処理
		 * @return 初期化に成功したか
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

	private:
		StageGimmickBase*	m_pGimmicks[STAGE_GIMMICK_MAX];	//!< ギミックオブジェクト.
		GamePlayFile*		m_pPlayFile;					//!< ゲームプレイファイルオブジェクト.
		CsvFile*			m_pCsvFile;						//!< CSVファイルオブジェクト.

	};
}

#endif // GAME_STAGEGIMMICKMANAGER_H
