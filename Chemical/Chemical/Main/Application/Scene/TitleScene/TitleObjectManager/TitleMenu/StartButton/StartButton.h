/**
 * @file	StartButton.h
 * @brief	スタートボタンクラス定義
 * @author	morimoto
 */
#ifndef TITLE_STARTBUTTON_H
#define TITLE_STARTBUTTON_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\TitleMenuButtonBase\TitleMenuButtonBase.h"
#include "..\MenuCursorEvent\MenuCursorEvent.h"


namespace Title
{
	/**
	 * スタートボタンクラス
	 */
	class StartButton : public MenuButtonBase
	{
	public:
		/**
		 * コンストラクタ
		 */
		StartButton();

		/**
		 * デストラクタ
		 */
		virtual ~StartButton();

		/**
		 * 初期化処理
		 * @return 初期化に成功したか
		 */
		virtual bool Initialize();

		/**
		 * 終了処理
		 */
		virtual void Finalize();

		/**
		 * オブジェクトの更新
		 */
		virtual void Update();

		/**
		 * オブジェクトの描画
		 */
		virtual void Draw();

		/**
		 * アイテムが持つイベントIDを取得
		 * @return イベントID
		 */
		virtual MenuCursorEvent::EVENT_TYPE GetID()
		{
			return MenuCursorEvent::START_BUTTON_PUSH;
		}

	};
}


#endif // !TITLE_STARTBUTTON_H
