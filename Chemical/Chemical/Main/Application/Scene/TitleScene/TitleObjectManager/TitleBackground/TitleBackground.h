/**
 * @file	TitleBackground.h
 * @brief	タイトルバックグラウンド定義
 * @author	morimoto
 */
#ifndef TITLE_BACKGROUND_H
#define TITLE_BACKGROUND_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Object2DBase\Object2DBase.h"


namespace Title
{
	/**
	 * タイトルバックグラウンドクラス
	 */
	class Background : public Object2DBase
	{
	public:
		/**
		 * コンストラクタ
		 */
		Background();

		/**
		 * デストラクタ
		 */
		virtual ~Background();

		/**
		 * 初期化処理
		 * @return 初期化に成功したか
		 */
		virtual bool Initialize();

		/**
		 * 終了処理
		 */
		virtual void Finalize();

		/**
		 * オブジェクトの更新
		 */
		virtual void Update();

		/**
		 * オブジェクトの描画
		 */
		virtual void Draw();

	};
}


#endif // !TITLE_BACKGROUND_H
