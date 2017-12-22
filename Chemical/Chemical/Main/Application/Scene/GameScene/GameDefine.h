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
		TITLE_DRAW_BACKGROUND = -1,	//!< 背景描画プライオリティ.
		GAME_DRAW_CHARACTER = 1,    //!< キャラクター描画プライオリティ.
		GAME_DRAW_UI = 2			//!< UI描画プライオリティ
	};

	/*** イベントの識別子 */
	enum EVENT_ID
	{
		PLAYER_EVENT = 0,			//!< プレイヤーイベント.
		ENEMY_GENERATE_EVENT = 1,	//!< エネミー生成イベント.
		BUTTON_GIMMICK_EVENT = 2,	//!< ボタンギミックイベント.
		WARP_ENTRANCE_EVENT = 3,	//!< ワープ入口イベント.
		WARP_EXIT_EVENT = 4,		//!< ワープ出口イベント.
		WARP_GIMMICK_EVENT = 5,		//!< ワープギミックイベント.
		RAIN_EVENT = 6,				//!< 雨を降らせるイベント.
		EVENT_ID_MAX				//!< イベント識別子最大数.
	};

	/*** イベントグループ名 */
	enum EVENT_GROUP
	{
		PLAYER_EVENT_GROUP = 0,			//!< プレイヤーイベントグループ.
		ENEMYGENERATOR_EVENT_GROUP = 1,	//!< エネミーイベントグループ.
		BUTTON_EVENT_GROUP = 2,			//!< ボタンイベントグループ.
		WARP_ENTRANCE_EVENT_GROUP = 3,	//!< ワープ入り口イベントグループ.
		WARP_EXIT_EVENT_GROUP = 4,		//!< ワープ出口イベントグループ.
		WARP_EVENT_GROUP = 5,			//!< ワープイベントグループ.
		RAIN_EVENT_GROUP = 6,			//!< 雨を降らせるイベント.
		EVENT_GROUP_MAX					//!< イベントグループの最大数.
	};

	/*** 当たり判定オブジェクトID */
	enum COLLISION_ID
	{
		EMPTY_COLLISION_ID,				//!< 空オブジェクトID(エラー値).
		PLAYER_COLLISION_ID,			//!< プレイヤー当たり判定ID.
		ROAD_COLLISION_ID,				//!< 道の当たり判定ID.
		SOIL_COLLISION_ID,				//!< 土の当たり判定ID.
		ROCK_COLLISION_ID,				//!< 岩場の当たり判定ID.
		LAVA_COLLISION_ID,				//!< 溶岩の当たり判定ID.
		SEA_COLLISION_ID,				//!< 水中ブロックの当たり判定ID.
		ENEMYGENERATOR_COLLISION_ID,	//!< エネミー生成ギミック当たり判定ID.
		FIRE_GIMMICK_COLLISION_ID,		//!< 火ギミック当たり判定ID.
		MUSHROOM_GIMMICK_COLLISION_ID,	//!< キノコギミック当たり判定ID.
		WOOD_GIMMICK_COLLISION_ID,		//!< 木ギミック当たり判定ID.
		RECOVERY_GIMMICK_COLLISION_ID,	//!< 回復ギミック当たり判定ID.
		BUTTON_GIMMICK_COLLISION_ID,	//!< ボタンギミック当たり判定ID.
		GATE_GIMMICK_COLLISION_ID,		//!< 門ギミック当たり判定ID.
		WARP_GIMMICK_COLLISION_ID,		//!< ワープギミック当たり判定ID.
		WATER_COLLISION_ID,				//!< 水の当たり判定ID.
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

	/*** 薬品の種類 */
	enum CHEMICAL_TYPE
	{
		CHEMICAL_BLUE,     // 蒼
		CHEMICAL_RED,      // 紅
		CHEMICAL_YELLOW,   // 黃
		CHEMICAL_EXPLOSION,// 爆発
		CHEMICAL_MOVEUP,   // 移動速度アップ
		CHEMICAL_RAIN,	   // 雨が降る
		CHEMICAL_EMPTY     // 空
	};
}


#endif // !GAME_GAMEDEFINE_H
