/**
 * @file	Application.cpp
 * @brief	アプリケーションクラス定義
 * @author	morimoto
 */
#ifndef APPLICATION_H
#define APPLICATION_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Window\Window.h"
#include "SceneManager\SceneManager.h"

namespace Title
{
	class TitleScene;
}

namespace Game
{
	class GameScene;
}


/*** アプリケーションクラス */
class Application
{
public:
	/*** シーンのID列挙子 */
	enum SCENE_ID
	{
		TITLE_SCENE_ID,	//!< タイトルシーンID.
		GAME_SCENE_ID,	//!< ゲームシーンID.
		END_SCENE_ID	//!< 終了ID.
	};

	/*** コンストラク */
	Application();

	/*** デストラクタ */
	~Application();

	/**
	 * 初期化処理
	 * @return 初期化に成功したらtrue 失敗したらfalse
	 */
	bool Initialize();

	/*** 終了処理 */
	void Finalize();

	/*** アプリケーションの実行 */
	void Run();

private:
	static const int m_WindowWidth;		//!< ウィンドウの幅.
	static const int m_WindowHeight;	//!< ウィンドウの高さ.
	static const DWORD m_WindowStyle;	//!< ウィンドウのスタイル.

	/**
	 * メインウィンドウの生成
	 * @return 生成に成功したらtrue 失敗したらfalse
	 */
	bool CreateMainWindow();

	/**
	 * グラフィックスデバイスの生成
	 * @return 生成に成功したらtrue 失敗したらfalse
	 */
	bool CreateGraphicsDevice();

	/**
	 * 入力デバイスの生成
	 * @return 生成に成功したらtrue 失敗したらfalse
	 */
	bool CreateInputDevice();

	/**
	 * シーン管理オブジェクトの生成
	 * @return 生成に成功したらtrue 失敗したらfalse
	 */
	bool CreateSceneManager();

	/*** メインウィンドウの破棄 */
	void ReleaseMainWindow();

	/*** グラフィックデバイスの破棄 */
	void ReleaseGraphicsDevice();

	/*** 入力デバイスの破棄 */
	void ReleaseInputDevice();

	/*** シーン管理オブジェクトの破棄 */
	void ReleaseSceneManager();


	Lib::Window*		m_pMainWindow;		//!< メインウィンドウ.
	Lib::SceneManager*	m_pSceneManager;	//!< シーン管理オブジェクト.

	Title::TitleScene*	m_pTitleScene;		//!< タイトルシーンオブジェクト.
	Game::GameScene*	m_pGameScene;		//!< シーンオブジェクト.

};


#endif // !APPLICATION_H
