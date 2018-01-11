/**
 * @file   JoyconManager.cpp
 * @brief  JoyconManagerクラスの実装
 * @author kotani
 */
#include "JoyconManager.h"


//----------------------------------------------------------------------
// Constructor	Destructor
//----------------------------------------------------------------------

JoyconManager::JoyconManager()
{
	for (int i = 0; i < Joycon::MAX_CONTROLLER; i++)
		m_pJoycon[i] = new Joycon();
}


JoyconManager::~JoyconManager()
{
	for (int i = 0; i < Joycon::MAX_CONTROLLER; i++)
	{
		delete m_pJoycon[i];
		m_pJoycon[i] = nullptr;
	}
	hid_exit();
}
