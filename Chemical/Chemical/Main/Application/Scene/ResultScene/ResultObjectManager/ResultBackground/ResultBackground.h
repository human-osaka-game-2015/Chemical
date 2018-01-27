/**
 * @file	リザルト背景クラス定義
 * @brief	ResultBackground.h
 * @author	morimoto
 */
#ifndef RESULT_RESULTBACKGROUND_H
#define RESULT_RESULTBACKGROUND_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Object2DBase\Object2DBase.h"

#include "Application\ResultFile\ResultFile.h"


namespace Result
{
	/*** リザルト背景クラス */
	class ResultBackground : public Object2DBase
	{
	public:
		/*** コンストラクタ */
		ResultBackground();

		/*** デストラクタ */
		virtual ~ResultBackground();

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

		/*** オブジェクトの更新 */
		virtual void Update();

		/*** オブジェクトの描画 */
		virtual void Draw();

	private:
		ResultFile	m_ResultFile;

	};
}


#endif // !RESULT_RESULTBACKGROUND_H
