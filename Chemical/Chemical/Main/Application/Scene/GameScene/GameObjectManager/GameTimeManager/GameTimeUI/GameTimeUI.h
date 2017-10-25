/**
 * @file	GameTimeUI.h
 * @brief	ゲームタイムUIクラス定義
 * @author	morimoto
 */
#ifndef GAME_TIMEUI_H
#define GAME_TIMEUI_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Object2DBase\Object2DBase.h"


namespace Game
{
	/*** ゲームタイムUIクラス */
	class TimeUI : public Object2DBase
	{
	public:
		/*** コンストラクタ */
		TimeUI();

		/*** デストラクタ */
		virtual ~TimeUI();

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

#endif // !GAME_TIMEUI_H
