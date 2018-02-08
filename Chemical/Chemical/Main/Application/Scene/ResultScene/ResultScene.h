/**
 * @file	ResultScene.h
 * @brief	リザルトシーンクラス定義
 * @author	morimoto
 */
#ifndef RESULT_RESULTSCENE_H
#define RESULT_RESULTSCENE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "SceneManager\SceneBase\SceneBase.h"

#include "ResultObjectManager\ResultObjectManager.h"
#include "EventManager\EventListener\EventListener.h"


namespace Result
{
	/*** リザルトシーンクラス */
	class ResultScene : public Lib::SceneBase
	{
	public:
		/**
		 * コンストラクタ 
		 * @param[in] _sceneId シーンのID
		 */
		ResultScene(int _sceneId);

		/*** デストラクタ */
		~ResultScene();

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
		void ReceiveEvent(Lib::EventBase* _pEvent);

		ResultObjectManager* m_pObjectManager;
		Lib::EventListener*	m_pEventListener;
		std::function<void(Lib::EventBase*)> m_pReceiveFunc;
		int									m_MainSoundIndex;

	};
}


#endif // !RESULT_RESULTSCENE_H
