/**
 * @file   ChemicalFactory.cpp
 * @brief  ChemicalFactoryクラスの実装
 * @author kotani
 */
#include "ChemicalFactory.h"
#include "ChemicalBase\ExplosionChemical\ExplosionChemical.h"
#include "DirectX11\AnimationManager\Dx11AnimationManager.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------

	bool ChemicalFactory::Initialize()
	{
		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\GameScene\\Texture\\Explosion.png",
			&m_TextureIndex[Types(CHEMICAL_BLUE, CHEMICAL_RED)])) return false;

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\GameScene\\Texture\\Explosion.png",
			&m_TextureIndex[Types(CHEMICAL_BLUE, CHEMICAL_YELLOW)])) return false;

		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\GameScene\\Texture\\Explosion.png",
			&m_TextureIndex[Types(CHEMICAL_RED, CHEMICAL_YELLOW)])) return false;

		return true;
	}

	void ChemicalFactory::Finalize()
	{
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->
			ReleaseTexture(m_TextureIndex[Types(CHEMICAL_BLUE, CHEMICAL_RED)]);

		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->
			ReleaseTexture(m_TextureIndex[Types(CHEMICAL_BLUE, CHEMICAL_YELLOW)]);
	}

	bool ChemicalFactory::RegisterCreateFunc(Types _types, CreateFunc _createFunc)
	{
		return m_CreateFuncs.insert(std::make_pair(_types, _createFunc)).second;
	}

	bool ChemicalFactory::UnRegisterCreateFunc(Types _types)
	{
		return m_CreateFuncs.erase(_types) == 1;
	}

	ChemicalBase* ChemicalFactory::Create(Types _types)
	{
		ChemicalBase* pChemicalBase = nullptr;

		auto itr = m_CreateFuncs.find(_types);

		if (itr != m_CreateFuncs.end())
			pChemicalBase = m_CreateFuncs[_types](m_TextureIndex[_types]);

		return pChemicalBase;
	}
}
