/**
 * @file	EndButton.h
 * @brief	終了ボタンクラス定義
 * @author	morimoto
 */
#ifndef TITLE_ENDBUTTON_H
#define TITLE_ENDBUTTON_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\TitleMenuItemBase\TitleMenuButtonBase.h"
#include "..\MenuCursorEvent\MenuCursorEvent.h"


namespace Title
{
	/**
	 * 終了ボタンクラス
	 */
	class EndButton : public MenuButtonBase
	{
	public:
		/**
		 * コンストラクタ
		 */
		EndButton();

		/**
		 * デストラクタ
		 */
		virtual ~EndButton();

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
			return MenuCursorEvent::END_BUTTON_PUSH;
		}

	};
}


#endif // !TITLE_ENDBUTTON_H
