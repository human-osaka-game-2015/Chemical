/**
 * @file   JoyconManager.h
 * @brief  JoyconManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef JOYCONMANAGER_H
#define JOYCONMANAGER_H
#include "Joycon\Joycon.h"

#include <array>

class JoyconManager
{
public:
	static JoyconManager& GetInstance()
	{
		static JoyconManager Instance;
		return Instance;
	}

	/**
	 * Joyconを取得する
	 * @param _controllerType 取得するコントローラの種類
	 */
	const Joycon& GetJoycon(Joycon::CONTROLLER_TYPE _controllerType)
	{
		return *m_pJoycon[_controllerType];
	}


private:
	JoyconManager(const JoyconManager&) = delete;
	JoyconManager& operator=(const JoyconManager&) = delete;

	JoyconManager();
	~JoyconManager();

	Joycon* m_pJoycon[Joycon::MAX_CONTROLLER];

};


#endif
