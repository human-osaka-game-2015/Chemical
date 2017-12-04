﻿/**
 * @file	GameDefine.h
 * @brief	ゲームの定義ヘッダ
 * @author	morimoto
 */
#ifndef GAME_GAMEDEFINE_H
#define GAME_GAMEDEFINE_H


namespace Game
{
	/*** 描画プライオリティ */
	enum DRAW_PRIORITY
	{
		TITLE_DRAW_BACKGROUND = -1,	//!< 背景描画プライオリティ.
		GAME_DRAW_CHARACTER = 1     //!< キャラクター描画プライオリティ.
	};

	/*** イベントの識別子 */
	enum EVENT_ID
	{
		PLAYER_EVENT = 0,			//!< プレイヤーイベント.
		ENEMY_GENERATE_EVENT = 1,	//!< エネミー生成イベント.
		BUTTON_GIMMICK_EVENT = 2,	//!< ボタンギミックイベント.
		EVENT_ID_MAX				//!< イベント識別子最大数.
	};

	/*** イベントグループ名 */
	enum EVENT_GROUP
	{
		PLAYER_EVENT_GROUP = 0,		//!< プレイヤーイベントグループ.
		GIMMICK_EVENT_GROUP = 1,	//!< エネミーイベントグループ.
		EVENT_GROUP_MAX				//!< イベントグループの最大数.
	};

	/*** 当たり判定オブジェクトID */
	enum COLLISION_ID
	{
		EMPTY_COLLISION_ID,				//!< 空オブジェクトID(エラー値).
		PLAYER_COLLISION_ID,			//!< プレイヤー当たり判定ID.
		ROAD_COLLISION_ID,				//!< 道の当たり判定ID.
		SOIL_COLLISION_ID,				//!< 土の当たり判定ID.
		ENEMYGENERATOR_COLLISION_ID,	//!< エネミー生成ギミック当たり判定ID.
		FIRE_GIMMICK_COLLISION_ID,		//!< 火ギミック当たり判定ID.
		MUSHROOM_GIMMICK_COLLISION_ID,	//!< キノコギミック当たり判定ID.
		WOOD_GIMMICK_COLLISION_ID,		//!< 木ギミック当たり判定ID.
		RECOVERY_GIMMICK_COLLISION_ID,	//!< 回復ギミック当たり判定ID.
		BUTTON_GIMMICK_COLLISION_ID,	//!< ボタンギミック当たり判定ID.
		COLLISION_ID_MAX				//!< 当たり判定ID最大値.
	};

	/*** ステージナンバー */
	enum STAGE_NUMBER
	{
		STAGE_ONE,
		STAGE_TWO,
		STAGE_THREE,
		STAGE_FOUR,
		STAGE_FIVE,
		STAGE_SIX,
		STAGE_SEVEN,
		STAGE_EIGHT,
		STAGE_MAX
	};
}


#endif // !GAME_GAMEDEFINE_H
