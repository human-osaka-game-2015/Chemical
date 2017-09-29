/**
 * @file	Window.h
 * @brief	ウィンドウクラス定義
 * @author	morimoto
 */
#ifndef LIB_WINDOW_H
#define LIB_WINDOW_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <Windows.h>


namespace Lib
{
	/**
	 * ウィンドウクラス
	 */
	class Window
	{
	public:
		/**
		 * コンストラクタ
		 */
		Window();
	
		/**
		 * デストラクタ
		 */
		~Window();
	
		/**
		 * ウィンドウ作成
		 * @param[in] _pWindowName ウィンドウの名前
		 * @param[in] _windowWidth ウィンドウの幅
		 * @param[in] _windowHeight ウィンドウの高さ
		 * @param[in] _style ウィンドウのスタイル
		 * @param[in] _hWndParent 親ウィンドウのハンドル
		 * @return 作成に成功したらtrue 失敗したらfalse
		 */
		bool Initialize(
			LPCTSTR _pWindowName,
			int _windowWidth, 
			int _windowHeight,
			DWORD _style, 
			HWND _hWndParent = nullptr);
	
		/**
		 * ウィンドウ破棄
		 */
		void Finalize();

		/**
		 * ウィンドウの更新
		 * @return ウィンドウが破棄されたらtrue されてなければfalse
		 */
		bool Update();
	
		/**
		 * ウィンドウハンドルを取得
		 * @return ウィンドウハンドル
		 */
		inline HWND GetWindowHandle() const
		{
			return m_hWnd;
		}
	
	private:
		HWND	m_hWnd;			//!< ウィンドウハンドル.
		HWND	m_hWndParent;	//!< 親ウィンドウハンドル.
		MSG		m_WindowMsg;	//!< ウィンドウメッセージ構造体.

	};
}


#endif // !LIB_WINDOW_H
