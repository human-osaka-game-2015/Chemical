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

	private:
		std::vector<Lib::ObjectBase*> m_pObjects;	//!< 管理オブジェクト.

	};
}


#endif // !GAME_STAGEMANAGER_H
