/**
* @file	EnemyBase.h
* @brief	エネミーベース定義
* @author	fujioka
*/
#ifndef GAME_ENEMYBASE_H
#define GAME_ENEMYBASE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Object2DBase\Object2DBase.h"

namespace Game
{
	class EnemyCollision;
	/*** エネミーベースクラス */
	class EnemyBase : public Object2DBase
	{
	public:
		/*** コンストラクタ */
		EnemyBase();

		/*** デストラクタ */
		virtual ~EnemyBase();

		/**
		* 初期化処理
		* @return 初期化に成功したらtrue 失敗したらfalse
		*/
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

		/*** オブジェクトの当たり判定更新*/
		virtual void CollisionTaskUpdate(){};

		/*** 更新処理 */
		virtual void Update();

		/*** 描画処理 */
		virtual void Draw();

		int GetAttack(){ return m_Attack; };

		int GetHealth(){ return m_Health; };

		D3DXVECTOR2 GetSize(){ return m_CollisionSize; };

		D3DXVECTOR2 GetPosition(){ return m_Pos; };
		
		bool GetIsAlive(){ return m_IsAlive; };

	protected:

		struct ENABLEAREA
		{
			int Top;
			int Bottom;
			int Left;
			int Right;
			
		};

		static const float m_Gravity;
	

		static const ENABLEAREA m_EnableArea;

		bool m_IsAlive;

		int m_Health;
		int m_Attack;
		D3DXVECTOR2 m_Speed;

		EnemyCollision*			m_pCollision;

		float					m_Acceleration;
		bool					m_IsLeft;
		bool					m_IsLanding; //!< 着地しているか?
		D3DXVECTOR2				m_CollisionSize;

		virtual void EnemyAi() = 0;
		virtual void DamageDecision() = 0;

	};
}


#endif
