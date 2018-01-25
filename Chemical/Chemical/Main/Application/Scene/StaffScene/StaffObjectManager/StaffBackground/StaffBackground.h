/**
 * @file	StaffBackground.h
 * @brief	スタッフバックグラウンド定義
 * @author	morimoto
 */
#ifndef STAFF_BACKGROUND_H
#define STAFF_BACKGROUND_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Object2DBase\Object2DBase.h"

#include "TitleBackEvent\TitleBackEvent.h"


namespace Staff
{
	/*** スタッフバックグラウンドクラス */
	class Background : public Object2DBase
	{
	public:
		/*** コンストラクタ */
		Background();

		/*** デストラクタ */
		virtual ~Background();

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
		TitleBackEvent* m_pEvent;

	};
}


#endif // !STAFF_BACKGROUND_H
