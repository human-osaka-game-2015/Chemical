/**
 * @file	Dx11AnimationManager.h
 * @brief	アニメーションの管理クラス定義
 * @author	morimoto
 */
#ifndef LIB_DX11_ANIMATIONMANAGER_H
#define LIB_DX11_ANIMATIONMANAGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <vector>

#include "..\..\SingletonBase\SingletonBase.h"


namespace Lib
{
	namespace Dx11
	{
		interface IAnimation;

		/**
		 * アニメーションの管理クラス
		 */
		class AnimationManager : public SingletonBase<AnimationManager>
		{
		public:
			friend SingletonBase<AnimationManager>;

			static const int m_InvalidIndex;	//!< AnimationManagerクラスがとるインデックスのエラー値.

			/**
			 * 初期化処理
			 * @return 初期化に成功したらtrue 失敗したらfalse
			 */
			bool Initialize();

			/**
			 * 終了処理
			 */
			void Finalize();

			/**
			 * アニメーションの読み込み
			 * @param[in] _pAnimationPath 読み込むアニメーションのパス
			 * @param[out] _pIndex 読み込んだアニメーション格納先インデックス
			 * @return 成功したらtrue 失敗したらfalse
			 */
			bool LoadAnimation(LPCTSTR _pAnimationPath, int* _pIndex);

			/**
			 * アニメーションの解放
			 * @param[in] _index 解放するアニメーションのインデックス
			 */
			void ReleaseAnimation(int _index);

			/**
			 * アニメーションの取得
			 * @param[in] _index 取得するアニメーションのインデックス
			 * @return 格納先のアニメーション
			 */
			inline IAnimation* GetAnimation(int _index) const
			{
				return m_pAnimation[_index];
			}

			/**
			 * アニメーションを格納しているバッファを解放する
			 */
			inline void ClearBuffer()
			{
				m_pAnimation.clear();
			}


		private:
			/**
			 * コンストラクタ
			 */
			AnimationManager();

			/**
			 * デストラクタ
			 */
			virtual ~AnimationManager();


			std::vector<IAnimation*>	m_pAnimation;	//!< アニメーションを格納するコンテナ.


			DISALLOW_COPY_AND_ASSIGN(AnimationManager);

		};
	}
}


#endif // !LIB_DX11_ANIMATIONMANAGER_H
