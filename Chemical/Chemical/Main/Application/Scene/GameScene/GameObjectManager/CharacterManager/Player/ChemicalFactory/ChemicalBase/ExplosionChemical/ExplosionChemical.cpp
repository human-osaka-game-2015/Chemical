/**
 * @file   ExplosionChemical.cpp
 * @brief  ExplosionChemicalクラスの実装
 * @author kotani
 */
#include "ExplosionChemical.h"
#include "..\..\ChemicalFactory.h"
#include "Application\Scene\GameScene\GameDefine.h"
#include "Application\Scene\GameScene\CollisionManager\CollisionManager.h"
#include "..\..\..\..\..\GameDataManager\GameDataManager.h"

#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "DirectX11\AnimationManager\Dx11AnimationManager.h"
#include "DirectX11\AnimationManager\IAnimation\Dx11IAnimation.h"


namespace Game
{
	namespace
	{
		ChemicalBase* CreateExplosionChemical(int _textureIndex)
		{
			ChemicalBase* pChemical = new ExplosionChemical(_textureIndex);
			pChemical->Initialize();
			return pChemical;
		}

		const bool registered = ChemicalFactory::GetInstance().
			RegisterCreateFunc(
			ChemicalFactory::Types(CHEMICAL_BLUE, CHEMICAL_RED),
			CreateExplosionChemical);
	}

	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------

	ExplosionChemical::ExplosionChemical(int _textureIndex) :
		ChemicalBase(_textureIndex, CHEMICAL_EXPLOSION),
		m_Scale(1.f), 
		m_IsAnimation(false)
	{
		m_Size = D3DXVECTOR2(40, 40);
		m_pExplosionCollision = new ExplosionCollision(EXPLOSION_COLLISION_ID);
		m_pDrawTask->SetPriority(GAME_DRAW_EFFECT);
		pControl[NORMAL_CONTROL] = &ExplosionChemical::NormalControl;
		pControl[EXPLOSION_CONTROL] = &ExplosionChemical::ExplosionControl;
		m_ControlState = NORMAL_CONTROL;
		//本素材が無いので.
		m_ExplosionTextureIndex = m_TextureIndex;

		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->LoadTexture(
			"Resource\\GameScene\\Texture\\Explosion2.png", 
			&m_TextureIndex2);
		SINGLETON_INSTANCE(Lib::Dx11::AnimationManager)->LoadAnimation(
			"Resource\\GameScene\\Animation\\Explosion.anim",
			&m_AnimationIndex);

		SINGLETON_INSTANCE(Lib::Dx11::AnimationManager)->GetAnimation(m_AnimationIndex)->SetAnimationPattern(
			Lib::Dx11::IAnimation::ONE_ANIMATION);
		SINGLETON_INSTANCE(Lib::Dx11::AnimationManager)->GetAnimation(m_AnimationIndex)->SetAnimationSpeed(0.25f);
		SINGLETON_INSTANCE(Lib::Dx11::AnimationManager)->GetAnimation(m_AnimationIndex)->AnimationStart();
	}

	ExplosionChemical::~ExplosionChemical()
	{
		SINGLETON_INSTANCE(Lib::Dx11::AnimationManager)->ReleaseAnimation(m_AnimationIndex);
		SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->ReleaseTexture(m_TextureIndex2);

		SafeDelete(m_pExplosionCollision);
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------

	void ExplosionChemical::UpdateStartUp()
	{
		if (!m_IsSprinkle) return;

		if (m_pCollision->GetHit())
		{
			m_ControlState = EXPLOSION_CONTROL;
			SINGLETON_INSTANCE(CollisionManager)->RemoveCollision(m_pCollision);
			SINGLETON_INSTANCE(CollisionManager)->AddCollision(m_pExplosionCollision);
		}

		if (m_IsAnimation)
		{
			m_IsAnimation = false;
			SINGLETON_INSTANCE(Lib::Dx11::AnimationManager)->GetAnimation(m_AnimationIndex)->AnimationStart();
			m_IsSprinkle = false;
			m_Scale = 1.f;
			m_ControlState = NORMAL_CONTROL;
			SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
			SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
			SINGLETON_INSTANCE(CollisionManager)->RemoveCollision(m_pExplosionCollision);
		}
	}

	void ExplosionChemical::Update()
	{
		(this->*pControl[m_ControlState])();
	}

	void ExplosionChemical::Draw()
	{
		D3DXVECTOR2 Pos = m_Pos;
		Pos.x -= SINGLETON_INSTANCE(GameDataManager)->GetScreenPos().x;

		m_pVertex->ShaderSetup();
		m_pVertex->WriteVertexBuffer();
		m_pVertex->WriteConstantBuffer(&Pos, &D3DXVECTOR2(m_Scale, m_Scale));
		m_pVertex->Draw();
	}

	void ExplosionChemical::Sprinkle(const D3DXVECTOR2& _pos, bool _isLeft)
	{
		if (m_IsSprinkle) return;

		if (m_ChemicalData.Remain >= 10)
		{
			m_ChemicalData.Remain -= 10;
			m_ChemicalData.Remain = (std::max)(0.f, m_ChemicalData.Remain);

			m_IsLeft = _isLeft;
			m_Pos = _pos;
			m_Acceleration = -7;
			m_IsSprinkle = true;
			SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->AddTask(m_pDrawTask);
			SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);
			SINGLETON_INSTANCE(CollisionTaskManager)->AddTask(m_pCollisionTask);
			SINGLETON_INSTANCE(CollisionManager)->AddCollision(m_pCollision);
		}
	}

	//----------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------

	void ExplosionChemical::NormalControl()
	{
		m_pVertex->SetAnimation(nullptr);
		m_pVertex->SetUV(&D3DXVECTOR2(0, 0), &D3DXVECTOR2(1.0, 1.0));
		m_pVertex->WriteVertexBuffer();
		m_pVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_ExplosionTextureIndex));

		m_Acceleration = (std::min)(m_Acceleration, 23.f);

		m_Pos.x += m_IsLeft ? -10.f : 10.f;
		m_Pos.y += (m_Acceleration += m_Gravity);

		RectangleCollisionBase::RECTANGLE Rectangle(
			m_Pos.x - m_Size.x / 2,
			m_Pos.y - m_Size.y / 2,
			m_Pos.x + m_Size.x / 2,
			m_Pos.y + m_Size.y / 2);
		m_pCollision->SetRect(Rectangle);
		m_pCollision->ResetCollision();
	}

	void ExplosionChemical::ExplosionControl()
	{
		m_IsAnimation = SINGLETON_INSTANCE(Lib::Dx11::AnimationManager)->GetAnimation(m_AnimationIndex)->Update();
		m_pVertex->SetAnimation(
			SINGLETON_INSTANCE(Lib::Dx11::AnimationManager)->GetAnimation(m_AnimationIndex));
		m_pVertex->SetTexture(
			SINGLETON_INSTANCE(Lib::Dx11::TextureManager)->GetTexture(m_TextureIndex2));

		switch (m_ChemicalData.Grade)
		{
			case GRADE_NORMAL:
				m_Scale += 0.15f;
				break;
			case GRADE_GOOD:
				m_Scale += 0.25f;
				break;
			case GRADE_GREAT:
				m_Scale += 0.35f;
				break;
		}
		m_pExplosionCollision->SetCircle(Circle(m_Pos, 40 * m_Scale));
	}
}
