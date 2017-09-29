/**
 * @file	SoundDevice.h
 * @brief	サウンドデバイスの管理クラス定義
 * @author	morimoto
 */
#ifndef SOUNDDEVICE_H
#define SOUNDDEVICE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <dsound.h>

#include "..\SingletonBase\SingletonBase.h"


namespace Lib
{
	/**
	 * サウンドデバイスの管理クラス
	 */
	class SoundDevice : public SingletonBase<SoundDevice>
	{
	public:
		friend SingletonBase<SoundDevice>;

		/**
		 * 初期化処理
		 * @param[in] _hWnd GraphicsDeviceが対応するウィンドウのハンドル
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		bool Initialize(HWND _hWnd);

		/**
		 * 終了処理
		 */
		void Finalize();

		/**
		 * サウンドオブジェクトを取得する
		 * @return サウンドオブジェクト
		 */
		inline IDirectSound8* GetSoundObject() const
		{
			return m_pDSound8;
		}

	private:
		/**
		 * コンストラクタ
		 */
		SoundDevice();

		/**
		 * デストラクタ
		 */
		virtual ~SoundDevice();


		IDirectSound8*	m_pDSound8;	//!< サウンドオブジェクト.
		HWND			m_hWnd;		//!< 対応するウィンドウハンドル.


		DISALLOW_COPY_AND_ASSIGN(SoundDevice);

	};
}


#endif // !LIB_SOUNDDEVICE_H
