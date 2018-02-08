/**
 * @file	TitleScene.h
 * @brief	タイトルシーンクラス定義
 * @author	morimoto
 */
#ifndef TITLE_TITLESCENE_H
#define TITLE_TITLESCENE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "SceneManager\SceneBase\SceneBase.h"

#include "ObjectManagerBase\ObjectManagerBase.h"
#include "EventManager\EventBase\EventBase.h"
#include "EventManager\EventListener\EventListener.h"
#include <functional>


namespace Title
{
	/*** タイトルシーンクラス */
	class TitleScene : public Lib::SceneBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _sceneId シーンのID
		 */
		TitleScene(int _sceneId);

		/*** デストラクタ */
		virtual ~TitleScene();

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
		int										m_MainSoundIndex;

	};
}


#endif // !TITLE_TITLESCENE_H
