/**
 * @file	Dx11IAnimation.h
 * @brief	アニメーションインターフェース定義
 * @author	morimoto
 */
#ifndef LIB_DX11_IANIMATION_H
#define LIB_DX11_IANIMATION_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <Windows.h>

#include "..\..\..\Define\Define.h"


namespace Lib
{
	namespace Dx11
	{
		/**
		 * アニメーションインターフェース
		 */
		interface IAnimation
		{
		public:
			/**
			 * アニメーションのパターン
			 */
			enum ANIMATION_PATTERN
			{
				ONE_ANIMATION,			//!< アニメーションが終了したらそのまま終了する.
				LOOP_ANIMATION,			//!< アニメーションが終了したら最初からループする.
				REVERSE_ONE_ANIMATION,	//!< アニメーションが終了したら反転して最初まで戻る.
				REVERSE_LOOP_ANIMATION	//!< アニメーションが終了したら反転して最初まで戻るのをする.
			};

			/**
			 * アニメーションのフレーム情報
			 */
			struct ANIMATION_FRAME
			{
				int FrameID;	//!< フレームのID.
				float MinTu;	//!< tuの最小値.
				float MinTv;	//!< tvの最小値.
				float MaxTu;	//!< tuの最大値.
				float MaxTv;	//!< tvの最大値.
			};


			/**
			 * コンストラクタ
			 */
			IAnimation();

			/**
			 * デストラクタ
			 */
			virtual ~IAnimation() = 0;

			/**
			 * アニメーションの開始
			 */
			virtual void AnimationStart() = 0;

			/**
			 * アニメーションの更新
			 * @return アニメーションが終了したらtrue 終了していなかったらfalse
			 */
			virtual bool Update() = 0;

			/**
			 * アニメーションのパターンを設定する(設定前のフレーム等は初期化される)
			 * @param[in] _animationPattern アニメーションのパターン
			 */
			virtual void SetAnimationPattern(ANIMATION_PATTERN _animationPattern) = 0;

			/**
			 * アニメーションの速度を設定する
			 * @param[in] _animationSpeed アニメーションの速度
			 */
			virtual void SetAnimationSpeed(float _animationSpeed) = 0;

			/**
			 * フレーム番号の設定
			 * @param[in] _frameNumber 設定するフレームの番号
			 */
			virtual void SetFrameNumber(int _frameNumber) = 0;

			/**
			 * フレーム番号の取得
			 * @return 現在のフレーム番号
			 */
			virtual int GetFrameNumber() = 0;

			/**
			 * フレームの数を取得
			 * @return フレームの数
			 */
			virtual int GetFrameMax() = 0;

			/**
			 * 現在のフレームを取得する
			 * @return 現在のアニメーションフレーム
			 */
			virtual ANIMATION_FRAME* GetCurrentFrame() const = 0;


		private:
			DISALLOW_COPY_AND_ASSIGN(IAnimation);

		};
	}
}



#endif // !LIB_DX11_IANIMATION_H
