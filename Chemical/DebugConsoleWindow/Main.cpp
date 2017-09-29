/**
 * @file	Main.cpp
 * @brief	エントリポイント
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <Windows.h>
#include <stdio.h>
#include <string>


//----------------------------------------------------------------------
// Define
//----------------------------------------------------------------------
#define BUFFER_SIZE 512


void StringInit(char* _str, size_t _size)
{
	for (unsigned int i = 0; i < _size; i++)
	{
		_str[i] = '\0';
	}
}

int main(int _argc, char** _argv)
{
	HMENU Menu = GetSystemMenu(GetConsoleWindow(), FALSE);
	RemoveMenu(Menu, SC_CLOSE, MF_BYCOMMAND);	// バツボタンの無効化.
	SetConsoleTitle(_argv[0]);					// タイトルの変更.

	std::string Buffer;
	CHAR ReadBuffer[BUFFER_SIZE];
	DWORD dwRead;
	BOOL IsSuccess;

	// 入力ハンドルの取得.
	HANDLE InputHandle = GetStdHandle(STD_INPUT_HANDLE);
	if (InputHandle == INVALID_HANDLE_VALUE) return -1;

	// 出力ハンドルの取得.
	HANDLE OutputHandle = CreateFile(
		TEXT("CONOUT$"),
		GENERIC_WRITE,
		FILE_SHARE_READ,
		0,
		OPEN_EXISTING,
		0,
		0);
	if (OutputHandle == INVALID_HANDLE_VALUE) return -1;

	while (1)
	{
		StringInit(ReadBuffer, BUFFER_SIZE);

		// 入力ハンドルからの書き込みを取得.
		IsSuccess = ReadFile(
			InputHandle,
			ReadBuffer,
			BUFFER_SIZE,
			&dwRead,
			nullptr);

		if (!IsSuccess || !dwRead) break;

		// 出力ハンドルに書き込む.
		WriteFile(OutputHandle, ReadBuffer, dwRead, &dwRead, 0);
	}

	CloseHandle(OutputHandle);
	CloseHandle(InputHandle);

	return 0;
}