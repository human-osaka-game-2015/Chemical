/**
 * @file	CollisionManager.h
 * @brief	衝突判定管理クラス定義
 * @author	morimoto
 */
#ifndef LIB_COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <D3DX11.h>
#include <D3DX10.h>
#include <vector>

#include "..\SingletonBase\SingletonBase.h"


namespace Lib
{
	class CollisionQuad2D;

	/**
	 * 衝突判定管理クラス
	 * @todo 現状は2D矩形のみ対応
	 */
	class CollisionManager : public SingletonBase<CollisionManager>
	{
	public:
		friend SingletonBase<CollisionManager>;

		/**
		 * オブジェクト同士のあたり判定を行う
		 */
		void Run();

		/**
		 * あたり判定用オブジェクトの追加
		 * @param[in] _pCollision 追加するあたり判定オブジェクト
		 */
		void AddCollision(CollisionQuad2D* _pCollision);

		/**
		 * あたり判定オブジェクトの削除
		 * @param[in] _pCollision 削除するあたり判定オブジェクト
		 */
		void RemoveCollision(CollisionQuad2D* _pCollision);


	private:
		/**
		 * コンストラクタ
		 */
		CollisionManager();

		/**
		 * デストラクタ
		 */
		virtual ~CollisionManager();

		/**
		 * オブジェクト同士のあたり判定を行う
		 * @param[in] _pCollision1 あたり判定を行うオブジェクト
		 * @param[in] _pCollision2 あたり判定を行うオブジェクト
		 */
		void CollisionCheck(CollisionQuad2D* _pCollision1, CollisionQuad2D* _pCollision2);

		std::vector<CollisionQuad2D*> m_pQuadCollision;	//!< あたり判定を行うオブジェクトを格納するコンテナ.

	};
}


#endif // !LIB_COLLISIONMANAGER_H
