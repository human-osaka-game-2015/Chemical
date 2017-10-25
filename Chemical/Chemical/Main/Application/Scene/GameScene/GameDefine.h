﻿/**
 * @file	GameDefine.h
 * @brief	ゲームの定義ヘッダ
 * @author	morimoto
 */
#ifndef GAME_GAMEDEFINE_H
#define GAME_GAMEDEFINE_H


namespace Game
{
	/**
	 * 描画プライオリティ
	 */
	enum DRAW_PRIORITY
	{
		TITLE_DRAW_BACKGROUND = -1	//!< 背景描画プライオリティ.
	};

	/**
	 * イベントの識別子
	 */
	enum EVENT_ID
	{
		PLAYER_EVENT = 0	//!< プレイヤーイベント.
	};

	/**
	 * イベントグループ名
	 */
	enum EVENT_GROUP
	{
		PLAYER_EVENT_GROUP = 0	//!< プレイヤーイベントグループ.
	};
}


#endif // !GAME_GAMEDEFINE_H
