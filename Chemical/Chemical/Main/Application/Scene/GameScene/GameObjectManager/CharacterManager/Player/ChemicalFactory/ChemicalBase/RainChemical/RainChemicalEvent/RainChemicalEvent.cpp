/**
 * @file   RainChemicalEvent.cpp
 * @brief  雨を降らせるインベントクラスの実装
 * @author kotani
 */
//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "RainChemicalEvent.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------

	RainChemicalEvent::RainChemicalEvent(unsigned int _eventID) :
		EventBase(_eventID),
		m_RainPos(0, 0)
	{
	}

	RainChemicalEvent::~RainChemicalEvent()
	{
	}
}
