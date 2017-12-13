/**
 * @file	PlayerUIManager.cpp
 * @brief	プレイヤーUIクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "PlayerUIManager.h"
#include "GaugeUIBase\PlayerGauge\PlayerGauge.h"
#include "GaugeUIBase\ChemicalGauge\ChemicalGauge.h"


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
		m_pGaugeUIs[PLAYER_GAUGE] = new PlayerGauge(m_pPlayerState);
		if (!m_pGaugeUIs[PLAYER_GAUGE]->Initialize()) return false;

		m_pGaugeUIs[CHEMICAL_GAUGE1] = new ChemicalGauge(&D3DXVECTOR2(100,100), &m_pPlayerState->ChemicalRemain[0]);
		if (!m_pGaugeUIs[CHEMICAL_GAUGE1]->Initialize()) return false;

		m_pGaugeUIs[CHEMICAL_GAUGE2] = new ChemicalGauge(&D3DXVECTOR2(200, 100), &m_pPlayerState->ChemicalRemain[1]);
		if (!m_pGaugeUIs[CHEMICAL_GAUGE2]->Initialize()) return false;

		m_pGaugeUIs[MIX_CHEMICAL_GAUGE1] = new ChemicalGauge(&D3DXVECTOR2(1720, 100), &m_pPlayerState->MixChemicalRemain[0]);
		if (!m_pGaugeUIs[MIX_CHEMICAL_GAUGE1]->Initialize()) return false;

		m_pGaugeUIs[MIX_CHEMICAL_GAUGE2] = new ChemicalGauge(&D3DXVECTOR2(1820, 100), &m_pPlayerState->MixChemicalRemain[1]);
		if (!m_pGaugeUIs[MIX_CHEMICAL_GAUGE2]->Initialize()) return false;

		return true;
	}

	void PlayerUIManager::Finalize()
	{
		for (auto pGaugeUIs : m_pGaugeUIs)
		{
			pGaugeUIs->Finalize();
			SafeDelete(pGaugeUIs);
		}
	}
}
