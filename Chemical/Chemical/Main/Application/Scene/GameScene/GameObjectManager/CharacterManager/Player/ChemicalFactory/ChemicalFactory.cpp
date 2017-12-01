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
	ChemicalFactory::ChemicalFactory()
	{
	}

	ChemicalFactory::~ChemicalFactory()
	{
	}


	//----------------------------------------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------------------------------------

	bool ChemicalFactory::Initialize()
	{
		if (!SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\GameScene\\Texture\\Explosion.png",
			&m_TextureIndex[EXPLOSION])) return false;

		return true;
	}

	void ChemicalFactory::Finalize()
	{
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex[EXPLOSION]);
	}

	ChemicalBase* ChemicalFactory::Create(Type _type1, Type _type2,const D3DXVECTOR2& _pos, bool _isLeft)
	{
		ChemicalBase* pChemicalBase = nullptr;

		if ((_type1 == RED  && _type2 == BLUE) ||
			(_type1 == BLUE && _type2 == RED) )
		{
			pChemicalBase = new ExplosionChemical(m_TextureIndex[EXPLOSION], _pos, _isLeft);
			pChemicalBase->Initialize();
		}

		return pChemicalBase;
	}
}
