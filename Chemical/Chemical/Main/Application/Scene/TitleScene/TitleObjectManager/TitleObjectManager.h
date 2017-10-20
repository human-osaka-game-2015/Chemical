/**
 * @file	TitleObjectManager.h
 * @brief	タイトルオブジェクトクラス定義
 * @author	morimoto
 */
#ifndef TITLE_OBJECTMANAGER_H
#define TITLE_OBJECTMANAGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ObjectManagerBase\ObjectManagerBase.h"


namespace Title
{
	/**
	 * タイトルオブジェクトクラス
	 */
	class ObjectManager : public Lib::ObjectManagerBase
	{
	public:
		/**
		 * コンストラクタ
		 */
		ObjectManager();

		/**
		 * デストラクタ
		 */
		virtual ~ObjectManager();

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize();

		/**
		 * 終了処理
		 */
		virtual void Finalize();

	};
}


#endif // TITLE_OBJECTMANAGER_H
