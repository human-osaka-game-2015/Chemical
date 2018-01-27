/**
 * @file	ResultDefine.h
 * @brief	リザルトの定義ヘッダ
 * @author	morimoto
 */
#ifndef RESULT_RESULTDEFINE_H
#define RESULT_RESULTDEFINE_H


namespace Result
{
	/*** 描画プライオリティ */
	enum DRAW_PRIORITY
	{
		RESULT_DRAW_BACKGROUND = 0,		//!< 背景描画プライオリティ.
		RESULT_DRAW_BACKCHARA = 1,		//!< バックキャラクター描画プライオリティ.
		RESULT_DRAW_BUTTON = 2,			//!< ボタン描画プライオリティ.
		RESULT_DRAW_FONT = 3,			//!< フォント描画プライオリティ.
		DRAW_PRIORITY_MAX
	};

	/*** イベントの識別子 */
	enum EVENT_ID
	{
		RESULT_MENU_EVENT_ID,			//!< リザルトメニューイベントID.
		EVENT_ID_MAX					//!< イベント識別子最大数.
	};

	/*** イベントグループ名 */
	enum EVENT_GROUP
	{
		RESULT_MENU_EVENT_GROUP,		//!< リザルトメニューイベントグループ.
		EVENT_GROUP_MAX					//!< イベントグループの最大数.
	};
}


#endif // !GAME_GAMEDEFINE_H
