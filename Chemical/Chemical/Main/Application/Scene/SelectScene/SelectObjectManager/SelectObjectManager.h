/**
 * @file   SelectObjectManager.h
 * @brief  ObjectManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef STAGE_SELECT_OBJECTMANAGER_H
#define STAGE_SELECT_OBJECTMANAGER_H
#include <vector>
#include "Object2DBase\Object2DBase.h"
#include "ObjectManagerBase\ObjectManagerBase.h"

namespace Select
{
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

	private:
		/*** ステージボードの生成 */
		void CreateSelectBoard();

	};
}


#endif
