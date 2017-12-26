/**
 * @file	PlayerUIManager.cpp
 * @brief	プレイヤーUIクラス実装
 * @author	kotani
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "PlayerUIManager.h"
#include "GaugeUIBase\PlayerGauge\PlayerGauge.h"
#include "GaugeUIBase\ChemicalGauge\ChemicalGauge.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------

	PlayerUIManager::PlayerUIManager(const Player::PlayerState* _pPlayerState) :
		m_pPlayerState(_pPlayerState)
	{
	}

	PlayerUIManager::~PlayerUIManager()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------

	bool PlayerUIManager::Initialize()
	{
		if (!LoadTextures()) return false;
		
		if (!CreateGaugeUIs()) return false;

		return true;
	}

	void PlayerUIManager::Finalize()
	{
		for (auto TextureIndex : m_TextureIndexs)
		{
			SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(TextureIndex);
		}

		for (auto pGaugeUIs : m_pGaugeUIs)
		{
			pGaugeUIs->Finalize();
			SafeDelete(pGaugeUIs);
		}
	}


	//----------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------

	bool PlayerUIManager::LoadTextures()
	{
		auto LoadTexture = [this](const char* _fileName, CHEMICAL_TYPE _chemicalType)
		{
			char Str[256];
			sprintf_s(Str, "Resource\\GameScene\\Texture\\ChemicalColor\\%s", _fileName);
			
			if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
				Str,
				&m_TextureIndexs[_chemicalType])) return false;

			return true;
		};

		if (!LoadTexture("Blue.png", CHEMICAL_BLUE)) return false;
		
		if (!LoadTexture("Red.png", CHEMICAL_RED)) return false;
		
		if (!LoadTexture("Yellow.png", CHEMICAL_YELLOW)) return false;
		
		if (!LoadTexture("Explosion.png", CHEMICAL_EXPLOSION)) return false;
		
		if (!LoadTexture("SpeedUp.png", CHEMICAL_SPEEDUP)) return false;
		
		if (!LoadTexture("Rain.png", CHEMICAL_RAIN)) return false;

		return true;
	}

	bool PlayerUIManager::CreateGaugeUIs()
	{
		m_pGaugeUIs[PLAYER_GAUGE] = new PlayerGauge(m_pPlayerState);
		if (!m_pGaugeUIs[PLAYER_GAUGE]->Initialize()) return false;

		m_pGaugeUIs[CHEMICAL_GAUGE1] = new ChemicalGauge(
			&D3DXVECTOR2(100, 100),
			&m_pPlayerState->ChemicalData[0],
			m_TextureIndexs);
		if (!m_pGaugeUIs[CHEMICAL_GAUGE1]->Initialize()) return false;

		m_pGaugeUIs[CHEMICAL_GAUGE2] = new ChemicalGauge(
			&D3DXVECTOR2(200, 100),
			&m_pPlayerState->ChemicalData[1],
			m_TextureIndexs);
		if (!m_pGaugeUIs[CHEMICAL_GAUGE2]->Initialize()) return false;

		m_pGaugeUIs[MIX_CHEMICAL_GAUGE1] = new ChemicalGauge(
			&D3DXVECTOR2(1720, 100),
			&m_pPlayerState->MixChemicalData[0],
			m_TextureIndexs);
		if (!m_pGaugeUIs[MIX_CHEMICAL_GAUGE1]->Initialize()) return false;

		m_pGaugeUIs[MIX_CHEMICAL_GAUGE2] = new ChemicalGauge(
			&D3DXVECTOR2(1820, 100),
			&m_pPlayerState->MixChemicalData[1],
			m_TextureIndexs);
		if (!m_pGaugeUIs[MIX_CHEMICAL_GAUGE2]->Initialize()) return false;

		return true;
	}
}
