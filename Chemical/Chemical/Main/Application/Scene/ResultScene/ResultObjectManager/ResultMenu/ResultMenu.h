/**
 * @file	ResultMenu.h
 * @brief	リザルトメニュークラス定義
 * @author	morimoto
 */
#ifndef RESULT_RESULTMENU_H
#define RESULT_RESULTMENU_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ObjectManagerBase\ObjectBase\ObjectBase.h"

#include "BackButton\BackButton.h"
#include "RestartButton\RestartButton.h"
#include "Ranking\Ranking.h"
#include "ResultScore\ResultScore.h"
#include "ResultTime\ResultTime.h"
#include "ResultMenuEvent\ResultMenuEvent.h"


namespace Result
{
	/*** リザルトメニュークラス */
	class ResultMenu : public Lib::ObjectBase
	{
	public:
		/*** コンストラクタ */
		ResultMenu();

		/*** デストラクタ */
		virtual ~ResultMenu();

		/**
		 * 初期化処理
		 * @return 初期化に成功したか
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

		/*** オブジェクトの更新 */
		virtual void Update();

		/*** オブジェクトの描画 */
		virtual void Draw();

	private:
		Lib::UpdateTask*	m_pUpdateTask;	//!< 更新タスクオブジェクト.
		BackButton*			m_pBackButton;
		RestartButton*		m_pRestartButton;
		Ranking*			m_pRanking;
		ResultScore*		m_pResultScore;
		ResultTime*			m_pResultTime;
		ResultMenuEvent*	m_pEvent;

		bool m_IsSelected;	//!< trueの場合バックボタンが選択.

		int m_SelectSEIndex;
		int m_EnterSEIndex;

	};
}


#endif // !RESULT_RESULTMENU_H
