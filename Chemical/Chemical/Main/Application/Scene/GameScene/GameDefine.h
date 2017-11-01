/**
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
		TITLE_DRAW_BACKGROUND = -1	//!< 背景描画プライオリティ.
	};

	/*** イベントの識別子 */
	enum EVENT_ID
	{
		PLAYER_EVENT = 0	//!< プレイヤーイベント.
	};

	/*** イベントグループ名 */
	enum EVENT_GROUP
	{
		PLAYER_EVENT_GROUP = 0	//!< プレイヤーイベントグループ.
	};

	/*** 当たり判定オブジェクトID */
	enum COLLISION_ID
	{
		EMPTY_COLLISION_ID = 0,	//!< 空オブジェクトID(エラー値).
		PLAYER_COLLISION_ID = 1,//!< プレイヤー当たり判定ID.
		ROAD_COLLISION_ID = 2,	//!< 道の当たり判定ID.
		SOIL_COLLISION_ID = 3	//!< 土の当たり判定ID.
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
