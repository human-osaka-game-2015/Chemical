/**
 * @file	Debugger.h
 * @brief	デバッグ機能定義
 * @author	morimoto
 */
#ifndef LIB_DEBUGGER_H
#define LIB_DEBUGGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <chrono>
#include <Windows.h>

#ifdef _DEBUG
#include <crtdbg.h>
#include <DbgHelp.h>
#include <typeinfo>
#endif // _DEBUG

#include "ConsoleWindow\ConsoleWindow.h"
#include "DebugTimer\DebugTimer.h"


namespace Lib
{
	namespace Debugger
	{
		/**
		 * メモリリークをチェックする
		 */
		void CheckMemoryLeak();

		/**
		 * デバッグログの出力関数
		 * @param[in] _pStr 出力する文字列
		 */
		void OutputDebugLog(TCHAR* _pStr, ...);

		/**
		 * ファイルを開く(ファイルがなければ作成する)
		 * @param[in] _pFilePath 開くファイルのパス
		 */
		void OpenLogFile(TCHAR* _pFilePath);

		/**
		 * デバッグ情報をファイルに書き込む
		 */
		void WriteLogFile(TCHAR* _pStr, ...);

		/**
		 * ファイルを閉じる
		 */
		void CloseLogFile();

		/**
		 * スタックフレーム情報を出力する
		 */
		void OutputStackFrame();

		/**
		 * 型名を文字列に変換して取得(型を直接受け取っているのでRTTIが無効でも問題ない)
		 * @tparam Type 変換する型名
		 * @return 型の文字列
		 */
		template <typename Type>
		LPCTSTR TypeToString()
		{
#ifdef _DEBUG
			return typeid(Type).name();
#else // _DEBUG
			return "";
#endif // !_DEBUG
		}

		/**
		 * 変数から型名を文字列に変換して取得
		 * @tparam Type 変数の型
		 * @param[in] _pType 型名を取得する変数 
		 * @return 型の文字列
		 */
		template <typename Type>
		LPCTSTR TypeToString(Type* _pType)
		{
#ifdef _DEBUG
			return typeid(*_pType).name();
#else // _DEBUG
			return "";
#endif // !_DEBUG
		}

	}
}


#ifdef _DEBUG

// アサートマクロ.
#define MyAssert(_expression, _str)											\
	do																		\
	{																		\
		if ((_expression))													\
		{																	\
			Lib::Debugger::OutputDebugLog(									\
			"\nMyAssert: %s\nErrorLog: %s\nFileName: %s\nLine: %d\n\n",		\
			#_expression,													\
			TEXT(_str),														\
			__FILE__,														\
			__LINE__);														\
			DebugBreak();													\
		}																	\
	} while (0)

// 静的アサートマクロ.
#define StaticMyAssert(_expression, _str)									\
	do																		\
	{																		\
		static_assert(!(_expression), _str);								\
	} while (0)

// デバッグログ出力マクロ.
#define OutputErrorLog(_str)														\
	do																				\
	{																				\
		Lib::Debugger::OutputDebugLog("\n\n---------------Error---------------");	\
		Lib::Debugger::OutputDebugLog("\nErrorLog: %s\nFileName: %s\nLine: %d\n\n", \
		TEXT(_str),																	\
		__FILE__,																	\
		__LINE__);																	\
	} while (0)

#else

#define MyAssert(_expression, _str) (void(0))

#define StaticMyAssert(_expression, _str) (void(0))

#define OutputErrorLog(_str) (void(0))

#endif // _DEBUG



#endif // !LIB_DEBUGGER_H
