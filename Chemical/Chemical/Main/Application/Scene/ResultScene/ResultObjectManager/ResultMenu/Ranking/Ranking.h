/**
 * @file	Ranking.h
 * @brief	ランキングクラス定義
 * @author	morimoto
 */
#ifndef RESULT_RANKING_H
#define RESULT_RANKING_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Object2DBase\Object2DBase.h"

#include "DirectX11\Font\Dx11Font.h"
#include "Application\ResultFile\ResultFile.h"


namespace Result
{
	/*** ランキングクラス */
	class Ranking : public Object2DBase
	{
	public:
		/*** コンストラクタ */
		Ranking();

		/*** デストラクタ */
		virtual ~Ranking();

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

		int m_Ranking;

		ResultFile m_ResultFile;


	};
}


#endif // !RESULT_RANKING_H
