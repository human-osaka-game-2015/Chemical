/**
 * @file	OptionButton.h
 * @brief	オプションボタンクラス定義
 * @author	morimoto
 */
#ifndef TITLE_OPTIONBUTTON_H
#define TITLE_OPTIONBUTTON_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\TitleMenuItemBase\TitleMenuButtonBase.h"
#include "..\MenuCursorEvent\MenuCursorEvent.h"


namespace Title
{
	/**
	 * オプションボタンクラス
	 */
	class OptionButton : public MenuButtonBase
	{
	public:
		/**
		 * コンストラクタ
		 */
		OptionButton();

		/**
		 * デストラクタ
		 */
		virtual ~OptionButton();

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
			return MenuCursorEvent::OPTION_BUTTON_PUSH;
		}

	};
}


#endif // !TITLE_OPTIONBUTTON_H
