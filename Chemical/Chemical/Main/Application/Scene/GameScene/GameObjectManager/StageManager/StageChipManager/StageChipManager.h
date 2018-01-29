/**
 * @file	StageChipManager.h
 * @brief	ステージチップ管理クラス定義
 * @author	morimoto
 */
#ifndef GAME_STAGECHIPMANAGER_H
#define GAME_STAGECHIPMANAGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ObjectManagerBase\ObjectBase\ObjectBase.h"
#include "StageChipBase\StageChipBase.h"
#include "CsvFile\CsvFile.h"

class GamePlayFile;

namespace Game
{
	/*** ステージチップ管理クラス */
	class StageChipManager : public Lib::ObjectBase
	{
	public:
		/*** ステージのチップID */
		enum STAGE_CHIP
		{
			NONE_CHIP,				//!< 空チップ.
			SOIL_CHIP,				//!< 土チップ.
			SOIL_BOTTOM_CHIP,		//!< 土の下部チップ.
			SOIL_TOP_CHIP,			//!< 土の上部チップ.
			ROCK_CHIP,				//!< 岩場チップ.
			ROCK_BOTTOM_CHIP,		//!< 岩場の下部チップ.
			ROCK_TOP_CHIP,			//!< 岩場の上部チップ.
			LAVA_CHIP,				//!< 溶岩チップ.
			LAVA_BOTTOM_CHIP,		//!< 溶岩の下部チップ.
			LAVA_TOP_CHIP,			//!< 溶岩の上部チップ.
			SEA_CHIP,				//!< 水中ブロックチップ.
			SEA_BOTTOM_CHIP,		//!< 水中ブロックの下部チップ.
			SEA_TOP_CHIP,			//!< 水中ブロックの上部チップ.
			WALL_CHIP,				//!< 塔壁チップ.
			WALL_BOTTOM_CHIP,		//!< 塔壁の下部チップ.
			WALL_TOP_CHIP,			//!< 塔壁の上部チップ.
			CAVE_CHIP,				//!< 洞窟壁チップ.
			CAVE_BOTTOM_CHIP,		//!< 洞窟壁の下部チップ.
			CAVE_TOP_CHIP,			//!< 洞窟壁の上部チップ.
			STONE_CHIP,
			STONE_BOTTOM_CHIP,
			STONE_TOP_CHIP,
			ELECTRON_CHIP,
			ELECTRON_BOTTOM_CHIP,
			ELECTRON_TOP_CHIP,
			STAGE_CHIP_MAX			//!< ステージチップ最大値.
		};

		static const D3DXVECTOR2 m_DefaultChipSize;	//!< チップのデフォルトサイズ.

		/*** コンストラクタ */
		StageChipManager();

		/*** デストラクタ */
		virtual ~StageChipManager();

		/**
		 * 初期化処理
		 * @return 初期化に成功したか
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

		/**
		 * CSVの行数の取得
		 * @return CSVの行数
		 */
		int GetLineNum(){ return m_pCsvFile->GetLineNum(); }

		/**
		 * CSVの列数の取得
		 * @return CSVの列数
		 */
		int GetRowNum(){ return m_pCsvFile->GetRowNum(); }

	private:
		StageChipBase*	m_pChips[STAGE_CHIP_MAX];	//!< チップオブジェクト.
		GamePlayFile*	m_pPlayFile;				//!< ゲームプレイファイルオブジェクト.
		CsvFile*		m_pCsvFile;					//!< CSVファイルオブジェクト.

	};
}


#endif // !GAME_STAGECHIPMANAGER_H
