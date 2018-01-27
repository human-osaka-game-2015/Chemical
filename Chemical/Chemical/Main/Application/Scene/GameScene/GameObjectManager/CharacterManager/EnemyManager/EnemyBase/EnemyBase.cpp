/**
* @file	Enemy.cpp
* @brief	エネミーベースクラス実装
* @author	fujioka
*/

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EnemyBase.h"
#include "Application\Scene\GameScene\GameDefine.h"
#include "..\..\..\GameDataManager\GameDataManager.h"
#include "..\..\..\..\CollisionManager\CollisionManager.h"
#include "Application\Scene\GameScene\CollisionManager\CollisionBase\EnemyCollision\EnemyCollision.h"
#include "WalkEnemy\EnemyUI\EnemyUI.h"

#include "DirectX11\AnimationManager\Dx11AnimationManager.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "InputDeviceManager\InputDeviceManager.h"
#include "InputDeviceManager\KeyDevice\KeyDevice.h"
#include "TaskManager\TaskManager.h"

namespace Game
{
	const float EnemyBase::m_Gravity = 0.8f;

	const EnemyBase::ENABLEAREA EnemyBase::m_EnableArea = { -600, 1320, -1150, 2480 };

	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------

	EnemyBase::EnemyBase() :
		m_IsLeft(true),
		m_pCollision(nullptr),
		m_Acceleration(0),
		m_IsLanding(false),
		m_IsAlive(true)
	{

	}

	EnemyBase::~EnemyBase()
	{

	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------

	bool EnemyBase::Initialize()
	{
		return true;
	}

	void EnemyBase::Finalize()
	{
	}

	void EnemyBase::Update()
	{
	}

	void EnemyBase::Draw()
	{
	}

	void EnemyBase::EnemyAi()
	{
	}

	void EnemyBase::DamageDecision()
	{
	}

}
