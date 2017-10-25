/**
 * @file	PlayerUI.h
 * @brief	プレイヤーUIクラス定義
 * @author	morimoto
 */
#ifndef GAME_PLAYERUI_H
#define GAME_PLAYERUI_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Object2DBase\Object2DBase.h"


namespace Game
{
	/*** プレイヤーUIクラス */
	class PlayerUI : public Object2DBase
	{
	public:
		/*** コンストラクタ */
		PlayerUI();

		/*** デストラクタ */
		virtual ~PlayerUI();

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


#endif // !GAME_PLAYERUI_H
