/**
 * @file	StaffScene.h
 * @brief	スタッフシーンクラス定義
 * @author	morimoto
 */
#ifndef GAME_STAFFSCENE_H
#define GAME_STAFFSCENE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "SceneManager\SceneBase\SceneBase.h"
#include "ObjectManagerBase\ObjectManagerBase.h"
#include "EventManager\EventListener\EventListener.h"
#include <functional>


namespace Staff
{
	/*** スタッフシーンクラス */
	class StaffScene : public Lib::SceneBase
	{
	public:
		/**
		 * コンストラクタ 
		 * @param[in] _sceneID シーンID
		 */
		StaffScene(int _sceneID);

		/*** デストラクタ */
		virtual ~StaffScene();

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

		/*** シーンの更新 */
		virtual void Update();

	private:
		/**
		 * イベント受信関数
		 * @param[in] _pEvent 受信したイベント
		 */
		void ReciveEvent(Lib::EventBase* _pEvent);

		Lib::ObjectManagerBase*					m_pObjectManager;
		std::function<void(Lib::EventBase*)>	m_pReciveFunc;
		Lib::EventListener*						m_pEventListener;

	};
}


#endif // !GAME_STAFFSCENE_H
