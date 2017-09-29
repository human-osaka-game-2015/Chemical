/**
 * @file	Sound.cpp
 * @brief	サウンドクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Sound.h"

#include "..\..\Debugger\Debugger.h"
#include "..\..\SoundDevice\SoundDevice.h"


namespace Lib
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	Sound::Sound(SoundDevice* _pSoundDevice, LPSTR _pSoundPath) :
		m_pSoundDevice(_pSoundDevice),
		m_pSound(nullptr)
	{
		Load(_pSoundPath);
	}

	Sound::~Sound()
	{
		Release();
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void Sound::SoundOperation(SoundManager::SOUND_OPERATION _operation)
	{
		switch (_operation)
		{
		case SoundManager::PLAY:
			m_pSound->Play(0, 0, 0);
			break;
		case SoundManager::PLAY_LOOP:
			m_pSound->Play(0, 0, DSBPLAY_LOOPING);
			break;
		case SoundManager::STOP:
			m_pSound->Stop();
			break;
		case SoundManager::RESET:
			m_pSound->SetCurrentPosition(0);
			break;
		case SoundManager::STOP_RESET:
			m_pSound->Stop();
			m_pSound->SetCurrentPosition(0);
			break;
		default:
			OutputErrorLog("サウンドに無効な操作が行われました");
			break;
		}
	}


	//----------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------
	void Sound::Load(LPSTR _pSoundPath)
	{
		WAVEFORMATEX WaveFormat;
		char* pWaveData = 0;
		DWORD WaveSize = 0;

		if (!WaveLoad(_pSoundPath, &WaveFormat, &pWaveData, &WaveSize))
		{
			OutputErrorLog("サウンドの読み込みに失敗しました");
			return;
		}

		DSBUFFERDESC DSBufferDesc;
		DSBufferDesc.dwSize = sizeof(DSBUFFERDESC);
		DSBufferDesc.dwFlags = 0;
		DSBufferDesc.dwBufferBytes = WaveSize;
		DSBufferDesc.dwReserved = 0;
		DSBufferDesc.lpwfxFormat = &WaveFormat;
		DSBufferDesc.guid3DAlgorithm = GUID_NULL;

		IDirectSoundBuffer* pTmpBuffer = nullptr;
		m_pSoundDevice->GetInstance()->GetSoundObject()->CreateSoundBuffer(&DSBufferDesc, &pTmpBuffer, nullptr);
		pTmpBuffer->QueryInterface(IID_IDirectSoundBuffer8, reinterpret_cast<void**>(&m_pSound));
		pTmpBuffer->Release();

		if (m_pSound == nullptr)
		{
			OutputErrorLog("サウンドの読み込みに失敗しました");
			SafeDeleteArray(pWaveData);
			return;
		}

		LPVOID pData = nullptr;
		DWORD Length = 0;
		if (FAILED(m_pSound->Lock(0, 0, &pData, &Length, nullptr, nullptr, DSBLOCK_ENTIREBUFFER)))
		{
			OutputErrorLog("サウンドの読み込みに失敗しました");
			SafeDeleteArray(pWaveData);
			return;
		}

		memcpy(pData, pWaveData, Length);
		m_pSound->Unlock(pData, Length, nullptr, 0);

		SafeDeleteArray(pWaveData);
	}

	void Sound::Release()
	{
		SafeRelease(m_pSound);
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool Sound::WaveLoad(LPSTR _pFilePath, WAVEFORMATEX* _pWaveFormat, char** _pWaveData, DWORD* _pDataSize)
	{
		HMMIO hMmio = nullptr;
		MMIOINFO MmioInfo;
		ZeroMemory(&MmioInfo, sizeof(MMIOINFO));

		hMmio = mmioOpen(_pFilePath, &MmioInfo, MMIO_READ);
		if (hMmio == nullptr)
		{
			return false;
		}

		MMRESULT MmResult;
		MMCKINFO RiffChunk;
		RiffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		MmResult = mmioDescend(hMmio, &RiffChunk, nullptr, MMIO_FINDRIFF);
		if (MmResult != MMSYSERR_NOERROR)
		{
			mmioClose(hMmio, 0);
			return false;
		}

		MMCKINFO FormatChunk;
		FormatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
		MmResult = mmioDescend(hMmio, &FormatChunk, &RiffChunk, MMIO_FINDCHUNK);
		if (MmResult != MMSYSERR_NOERROR)
		{
			mmioClose(hMmio, 0);
			return false;
		}

		DWORD FormatSize = FormatChunk.cksize;
		DWORD Size = mmioRead(hMmio, reinterpret_cast<HPSTR>(_pWaveFormat), FormatSize);
		if (Size != FormatSize)
		{
			mmioClose(hMmio, 0);
			return false;
		}

		mmioAscend(hMmio, &FormatChunk, 0);


		MMCKINFO DataChunk;
		DataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
		MmResult = mmioDescend(hMmio, &DataChunk, &RiffChunk, MMIO_FINDCHUNK);
		if (MmResult != MMSYSERR_NOERROR)
		{
			mmioClose(hMmio, 0);
			return false;
		}

		*_pWaveData = new char[DataChunk.cksize];
		Size = mmioRead(hMmio, reinterpret_cast<HPSTR>(*_pWaveData), DataChunk.cksize);
		*_pDataSize = Size;
		if (Size != DataChunk.cksize)
		{
			mmioClose(hMmio, 0);
			delete[] * _pWaveData;
			return false;
		}

		mmioClose(hMmio, 0);

		return true;
	}
}

