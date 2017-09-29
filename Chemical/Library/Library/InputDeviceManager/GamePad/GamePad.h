/**
 * @file	GamePad.h
 * @brief	ゲームパッドクラス定義
 * @author	morimoto
 */
#ifndef LIB_GAMEPAD_H
#define LIB_GAMEPAD_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <Windows.h>
#include <XInput.h>


namespace Lib
{
	/**
	 * ゲームパッドクラス
	 */
	class GamePad
	{
	public:
		/**
		 * XboxコントローラのボタンID
		 */
		enum XINPUT_ID
		{
			GAMEPAD_DANALOG_UP,			//!< アナログ十字キー上.
			GAMEPAD_DANALOG_DOWN,		//!< アナログ十字キー下.
			GAMEPAD_DANALOG_LEFT,		//!< アナログ十字キー左.
			GAMEPAD_DANALOG_RIGHT,		//!< アナログ十字キー右.
			GAMEPAD_START,				//!< スタートボタン.
			GAMEPAD_BACK,				//!< バックボタン.
			GAMEANALOG_LEFT_THUMB,		//!< 左スティック押し込み.
			GAMEANALOG_RIGHT_THUMB,		//!< 右スティック押し込み.
			GAMEANALOG_LEFT_SHOULDER,	//!< LBキー.
			GAMEANALOG_RIGHT_SHOULDER,	//!< RBキー.
			GAMEPAD_A,					//!< Aボタン.
			GAMEPAD_B,					//!< Bボタン.
			GAMEPAD_X,					//!< Xボタン.
			GAMEPAD_Y,					//!< Yボタン.
			XINPUT_ID_MAX				//!< ボタンの総数.
		};

		/**
		 * XboxコントローラのID
		 */
		enum XINPUTPAD
		{
			GAMEPAD1,		//!< ゲームパッド1P.
			GAMEPAD2,		//!< ゲームパッド2P.
			GAMEPAD3,		//!< ゲームパッド3P.
			GAMEPAD4,		//!< ゲームパッド4P.
			GAMEANALOG_MAX	//!< ゲームパッドの最大数.
		};

		/**
		 * ボタンの状態 
		 */
		enum PADSTATE
		{
			PAD_PUSH,		//!< 押されたら.
			PAD_RELEASE,	//!< 離されたら.
			PAD_ON,			//!< 押され続けている.
			PAD_OFF			//!< 離され続けている.
		};

		/**
		 * アナログパッドの状態
		 */
		enum ANALOGPAD
		{
			ANALOG_LEFT,	//!< 左.
			ANALOG_RIGHT,	//!< 右.
			ANALOG_UP,		//!< 上.
			ANALOG_DOWN,	//!< 下.
			ANALOG_MAX		//!< 最大数.
		};


		/**
		 * コンストラクタ
		 */
		GamePad();

		/**
		 * デストラクタ
		 */
		~GamePad();

		/**
		 * GamePadの状態チェック関数
		 * @param[in] _pad チェックするパッド
		 */
		void Update(XINPUTPAD _pad);

		/**
		 * 指定のボタンの状態を更新する
		 * @param[in] _pad チェックするGamePad
		 * @param[in] _buttonId チェックするボタン
		 * @param[in] _xinputButton 更新するXINPUT_GAMEPADのボタン
		 */
		void CheckButton(XINPUTPAD _pad, XINPUT_ID _buttonId, WORD _xinputButton);

		/**
		 * GamePadのボタンの状態を取得する
		 * @param[in] id チェックするボタン
		 * @param[in] pad チェックするパッド
		 */
		PADSTATE GetButtonState(XINPUT_ID _buttonId, XINPUTPAD _pad);

		/**
		 * Lスティックの状態を取得する関数
		 * @param[in] id チェックするスティック
		 * @param[in] pad チェックするパッド
		 * @return スティックの状態
		 */
		bool GetLAnalogState(ANALOGPAD _analogId, XINPUTPAD _pad);

		/**
		 * Rスティックの状態を取得する関数
		 * @param[in] id チェックするスティック
		 * @param[in] pad チェックするパッド
		 * @return スティックの状態
		 */
		bool GetRAnalogState(ANALOGPAD _analogId, XINPUTPAD _pad);


	private:
		/**
		 * コントローラの状態構造体
		 */
		struct CONTROLER_STATE
		{
			XINPUT_STATE		State;		//!< ボタンなどの状態.
			XINPUT_VIBRATION	Vib_State;	//!< 振動の状態.
		};


		static const float m_ControlerDeadZone;	//!< コントローラーのデッドゾーン値.


		CONTROLER_STATE m_PadControlState[GAMEANALOG_MAX];				//!< コントローラステート構造体.
		PADSTATE		m_PadOldState[GAMEANALOG_MAX][XINPUT_ID_MAX];	//!< 前回のパッド状態構造体.
		PADSTATE		m_PadState[GAMEANALOG_MAX][XINPUT_ID_MAX];		//!< パッド状態構造体.


	};
}


#endif // !LIB_GAMEPAD_H
