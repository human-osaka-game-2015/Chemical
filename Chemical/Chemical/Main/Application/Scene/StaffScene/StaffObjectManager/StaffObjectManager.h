/**
 * @file	StaffObjectManager.h
 * @brief	スタッフオブジェクト管理クラス定義
 * @author	morimoto
 */
#ifndef GAME_STAFFOBJECTMANAGER_H
#define GAME_STAFFOBJECTMANAGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ObjectManagerBase\ObjectManagerBase.h"


namespace Staff
{
	/*** スタッフオブジェクト管理クラス */
	class StaffObjectManager : public Lib::ObjectManagerBase
	{
	public:
		/*** コンストラクタ */
		StaffObjectManager();

		/*** デストラクタ */
		~StaffObjectManager();

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

	};
}


#endif // !GAME_STAFFOBJECTMANAGER_H
