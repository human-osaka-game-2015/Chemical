/**
 * @file	SceneManager.h
 * @brief	シーン管理クラス定義
 * @author	morimoto
 */
#ifndef LIB_SCENEMANAGER_H
#define LIB_SCENEMANAGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <vector>


namespace Lib
{
	class SceneBase;

	/**
	 * シーン管理クラス
	 */
	class SceneManager
	{
	public:
		/**
		 * コンストラクタ
		 */
		SceneManager();

		/**
		 * デストラクタ
		 */
		~SceneManager();

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		bool Initialize();

		/**
		 * 終了処理
		 */
		void Finalize();

		/**
		 * シーンを更新する
		 * @return シーン動作が終了したらtrue そうでなければfalse
		 */
		bool Update();

		/**
		 * シーンの追加
		 * @param[in] _pScene 追加するシーンオブジェクト
		 * @return シーンの追加に成功したらtrue 失敗したらfalse
		 */
		bool AddScene(SceneBase* _pScene);

		/**
		 * シーンの削除
		 * @param[in] _pScene 削除するシーンオブジェクト
		 */
		void DeleteScene(SceneBase* _pScene);

		/**
		 * エントリシーンを設定する
		 * @param[in] _pScene エントリシーンオブジェクト
		 */
		void SetEntryScene(SceneBase* _pScene);

	private:
		static const int		m_EmptySceneID;	//!< 空シーンのID.

		std::vector<SceneBase*>	m_pSceneData;	//!< シーンを格納しているコンテナ.
		SceneBase*				m_pCurrentScene;//!< 現在のシーン.

	};
}


#endif // !LIB_SCENEMANAGER_H
