/**
 * @file	SoundManager.cpp
 * @brief	サウンド管理クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "SoundManager.h"

#include "Sound\Sound.h"


namespace Lib
{
	//----------------------------------------------------------------------
	// Static Public Variables
	//----------------------------------------------------------------------
	const int SoundManager::m_InvalidIndex = 0;


	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	SoundManager::SoundManager()
	{
	}

	SoundManager::~SoundManager()
	{
		Finalize();
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool SoundManager::Initialize(SoundDevice* _pSoundDevice)
	{
		m_pSoundDevice = _pSoundDevice;
		return true;
	}

	void SoundManager::Finalize()
	{
		for (auto itr = m_pSounds.begin(); itr != m_pSounds.end(); itr++)
		{
			SafeDelete(*itr);
		}
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool SoundManager::LoadSound(LPSTR _pSoundPath, int* _pIndex)
	{
		Sound* pSound = new Sound(m_pSoundDevice, _pSoundPath);

		if (pSound->Get() == nullptr)
		{
			SafeDelete(pSound);
			*_pIndex = m_InvalidIndex;
			return false;
		}

		*_pIndex = m_pSounds.size();
		m_pSounds.push_back(pSound);

		return true;
	}

	void SoundManager::ReleaseSound(int _index)
	{
		SafeDelete(m_pSounds[_index]);
	}
}

