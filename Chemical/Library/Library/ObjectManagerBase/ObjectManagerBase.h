/**
 * @file	ObjectManagerBase.h
 * @brief	オブジェクト管理基底クラス定義
 * @author	morimoto
 */
#ifndef LIB_OBJECTMANAGERBASE_H
#define LIB_OBJECTMANAGERBASE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <vector>

#include "ObjectBase\ObjectBase.h"


namespace Lib
{
	/**
	 * オブジェクト管理基底クラス
	 */
	class ObjectManagerBase
	{
	public:
		/**
		 * コンストラクタ
		 */
		ObjectManagerBase();

		/**
		 * デストラクタ
		 */
		virtual ~ObjectManagerBase();

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize();

		/**
		 * 終了処理
		 */
		virtual void Finalize();

	protected:
		std::vector<ObjectBase*> m_pObjects;	//!< 管理するオブジェクトを格納するコンテナ.

	};
}


#endif // !LIB_OBJECTMANAGERBASE_H
