/**
 * @file	SelectDefine.h
 * @brief	タイトルの定義ヘッダ
 * @author	kotani
 */
#ifndef SELECT_DEFINE_H
#define SELECT_DEFINE_H


namespace Select
{
	/*** 描画プライオリティ */
	enum DRAW_PRIORITY
	{
		SELECT_DRAW_BACKGROUND = -1,
		SELECT_DRAW_SELECT_BOARD = 0,
		SELECT_DRAW_STAGEUP_WINDOW = 1,
		SELECT_DRAW_ONSELECT_BOARD = 2
	};

	/*** イベントの識別子 */
	enum EVENT_ID
	{
		GAME_START_EVENT,
	};
}

#endif
