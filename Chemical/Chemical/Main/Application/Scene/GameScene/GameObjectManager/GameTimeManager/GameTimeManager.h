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

#include "TaskManager\TaskBase\UpdateTask\UpdateTask.h"
#include "TaskManager\TaskBase\DrawTask\DrawTask.h"


namespace Game
{
	class TimeUI;

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

	private:
		static const int m_FrameMax;
		static const int m_SecondsMax;
		static const int m_MinuteMax;

		/*** 時間の更新処理 */
		void TimeUpdate();

		Lib::UpdateTask*	m_pUpdateTask;	//!< 更新タスクオブジェクト.
		Lib::Draw2DTask*	m_pDrawTask;	//!< 描画タスクオブジェクト.
		TimeUI*				m_pTimeUI;		//!< 時間UI.
		int					m_Frame;		//!< 経過時間(フレーム).
		int					m_Seconds;		//!< 経過時間(秒).
		int					m_Minute;		//!< 経過時間(分).

	};
}


#endif // !GAME_TIMEMANAGER_H
