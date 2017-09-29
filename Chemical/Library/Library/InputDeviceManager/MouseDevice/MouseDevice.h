/**
 * @file	MouseDevice.h
 * @brief	マウスデバイスクラス定義
 * @author	morimoto
 */
#ifndef LIB_MOUSEDEVICE_H
#define LIB_MOUSEDEVICE_H

//----------------------------------------------------------------------
// Define
//----------------------------------------------------------------------

// DirectInputのバージョン指定.
#define DIRECTINPUT_VERSION 0x0800


//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <dinput.h>


namespace Lib
{
	/** 
	 * マウスデバイスクラス
	 */
	class MouseDevice
	{
	public:
		/**
		 * マウスの状態を表した列挙子
		 */
		enum MOUSEBUTTONSTATE
		{
			MOUSEBUTTON_PUSH,	//!< マウスのボタンが押された瞬間の状態.
			MOUSEBUTTON_RELEASE,//!< マウスのボタンが離された瞬間の状態.
			MOUSEBUTTON_ON,		//!< マウスのボタンが押され続けている状態.
			MOUSEBUTTON_OFF		//!< マウスのボタンが離されている状態.
		};

		/**
		 * マウスの状態を格納する構造体
		 */
		struct MOUSESTATE
		{
			LONG				lX;			//!< マウスのX方向の移動量.
			LONG				lY;			//!< マウスのY方向の移動量.
			LONG				lZ;			//!< マウスのZ方向の移動量.
			MOUSEBUTTONSTATE	Buttons[4];	//!< マウスのボタンの状態.
			POINT				CursorPos;	//!< ウィンドウ内のカーソル位置.
		};

		/**
		 * コンストラクタ
		 */
		MouseDevice();

		/**
		 * デストラクタ
		 */
		~MouseDevice();

		/**
		 * 初期化処理
		 * @param[in] _pDInput8 DirectInput8オブジェクト
		 * @param[in] _hWnd デバイスに対応させるウィンドウハンドル
		 * @return 初期化に成功したらtrue 初期化に失敗したらfalse
		 */
		bool Initialize(LPDIRECTINPUT8 _pDInput8, HWND _hWnd);

		/**
		 * 終了処理
		 */
		void Finalize();

		/**
		 * マウスの状態を更新
		 */
		void Update();

		/**
		 * マウスの状態を取得
		 * @return マウスの状態
		 */
		inline const MOUSESTATE& GetMouseState() const 
		{ 
			return m_MouseState; 
		}

	private:
		LPDIRECTINPUT8			m_pDInput8;			//!< DirectInput8オブジェクト.
		LPDIRECTINPUTDEVICE8	m_pDInputDevice8;	//!< DirectInput8デバイス.
		HWND					m_hWnd;				//!< 対応するウィンドウハンドル.
		MOUSESTATE				m_MouseState;		//!< マウスとカーソルの状態を格納する構造体.
		DIMOUSESTATE			m_DIMouseState;		//!< マウスデバイスの状態を格納する構造体.
		DIMOUSESTATE			m_OldDIMouseState;	//!< マウスデバイスの古い状態を格納する構造体.

	};
}


#endif // !LIB_MOUSEDEVICE_H
