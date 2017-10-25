/**
 * @file	StageBackground.h
 * @brief	ステージ背景クラス定義
 * @author	morimoto
 */
#ifndef GAME_STAGEBACKGROUND_H
#define GAME_STAGEBACKGROUND_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Object2DBase\Object2DBase.h"
#include "CsvFile\CsvFile.h"


namespace Game
{
	/*** ステージ背景クラス */
	class StageBackground : public Object2DBase
	{
	public:
		/*** コンストラクタ */
		StageBackground();

		/*** デストラクタ */
		virtual ~StageBackground();

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

		/*** 更新処理 */
		virtual void Update();

		/*** 描画処理 */
		virtual void Draw();

	private:
		CsvFile*	m_pCsvFile;		//!< CSVファイルオブジェクト.

	};
}


#endif // !GAME_STAGEBACKGROUND_H
