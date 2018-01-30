/**
 * @file	GameScene.h
 * @brief	ゲームシーンクラス定義
 * @author	morimoto
 */
#ifndef GAME_GAMESCENE_H
#define GAME_GAMESCENE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "SceneManager\SceneBase\SceneBase.h"

#include "Debugger\Debugger.h"
#include "DirectX11\Font\Dx11Font.h"
#include "GameObjectManager\GameObjectManager.h"
#include "EventManager\EventListener\EventListener.h"


namespace Game
{
	/*** ゲームシーンクラス */
	class GameScene : public Lib::SceneBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _sceneId シーンのID
		 */
		GameScene(int _sceneId);

		/*** デストラクタ */
		virtual ~GameScene();

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

		ObjectManager*		m_pObjectManager;	//!< 管理オブジェクト.
		Lib::EventListener*	m_pEventListener;
		std::function<void(Lib::EventBase*)> m_pReceiveFunc;
		int					m_MainBGMIndex;

	};
}


#endif // !GAME_GAMESCENE_H
