/**
* @file	WalkEnemy.h
* @brief	スロウエネミークラス定義
* @author	fujioka
*/
#ifndef GAME_BULLET_H
#define GAME_BULLET_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Object2DBase\Object2DBase.h"
#include "Application\Scene\GameScene\CollisionTask\CollisionTask.h"

namespace Game
{
	class EnemyCollision;
	/*** スロウエネミークラス */
	class Bullet : public Object2DBase
	{
	public:
		/*** コンストラクタ */
		Bullet(D3DXVECTOR2* _pPosotion,int* _Speed);

		/*** デストラクタ */
		virtual ~Bullet();

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

		bool GedEnable(){ return m_IsEnable; };

	private:

		int						m_Frame;
		int						m_Speed;
		bool					m_IsEnable;

		static const int		m_Interval;

		EnemyCollision*			m_pCollision;
		CollisionTask*			m_pCollisionTask;

	};
}


#endif
