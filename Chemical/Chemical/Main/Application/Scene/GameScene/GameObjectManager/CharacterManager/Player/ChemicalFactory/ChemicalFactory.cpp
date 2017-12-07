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
	//----------------------------------------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------------------------------------

	bool ChemicalFactory::Initialize()
	{
		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\GameScene\\Texture\\Explosion.png",
			&m_TextureIndex[Types(ChemicalBase::BLUE, ChemicalBase::RED)])) return false;

		return true;
	}

	void ChemicalFactory::Finalize()
	{
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->
			ReleaseTexture(m_TextureIndex[Types(ChemicalBase::BLUE, ChemicalBase::RED)]);
	}

	bool ChemicalFactory::RegisterCreateFunc(Types _types, CreateFunc _createFunc)
	{
		return m_CreateFuncs.insert(std::make_pair(_types, _createFunc)).second;
	}

	bool ChemicalFactory::UnRegisterCreateFunc(Types _types)
	{
		return m_CreateFuncs.erase(_types) == 1;
	}

	ChemicalBase* ChemicalFactory::Create(Types _types, const D3DXVECTOR2& _pos, bool _isLeft)
	{
		ChemicalBase* pChemicalBase = nullptr;

		pChemicalBase = m_CreateFuncs[_types](m_TextureIndex[_types], _pos, _isLeft);

		return pChemicalBase;
	}
}
