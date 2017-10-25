/**
 * @file	GameObjectManager.cpp
 * @brief	ゲームオブジェクト管理クラス定義
 * @author	morimoto
 */
#ifndef GAME_OBJECTMANAGER_H
#define GAME_OBJECTMANAGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ObjectManagerBase\ObjectManagerBase.h"

#include <vector>


namespace Game
{
	/*** ゲームオブジェクト管理クラス */
	class ObjectManager : public Lib::ObjectManagerBase
	{
	public:
		/*** コンストラクタ */
		ObjectManager();

		/*** デストラクタ */
		virtual ~ObjectManager();

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

	};
}


#endif // !GAME_OBJECTMANAGER_H
