/**
 * @file	StaffDefine.h
 * @brief	スタッフの定義ヘッダ
 * @author	morimoto
 */
#ifndef STAFF_STAFFDEFINE_H
#define STAFF_STAFFDEFINE_H


namespace Staff
{
	/**
	 * 描画プライオリティ
	 */
	enum DRAW_PRIORITY
	{
		STAFF_DRAW_BACKGROUND = -1
	};

	/**
	 * イベントの識別子
	 */
	enum EVENT_ID
	{
		STAFF_EVENT = 0
	};

	/**
	 * イベントグループ名
	 */
	enum EVENT_GROUP
	{
		STAFF_GROUP
	};
}


#endif // !STAFF_STAFFDEFINE_H
