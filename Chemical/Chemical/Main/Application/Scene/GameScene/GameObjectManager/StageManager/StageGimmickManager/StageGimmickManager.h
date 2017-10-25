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


namespace Game
{
	/*** ステージギミック管理クラス */
	class StageGimmickManager : public Lib::ObjectBase
	{
	public:
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

	};
}

#endif // GAME_STAGEGIMMICKMANAGER_H
