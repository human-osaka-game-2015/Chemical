/**
 * @file	TitleBackLogo.h
 * @brief	タイトルロゴクラス定義
 * @author	morimoto
 */
#ifndef TITLE_BACKLOGO_H
#define TITLE_BACKLOGO_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Object2DBase\Object2DBase.h"


namespace Title
{
	/*** タイトルロゴクラス */
	class BackLogo : public Object2DBase
	{
	public:
		/*** コンストラクタ */
		BackLogo();

		/*** デストラクタ */
		virtual ~BackLogo();

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

	};
}


#endif // !TITLE_BACKLOGO_H
