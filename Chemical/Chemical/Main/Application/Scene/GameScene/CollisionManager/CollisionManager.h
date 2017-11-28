/**
 * @file	CollisionManager.h
 * @brief	当たり判定管理クラス定義
 * @author	morimoto
 */
#ifndef GAME_COLLISIONMANAGER_H
#define GAME_COLLISIONMANAGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "SingletonBase\SingletonBase.h"

#include <list>


namespace Game
{
	class CollisionBase;

	/*** 当たり判定管理クラス */
	class CollisionManager : public Lib::SingletonBase<CollisionManager>
	{
	public:
		friend SingletonBase<CollisionManager>;

		/*** 衝突判定を行う */
		void Run();

		/**
		 * 衝突判定オブジェクトを追加する
		 * @param[in] _pCollision 追加する当たり判定オブジェクト
		 */
		void AddCollision(CollisionBase* _pCollision);

		/**
		 * 衝突判定オブジェクトを削除する
		 * @param[in] _pCollision 削除する当たり判定オブジェクト
		 */
		void RemoveCollision(CollisionBase* _pCollision);

	private:
		/*** コンストラクタ */
		CollisionManager();

		/*** デストラクタ */
		virtual ~CollisionManager();


		std::list<CollisionBase*>	m_pCollisions;	//!< 当たり判定オブジェクト管理するコンテナ.
	};
}


#endif // !GAME_COLLISIONMANAGER_H
