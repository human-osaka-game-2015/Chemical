/**
 * @file	Enemy.h
 * @brief	エネミークラス定義
 * @author	morimoto
 */
#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Object2DBase\Object2DBase.h"


namespace Game
{
	/*** エネミークラス */
	class Enemy : public Object2DBase
	{
	public:
		/*** コンストラクタ */
		Enemy();

		/*** デストラクタ */
		virtual ~Enemy();

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

		/*** 更新処理 */
		virtual void Update();

		/*** 描画処理 */
		virtual void Draw();

	};
}


#endif // !GAME_ENEMY_H
