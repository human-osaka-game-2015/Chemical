/**
 * @file   SpeedUpChemicalEvent.cpp
 * @brief  踏んだら足が速くなるインベントクラスの実装
 * @author kotani
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "SpeedUpChemicalEvent.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------

	SpeedUpChemicalEvent::SpeedUpChemicalEvent(unsigned int _eventID) :
		EventBase(_eventID),
		m_SpeedUpPos(0, 0)
	{
	}

	SpeedUpChemicalEvent::~SpeedUpChemicalEvent()
	{
	}
}
