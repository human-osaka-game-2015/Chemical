/**
 * @file	Dx11Animation.h
 * @brief	2Dアニメーションクラス定義
 * @author	morimoto
 */
#ifndef LIB_DX11_ANIMATION_H
#define LIB_DX11_ANIMATION_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <vector>
#include <Windows.h>

#include "..\IAnimation\Dx11IAnimation.h"


namespace Lib
{
	namespace Dx11
	{
		/**
		 * 2Dアニメーションクラス
		 */
		class Animation : public IAnimation
		{
		public:
			/**
			 * コンストラクタ
			 * @param[in] _pAnimationPath アニメーションファイルのパス
			 */
			Animation(LPCTSTR _pAnimationPath);

			/**
			 * デストラクタ
			 */
			virtual ~Animation();

			/**
			 * アニメーションの開始
			 */
			virtual void AnimationStart();

			/**
			 * アニメーションの更新
			 * @return アニメーションが終了したらtrue 終了していなかったらfalse
			 */
			virtual bool Update();

			/**
			 * アニメーションのパターンを設定する(設定前のフレーム等は初期化される)
			 * @param[in] _animationPattern アニメーションのパターン
			 */
			virtual void SetAnimationPattern(ANIMATION_PATTERN _animationPattern);

			/**
			 * アニメーションの速度を設定する
			 * @param[in] _animationSpeed アニメーションの速度
			 */
			virtual void SetAnimationSpeed(float _animationSpeed);

			/**
			 * フレーム番号の設定
			 * @param[in] _frameNumber 設定するフレームの番号
			 */
			virtual void SetFrameNumber(int _frameNumber);

			/**
			 * フレーム番号の取得
			 * @return 現在のフレーム番号
			 */
			virtual int GetFrameNumber();

			/**
			 * フレームの数を取得
			 * @return フレームの数
			 */
			virtual int GetFrameMax();

			/**
			 * 現在のフレームを取得する
			 * @return 現在のアニメーションフレーム
			 */
			virtual ANIMATION_FRAME* GetCurrentFrame() const;


		private:
			/**
			 * 読み込み処理
			 * @param[in] _pAnimationPath アニメーションファイルのパス
			 */
			void Load(LPCTSTR _pAnimationPath);

			/**
			 * 解放処理
			 */
			void Release();

			/**
			 * アニメーション制御
			 */
			bool OneAnimationControl();

			/**
			 * ループアニメーション制御
			 */
			bool LoopAnimationControl();

			/**
			 * 逆アニメーション制御
			 */
			bool ReverseOneAnimationControl();

			/**
			 * 逆ループアニメーション制御
			 */
			bool ReverseLoopAnimationControl();


			static const float				m_AnimationTime;	//!< アニメーションを行う時間.
			std::vector<ANIMATION_FRAME*>	m_pFrame;			//!< アニメーションフレーム.
			int								m_CurrentFrame;		//!< 現在のアニメーションフレーム.
			float							m_AnimationCounter;	//!< アニメーションを行うかを判断するためのカウンタ.
			float							m_AnimationSpeed;	//!< アニメーションを行うスピード.
			ANIMATION_PATTERN				m_AnimationPattern;	//!< アニメーションのパターン.
			bool							m_IsReverse;		//!< 反転しているか.
			bool							m_IsAnimationEnd;	//!< アニメーションが終了しているか.
			bool(Animation::*m_pAnimationFunc)();				//!< アニメーション更新関数ポインタ.

		};
	}
}


#endif // !LIB_DX11_ANIMATION_H
