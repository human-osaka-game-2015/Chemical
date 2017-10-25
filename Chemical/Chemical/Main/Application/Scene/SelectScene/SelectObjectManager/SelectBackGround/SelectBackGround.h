/**
 * @file   SelectBackGround.h
 * @brief  BackGroundクラスのヘッダファイル
 * @author kotani
 */
#ifndef STAGE_SELECT_BACKGROUND_H
#define STAGE_SELECT_BACKGROUND_H
#include "Object2DBase\Object2DBase.h"


namespace Select
{
	class BackGround : public Object2DBase
	{
	public:
		/*** コンストラクタ */
		BackGround();

		/*** デストラクタ */
		virtual ~BackGround();

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
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

	private:

	};
}	

#endif