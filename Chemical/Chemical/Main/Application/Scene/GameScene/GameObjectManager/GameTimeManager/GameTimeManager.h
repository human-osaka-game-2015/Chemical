/**
 * @file	GameTimeManager.h
 * @brief	ゲーム内時間管理クラス定義
 * @author	morimoto
 */
#ifndef GAME_TIMEMANAGER_H
#define GAME_TIMEMANAGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ObjectManagerBase\ObjectBase\ObjectBase.h"


namespace Game
{
	/*** ゲーム内時間管理クラス */
	class TimeManager : public Lib::ObjectBase
	{
	public:
		/*** コンストラクタ */
		TimeManager();

		/*** デストラクタ */
		virtual ~TimeManager();

		/**
		 * 初期化処理
		 * @return 初期化に成功したか
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

		/*** 更新処理 */
		virtual void Update();

		/*** 描画処理 */
		virtual void Draw();

	};
}


#endif // !GAME_TIMEMANAGER_H
