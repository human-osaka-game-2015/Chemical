/**
 * @file	ISound.h
 * @brief	サウンドインターフェース定義
 * @author	morimoto
 */
#ifndef LIB_ISOUND_H
#define LIB_ISOUND_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <Windows.h>

#include "..\..\Define\Define.h"
#include "..\SoundManager.h"


namespace Lib
{
	/**
	 * サウンドインターフェース
	 */
	interface ISound
	{
	public:
		/**
		 * コンストラクタ
		 */
		ISound();

		/**
		 * デストラクタ
		 */
		virtual ~ISound() = 0;

		/**
		 * サウンドの操作
		 */
		virtual void SoundOperation(SoundManager::SOUND_OPERATION _operation) = 0;

	private:
		DISALLOW_COPY_AND_ASSIGN(ISound);

	};
}


#endif // !LIB_ISOUND_H
