/**
 * @file	KeyDevice.h
 * @brief	キーデバイスクラス定義
 * @author	morimoto
 */
#ifndef LIB_KEYDEVICE_H
#define LIB_KEYDEVICE_H

//----------------------------------------------------------------------
// Define
//----------------------------------------------------------------------

// DirectInputのバージョン指定.
#define DIRECTINPUT_VERSION 0x0800


//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <dinput.h>
#include <stdio.h>


namespace Lib
{
	/**
	 * キーデバイスクラス
	 */
	class KeyDevice
	{
	public:
		/**
		 * キーの状態を表した列挙子
		 */
		enum KEYSTATE
		{
			KEY_PUSH,		//!< キーが押された瞬間の状態.
			KEY_RELEASE,	//!< キーが離された瞬間の状態.
			KEY_ON,			//!< キーが押され続けている状態.
			KEY_OFF			//!< キーが押されていない状態.
		};

		/** 
		 * コンストラクタ
		 */
		KeyDevice();

		/**
		 * デストラクタ
		 */
		~KeyDevice();

		/**
		 * 初期化処理
		 * @param[in] _pDInput8 DirectInput8オブジェクト
		 * @param[in] _hWnd デバイスに対応させるウィンドウハンドル
		 * @param[in] _IsDebug デバッグ機能を使用するかの指定
		 * @param[in] _IsPlayDebugLog ログファイルを再生するかの指定
		 * @return 初期化に成功したらtrue 初期化に失敗したらfalse
		 */
		bool Initialize(
			LPDIRECTINPUT8 _pDInput8, 
			HWND _hWnd, 
			bool _IsDebug = false, 
			bool _IsPlayDebugLog = false);

		/**
		 * 終了処理
		 */
		void Finalize();

		/**
		 * デバイスの状態を更新する
		 */
		void Update();

		/**
		 * キーの状態を更新する
		 * @param[in] 更新したいキーのDIK
		 */
		void KeyCheck(int _dik);

		/**
		 * キーの状態が格納されている配列を取得する
		 * @return キーの状態が格納されている配列
		 */
		inline const KEYSTATE* GetKeyState() const 
		{
			return m_pKeyState;
		}

	private:
		static const char*	m_pDebugFileName;	//!< デバッグファイルの名前.
		static const int	m_DebugFileSizeMax;	//!< デバッグファイルの最大サイズ.
		static const int	m_TimeCounterMax;	//!< 時間カウンタの最大値.
		static const int	m_TimeCounter2Max;	//!< 時間カウンタ2の最大値.

		/**
		 * 通常時の更新関数
		 */
		void NormalUpdate();

		/**
		 * デバッグログを出力する際の更新関数
		 */
		void DebugUpdate();

		/**
		 * デバッグログを実行する際の更新関数
		 */
		void DebugLogPlay();


		LPDIRECTINPUT8			m_pDInput8;				//!< DirectInput8オブジェクト.
		LPDIRECTINPUTDEVICE8	m_pDInputDevice8;		//!< DirectInput8デバイス.
		HWND					m_hWnd;					//!< 対応するウィンドウハンドル.
		KEYSTATE				m_pKeyState[256];		//!< キーの状態を格納する構造体.
		BYTE					m_pDIKeyState[256];		//!< キーの状態を格納している配列.
		BYTE					m_pOldDIKeyState[256];	//!< キーの古い状態を格納している配列.
		void(KeyDevice::*m_pUpdateFunc)();				//!< 更新関数ポインタ.

		bool					m_IsDebug;				//!< デバッグ機能を使用するか.
		FILE*					m_pDebugFile;			//!< デバッグ情報を出力するファイル.
		int						m_TimeCounter;			//!< 時間カウンタ.
		int						m_TimeCounter2;			//!< 時間カウンタ2.
		bool					m_IsDebugLogPlay;		//!< デバッグログを再生するか.

	};
}


#endif // !LIB_KEYDEVICE_H
