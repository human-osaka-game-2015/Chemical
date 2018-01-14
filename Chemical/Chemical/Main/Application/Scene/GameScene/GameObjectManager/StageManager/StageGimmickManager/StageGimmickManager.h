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

#include <array>

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
			WOOD_GIMMICK,
			RECOVERY_GIMMICK,
			ENEMY_GENERATOR_GIMMICK,
			BUTTON_GIMMICK,
			GATE_GIMMICK,
			WARP_ENTRANCE_GIMMICK,
			WARP_EXIT_GIMMICK,
			BELTCONVEYOR_GIMMICK,
			BELTCONVEYOR_LEFT_GIMMICK,
			BELTCONVEYOR_RIGHT_GIMMICK,
			RAINCLOUD_GIMMICK,
			GATE_LEFT_GIMMICK,
			GATE_RIGHT_GIMMICK,
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
		using GimmickArray = std::array<StageGimmickBase*, STAGE_GIMMICK_MAX>;

		GimmickArray	m_pGimmicks;	//!< ギミックオブジェクト.
		GamePlayFile*	m_pPlayFile;	//!< ゲームプレイファイルオブジェクト.
		CsvFile*		m_pCsvFile;		//!< CSVファイルオブジェクト.

	};
}

#endif // GAME_STAGEGIMMICKMANAGER_H
