/**
 * @file	SoundManager.h
 * @brief	サウンド管理クラス定義
 * @author	morimoto
 */
#ifndef LIB_SOUNDMANAGER_H
#define LIB_SOUNDMANAGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <vector>

#include "..\SingletonBase\SingletonBase.h"


namespace Lib
{
	class SoundDevice;
	interface ISound;

	/**
	 * サウンドを管理するクラス
	 */
	class SoundManager : public SingletonBase<SoundManager>
	{
	public:
		friend SingletonBase<SoundManager>;

		static const int m_InvalidIndex;	//!< SoundManagerクラスがとるインデックスのエラー値.

		/**
		 * サウンドの操作
		 */
		enum SOUND_OPERATION
		{
			PLAY,				//!< 再生.
			PLAY_LOOP,			//!< ループ再生.
			STOP,				//!< 停止.
			RESET,				//!< 再生位置をリセットする.
			STOP_RESET,			//!< 再生位置をリセットして停止する.
			SOUND_OPERATION_MAX	//!< サウンド操作列挙子の数.
		};

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		bool Initialize(SoundDevice* _pSoundDevice);

		/**
		 * 終了処理
		 */
		void Finalize();

		/**
		 * サウンドの読み込み
		 * @param[in] _pSoundPath 読み込むサウンドのパス
		 * @param[out] _pIndex 読み込んだサウンド格納先インデックス
		 * @return 成功したらtrue 失敗したらfalse
		 */
		bool LoadSound(LPSTR _pSoundPath, int* _pIndex);

		/**
		 * サウンドの解放
		 * @param[in] _index 解放するサウンドのインデックス
		 */
		void ReleaseSound(int _index);

		/**
		 * サウンドの取得
		 * @param[in] _index 取得するサウンドのインデックス
		 * @return 格納先のサウンド
		 */
		inline ISound* GetSound(int _index) const
		{
			return m_pSounds[_index];
		}

		/**
		 * サウンドを格納しているバッファを解放する
		 */
		inline void ClearBuffer()
		{
			m_pSounds.clear();
		}

	private:
		/**
		 * コンストラクタ
		 */
		SoundManager();

		/**
		 * デストラクタ
		 */
		virtual ~SoundManager();


		std::vector<ISound*>	m_pSounds;		//!< サウンドオブジェクトを管理するコンテナ.
		SoundDevice*			m_pSoundDevice;	//!< サウンドデバイス.


		DISALLOW_COPY_AND_ASSIGN(SoundManager);

	};
}


#endif // !LIB_SOUNDMANAGER_H
