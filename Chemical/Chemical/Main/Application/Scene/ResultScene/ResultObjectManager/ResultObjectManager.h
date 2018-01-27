/**
 * @file	ResultObjectManager.h
 * @brief	リザルトオブジェクト管理クラス定義
 * @author	morimoto
 */
#ifndef RESULT_RESULTOBJECTMANAGER_H
#define RESULT_RESULTOBJECTMANAGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ObjectManagerBase\ObjectManagerBase.h"


namespace Result
{
	/*** リザルトオブジェクト管理クラス */
	class ResultObjectManager : public Lib::ObjectManagerBase
	{
	public:
		/*** コンストラクタ */
		ResultObjectManager();

		/*** デストラクタ */
		virtual ~ResultObjectManager();

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

	};
}


#endif // !RESULT_RESULTOBJECTMANAGER_H
