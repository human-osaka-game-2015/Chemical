/**
 * @file	EnemyGenerator.cpp
 * @brief	エネミー生成ギミッククラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EnemyGenerator.h"

#include "..\..\StageGimmickManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	EnemyGenerator::EnemyGenerator() :
		StageGimmickBase(ENEMYGENERATOR_COLLISION_ID, "", "EnemyGenerator")
	{
	}

	EnemyGenerator::~EnemyGenerator()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool EnemyGenerator::Initialize()
	{
		return true;
	}

	void EnemyGenerator::Finalize()
	{
	}

	void EnemyGenerator::Update()
	{
	}

	void EnemyGenerator::Draw()
	{
	}

	void EnemyGenerator::AddGimmick(int _x, int _y)
	{
		float X = StageGimmickManager::m_DefaultGimmickSize.x;
		float Y = StageGimmickManager::m_DefaultGimmickSize.y;

		D3DXVECTOR2 Pos(_x * X + X / 2, _y * Y + Y / 2);

		RECTANGLE Rect(
			Pos.x - X / 2,
			Pos.y - Y / 2,
			Pos.x + X / 2,
			Pos.y + Y / 2);

		m_Positions.emplace_back(Pos);

		m_Rectangles.emplace_back(Rect);
		m_pCollision->AddRect(Rect);
		m_GimmickNum++;	// ギミックの個数をカウント.
	}

	void EnemyGenerator::ClearChip()
	{
		m_Rectangles.clear();
		m_Positions.clear();
	}
}
