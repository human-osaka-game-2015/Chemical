/**
 * @file	Main.cpp
 * @brief	エントリポイント
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include 
//----------------------------------------------------------------------
#include <Windows.h>
#include "Application\Application.h"


int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _szStr, INT _iCmdShow)
{
	::ImmDisableIME(NULL);	// IMEは切っておく.

	Application App;
	if (!App.Initialize())
	{
		return -1;
	}

	App.Run();
	App.Finalize();

	return 0;
}
