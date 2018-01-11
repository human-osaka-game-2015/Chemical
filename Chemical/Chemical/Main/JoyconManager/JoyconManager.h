/**
 * @file   JoyconManager.h
 * @brief  JoyconManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef JOYCONMANAGER_H
#define JOYCONMANAGER_H
#include "Joycon\Joycon.h"
#include "SingletonBase\SingletonBase.h"

#include <array>

class JoyconManager
{
	friend Lib::SingletonBase<JoyconManager> ;
public:
	/**
	 * Joyconを取得する
	 * @param _controllerType 取得するコントローラの種類
	 */
	Joycon* GetJoycon(Joycon::CONTROLLER_TYPE _controllerType) const
	{
		return m_pJoycon[_controllerType];
	}

	bool Connect(Joycon::CONTROLLER_TYPE _controllerType) const
	{
		return m_pJoycon[_controllerType]->Connect(_controllerType);
	}

	void Disconnect(Joycon::CONTROLLER_TYPE _controllerType) const
	{
		m_pJoycon[_controllerType]->Disconnect();
	}

	void CheckButton(Joycon::CONTROLLER_TYPE _controllerType, int _button) const
	{
		m_pJoycon[_controllerType]->CheckButton(_button);
	}

private:
	JoyconManager(const JoyconManager&) = delete;
	JoyconManager& operator=(const JoyconManager&) = delete;

	JoyconManager();
	~JoyconManager();

	Joycon* m_pJoycon[Joycon::MAX_CONTROLLER];

};


#endif
