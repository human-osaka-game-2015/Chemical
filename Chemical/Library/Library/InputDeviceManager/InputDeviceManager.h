/**
 * @file	InputDeviceManager.h
 * @brief	入力デバイスの管理クラス定義
 * @author	morimoto
 */
#ifndef LIB_INPUTDEVICEMANAGER_H
#define LIB_INPUTDEVICEMANAGER_H

//----------------------------------------------------------------------
// Define
//----------------------------------------------------------------------

// DirectInputのバージョン指定.
#define DIRECTINPUT_VERSION 0x0800


//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <dinput.h>

#include "GamePad\GamePad.h"
#include "KeyDevice\KeyDevice.h"
#include "MouseDevice\MouseDevice.h"
#include "..\SingletonBase\SingletonBase.h"


namespace Lib
{
	/**
	 * 入力デバイスの管理クラス
	 */
	class InputDeviceManager : public SingletonBase<InputDeviceManager>
	{
	public:
		friend SingletonBase<InputDeviceManager>;

		/**
		 * 管理するデバイスの種類
		 */
		enum INPUTDEVICE_TYPE
		{
			GAMEPAD_TYPE,		//!< コントローラー.
			KEYDEVICE_TYPE,		//!< キーボード.
			MOUSEDEVICE_TYPE,	//!< マウス.
			DEVICE_TYPE_MAX		//!< デバイス最大数.
		};

		/**
		 * 初期化処理
		 * @param[in] _hWnd 入力デバイスに対応するウィンドウハンドル
		 * @return 初期化に成功したか
		 */
		bool Initialize(HWND _hWnd);

		/**
		 * 終了処理
		 */
		void Finalize();

		/**
		 * デバイスの生成
		 * @param[in] _deviceType 生成するデバイスの種類
		 * @param[in] _isDebug デバッグ機能を使用するかの指定
		 * @param[in] _IsPlayDebugLog ログファイルを再生するかの指定
		 * @return 成功したらtrue 失敗したらfalse
		 */
		bool CreateDevice(INPUTDEVICE_TYPE _deviceType, bool _isDebug = false, bool _IsPlayDebugLog = false);

		/**
		 * デバイスの破棄
		 * @param[in] _deviceType 破棄するデバイスの種類
		 */
		void ReleaseDevice(INPUTDEVICE_TYPE _deviceType);

		/**
		 * KeyDeviceの状態を更新する
		 */
		void KeyUpdate();

		/**
		 * MouseDeviceの状態を更新する
		 */
		void MouseUpdate();

		/**
		 * GamePadの状態を更新する
		 */
		void GamePadUpdate(GamePad::XINPUTPAD _pad);

		/**
		 * キーの状態を更新する
		 * @param[in] 更新したいキーのDIK
		 */
		void KeyCheck(int _dik);

		/**
		 * 指定のボタンの状態を更新する
		 * @param[in] _pad チェックするGamePad
		 * @param[in] _buttonId チェックするボタン
		 * @param[in] _xinputButton 更新するXINPUT_GAMEPADのボタン
		 */
		void CheckButton(GamePad::XINPUTPAD _pad, GamePad::XINPUT_ID _buttonId, WORD _button);

		/**
		 * キーの状態が格納されている配列を取得する
		 * @return キーの状態が格納されている配列
		 */
		const KeyDevice::KEYSTATE* GetKeyState() const;

		/**
		 * マウスの状態を取得する
		 * @return マウスの状態が格納されている構造体
		 */
		const MouseDevice::MOUSESTATE GetMouseState() const;
		
		/**
		 * GamePadのボタンの状態を取得する
		 * @param[in] id チェックするボタン
		 * @param[in] pad チェックするGamePad
		 */
		GamePad::PADSTATE GetButtonState(GamePad::XINPUT_ID _buttonId, GamePad::XINPUTPAD _pad);

		/**
		 * Lスティックの状態を取得する関数
		 * @param[in] id チェックするスティック
		 * @param[in] pad チェックするGamePad
		 * @return スティックの状態
		 */
		bool GetLAnalogState(GamePad::ANALOGPAD _analogId, GamePad::XINPUTPAD _pad);

		/**
		 * Rスティックの状態を取得する関数
		 * @param[in] id チェックするスティック
		 * @param[in] pad チェックするGamePad
		 * @return スティックの状態
		 */
		bool GetRAnalogState(GamePad::ANALOGPAD _analogId, GamePad::XINPUTPAD _pad);

	private:
		/**
		 * コンストラクタ 
		 */
		InputDeviceManager();

		/**
		 * デストラクタ
		 */
		virtual ~InputDeviceManager();

		/**
		 * ゲームパッドの生成
		 * @param[in] _isDebug デバッグ機能を使用するかの指定
		 * @return 成功したらtrue 失敗したらfalse
		 */
		bool CreateGamePad(bool _isDebug, bool _IsPlayDebugLog);

		/**
		 * キーデバイスの生成
		 * @param[in] _isDebug デバッグ機能を使用するかの指定
		 * @return 成功したらtrue 失敗したらfalse
		 */
		bool CreateKeyDevice(bool _isDebug, bool _IsPlayDebugLog);

		/**
		 * マウスデバイスの生成
		 * @param[in] _isDebug デバッグ機能を使用するかの指定
		 * @return 成功したらtrue 失敗したらfalse
		 */
		bool CreateMouseDevice(bool _isDebug, bool _IsPlayDebugLog);

		/**
		 * ゲームパッドの破棄
		 */
		void ReleaseGamePad();

		/**
		 * キーデバイスの破棄
		 */
		void ReleaseKeyDevice();

		/**
		 * マウスデバイスの破棄
		 */
		void ReleaseMouseDevice();


		GamePad*		m_pGamePad;		//!< ゲームパッドオブジェクト.
		KeyDevice*		m_pKeyDevice;	//!< キーデバイスオブジェクト.
		MouseDevice*	m_pMouseDevice;	//!< マウスデバイスオブジェクト.
		LPDIRECTINPUT8	m_pDInput8;		//!< DirectInput8オブジェクト.
		HWND			m_hWnd;			//!< 対応するウィンドウハンドル.

	};
}


#endif // !LIB_INPUTDEVICEMANAGER_H
