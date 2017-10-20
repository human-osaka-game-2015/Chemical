/**
 * @file	TitleDefine.h
 * @brief	タイトルの定義ヘッダ
 * @author	morimoto
 */

namespace Title
{
	/**
	 * 描画プライオリティ
	 */
	enum DRAW_PRIORITY
	{
		TITLE_DRAW_BACKGROUND = -1,
		TITLE_DRAW_MENU_CURSOR = 0,
		TITLE_DRAW_MENU_BUTTON = 1,
		TITLE_DRAW_BACK_LOGO = 2
	};

	/**
	 * イベントの識別子
	 */
	enum EVENT_ID
	{
		TITLE_MENU_EVENT = 0
	};

	/**
	 * イベントグループ名
	 */
	enum EVENT_GROUP
	{
		TITLE_MENU_GROUP
	};
}
