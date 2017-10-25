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


namespace Game
{
	/*** ステージチップ管理クラス */
	class StageChipManager : public Lib::ObjectBase
	{
	public:
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

	};
}


#endif // !GAME_STAGECHIPMANAGER_H
