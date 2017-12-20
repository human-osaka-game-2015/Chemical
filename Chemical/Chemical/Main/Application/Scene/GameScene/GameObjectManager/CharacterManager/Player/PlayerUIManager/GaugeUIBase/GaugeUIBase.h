/**
 * @file   GaugeUIBase.h
 * @brief  GaugeUIBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAME_GAUGEUIBASE_H
#define GAME_GAUGEUIBASE_H

#include "Object2DBase\Object2DBase.h"

namespace Game
{
	class GaugeUIBase : public Object2DBase
	{
	public:
		/*** コンストラクタ */
		GaugeUIBase() :
			m_GaugeMaxValue(100.f),
			m_GaugeValue(100.f){}

		/*** デストラクタ */
		virtual ~GaugeUIBase(){}
		
		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize() = 0;

		/*** 終了処理 */
		virtual void Finalize(){}

		/*** 更新処理 */
		virtual void Update(){}

		/*** 描画処理 */
		virtual void Draw();

	protected:
		float m_GaugeMaxValue; //!< ゲージの最大値
		float m_GaugeValue;	   //!< ゲージの数値
		int   m_GaugeTextureIndex;
		int   m_FrameTextureIndex;

	};
}


#endif
