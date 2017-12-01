/**
 * @file   ChemicalBase.h
 * @brief  ChemicalBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAME_CHEMICALBASE_H
#define GAME_CHEMICALBASE_H
#include "Object2DBase\Object2DBase.h"
#include "Application\Scene\GameScene\CollisionTask\CollisionTask.h"
#include "Application\Scene\GameScene\CollisionManager\CollisionBase\ChemicalCollision\ChemicalCollision.h"

namespace Game
{
	class ChemicalCollision;

	class ChemicalBase : public Object2DBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] 使用するテクスチャのインデックス
		 */
		ChemicalBase(int _textureIndex, const D3DXVECTOR2& _pos, bool _isLeft);

		/*** デストラクタ */
		virtual ~ChemicalBase();

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

		/*** オブジェクトの当たり判定更新 */
		virtual void CollisionTaskUpdate();

		/*** 更新処理 */
		virtual void Update();

		/*** 描画処理 */
		virtual void Draw();

		/**
		 * 当たっているかのflagを取得する 
		 * @return 当たっていたらtrue 当たっていなかったらfalse 
		 */
		bool GetIsHit()
		{
			return m_pCollision->GetHit();
		}

	protected:
		static const float m_Gravity;
		
		/*** 制御用関数ポインタ */
		void (ChemicalBase::*pControl)();

		CollisionTask*     m_pCollisionTask;
		ChemicalCollision* m_pCollision;
		float			   m_Acceleration;
		bool			   m_IsLeft;
		
	};
}


#endif
