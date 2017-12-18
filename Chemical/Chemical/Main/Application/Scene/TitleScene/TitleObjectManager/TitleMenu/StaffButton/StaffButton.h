/**
 * @file	StaffButton.h
 * @brief	スタッフボタンクラス定義
 * @author	morimoto
 */
#ifndef TITLE_STAFFBUTTON_H
#define TITLE_STAFFBUTTON_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\TitleMenuButtonBase\TitleMenuButtonBase.h"
#include "..\MenuCursorEvent\MenuCursorEvent.h"


namespace Title
{
	/*** スタッフボタンクラス */
	class StaffButton : public MenuButtonBase
	{
	public:
		/*** コンストラクタ */
		StaffButton();

		/*** デストラクタ */
		virtual ~StaffButton();

		/**
		 * 初期化処理
		 * @return 初期化に成功したか
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

		/*** オブジェクトの更新 */
		virtual void Update();

		/*** オブジェクトの描画 */
		virtual void Draw();

		/**
		 * アイテムが持つイベントIDを取得
		 * @return イベントID
		 */
		virtual MenuCursorEvent::EVENT_TYPE GetID()
		{
			return MenuCursorEvent::STAFF_BUTTON_PUSH;
		}

	};
}


#endif // !TITLE_STAFFBUTTON_H
