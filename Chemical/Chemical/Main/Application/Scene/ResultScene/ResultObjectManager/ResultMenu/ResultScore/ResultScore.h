/**
 * @file	ResultScore.h
 * @brief	リザルトスコアクラス定義
 * @author	morimoto
 */
#ifndef RESULT_RESULTSCORE_H
#define RESULT_RESULTSCORE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Object2DBase\Object2DBase.h"

#include "DirectX11\Font\Dx11Font.h"
#include "Application\ResultFile\ResultFile.h"


namespace Result
{
	/*** リザルトスコアクラス */
	class ResultScore : public Object2DBase
	{
	public:
		/*** コンストラクタ */
		ResultScore();

		/*** デストラクタ */
		virtual ~ResultScore();

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
		static const D3DXVECTOR2 m_DefaultPos;
		static const D3DXVECTOR2 m_DefaultSize;

		Lib::Dx11::Font* m_pFont;	//!< フォント描画オブジェクト.

		int m_Score;

		ResultFile m_ResultFile;

	};
}


#endif // !RESULT_RESULTSCORE_H
