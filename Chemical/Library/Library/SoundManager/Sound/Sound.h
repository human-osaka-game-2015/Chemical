/**
 * @file	Sound.h
 * @brief	サウンドクラス定義
 * @author	morimoto
 */
#ifndef LIB_SOUND_H
#define LIB_SOUND_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <dsound.h>

#include "..\..\Define\Define.h"
#include "..\SoundManager.h"
#include "..\ISound\ISound.h"


namespace Lib
{
	class SoundDevice;

	/**
	 * サウンドクラス
	 */
	class Sound : public ISound
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _pSoundDevice サウンドデバイス
		 * @param[in] _pSoundPath サウンドファイルのパス
		 */
		Sound(SoundDevice* _pSoundDevice, LPSTR _pSoundPath);

		/**
		 * デストラクタ
		 */
		virtual ~Sound();

		/**
		 * サウンドの操作
		 * @param[in] _operation サウンドに対して行う操作
		 */
		virtual void SoundOperation(SoundManager::SOUND_OPERATION _operation);

		/**
		 * サウンドの取得
		 * @return サウンドバッファ
		 */
		inline LPDIRECTSOUNDBUFFER8 Get() const
		{
			return m_pSound;
		}

	private:
		/**
		 * サウンドの読み込み
		 * @param[in] _pSoundPath テクスチャのパス
		 */
		void Load(LPSTR _pSoundPath);

		/**
		 * サウンドの解放
		 */
		void Release();

		/**
		 * waveファイルの読み込み
		 * @param[in] _pFilePath サウンドファイルのパス
		 * @param[out] _pWaveFormat waveファイルフォーマットの出力先
		 * @param[out] _pWaveData waveデータの出力先
		 * @param[out] _pDataSize データサイズの出力先
		 * @return 読み込みに成功したらtrue 失敗したらfalse
		 */
		bool WaveLoad(LPSTR _pFilePath, WAVEFORMATEX* _pWaveFormat, char** _pWaveData, DWORD* _pDataSize);


		SoundDevice*			m_pSoundDevice;	//!< サウンドデバイス.
		LPDIRECTSOUNDBUFFER8	m_pSound;		//!< サウンドバッファ.


		DISALLOW_COPY_AND_ASSIGN(Sound);

	};
}



#endif // !LIB_SOUND_H
