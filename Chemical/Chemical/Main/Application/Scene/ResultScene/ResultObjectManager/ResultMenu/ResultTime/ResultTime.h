/**
 * @file	ResultTime.h
 * @brief	リザルト時間クラス定義
 * @author	morimoto
 */
#ifndef RESULT_RESULTTIME_H
#define RESULT_RESULTTIME_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Object2DBase\Object2DBase.h"

#include "DirectX11\Font\Dx11Font.h"
#include "Application\ResultFile\ResultFile.h"


namespace Result
{
	/*** リザルト時間クラス */
	class ResultTime : public Object2DBase
	{
	public:
		/*** コンストラクタ */
		ResultTime();

		/*** デストラクタ */
		virtual ~ResultTime();

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

		int m_Seconds;		//!< 経過時間(秒).
		int m_Minute;		//!< 経過時間(分).

		ResultFile m_ResultFile;

	};
}


#endif // !RESULT_RESULTTIME_H
