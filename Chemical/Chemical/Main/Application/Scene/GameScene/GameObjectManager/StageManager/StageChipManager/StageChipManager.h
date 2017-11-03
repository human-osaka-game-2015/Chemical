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

class GamePlayFile;
class CsvFile;

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
			SOIL_BOTTOM_LEFT_CHIP,	//!< 土の下部左端チップ.
			SOIL_BOTTOM_RIGHT_CHIP,	//!< 土の下部右端チップ.
			SOIL_TOP_CHIP,			//!< 土の上部チップ.
			SOIL_TOP_LEFT_CHIP,		//!< 土の上部左端チップ.
			SOIL_TOP_RIGHT_CHIP,	//!< 土の上部右端チップ.
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

	private:
		StageChipBase*	m_pChips[STAGE_CHIP_MAX];	//!< チップオブジェクト.
		GamePlayFile*	m_pPlayFile;				//!< ゲームプレイファイルオブジェクト.
		CsvFile*		m_pCsvFile;					//!< CSVファイルオブジェクト.

	};
}


#endif // !GAME_STAGECHIPMANAGER_H
