/**
* @file	WalkEnemy.h
* @brief	エッグエネミークラス定義
* @author	fujioka
*/
#ifndef GAME_EGGENEMY_H
#define GAME_EGGENEMY_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Application\Scene\GameScene\GameObjectManager\CharacterManager\EnemyManager\EnemyBase\EnemyBase.h"
#include "Application\Scene\GameScene\CollisionTask\CollisionTask.h"

namespace Game
{
	class EnemyUI;
	/*** ウォークエネミークラス */
	class EggEnemy : public EnemyBase
	{
	public:
		/*** コンストラクタ */
		EggEnemy(D3DXVECTOR2* _pPosotion,int EnemyType);

		/*** デストラクタ */
		virtual ~EggEnemy();

		/**
		* 初期化処理
		* @return 初期化に成功したらtrue 失敗したらfalse
		*/
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

		/*** オブジェクトの当たり判定更新*/
		virtual void CollisionTaskUpdate();

		/*** 更新処理 */
		virtual void Update();
		/*** 描画処理 */
		virtual void Draw();

		bool GetCompletion(){ return m_Completion; };

		int GetEnemyType(){ return m_EnemyType; };

		D3DXVECTOR2 GetPosition(){ return m_Pos; };
	private:

		int						m_AnimationIndex;
		int						m_EnemyType;

		bool					m_AiEnable;
		bool					m_OldEnable;

		bool					m_Completion;

		Lib::Dx11::IAnimation*	m_pWalkAnimation;
		CollisionTask*			m_pCollisionTask;
		EnemyUI*				m_EnemyUI;

		void GravityUpdate();

		bool AiEnable();
		void EnemyAi();
		void DamageDecision();

		
	};
}


#endif
