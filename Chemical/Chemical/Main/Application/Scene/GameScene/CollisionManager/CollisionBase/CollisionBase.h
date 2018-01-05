/**
 * @file	CollisionBase.h
 * @brief	当たり判定基底クラス定義
 * @author	morimoto
 */
#ifndef GAME_COLLISIONBASE_H
#define GAME_COLLISIONBASE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\GameDefine.h"

#include <queue>


namespace Game
{
	class EmptyCollision;
	class ChipCollision;
	class GimmickCollision;
	class FireGimmickCollision;
	class MushroomGimmickCollision;
	class WoodGimmickCollision;
	class RecoveryGimmickCollision;
	class EnemyGeneratorCollision;
	class ButtonGimmickCollision;
	class GateGimmickCollision;
	class RainCloudGimmickCollision;
	class RainGimmickCollision;
	class PlayerCollision;
	class ChemicalCollision;
	class ExplosionCollision;

	/*** 当たり判定基底クラス */
	class CollisionBase
	{
	public:
		/**
		 * コンストラクタ 
		 * @param[in] _id 当たり判定ID
		 */
		CollisionBase(int _id);

		/*** デストラクタ */
		virtual ~CollisionBase();

		/**
		 * Collide関数へのDispatch関数
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Dispatch(CollisionBase* _pOther) = 0;

		/*** 空オブジェクトとの当たり判定を行う */
		virtual void Collide(EmptyCollision* _pOther);

		/*** チップオブジェクトとの当たり判定を行う */
		virtual void Collide(ChipCollision* _pOther);

		/*** ギミックオブジェクトとの当たり判定を行う */
		virtual void Collide(GimmickCollision* _pOther);

		/*** 火ギミックオブジェクトとの当たり判定を行う */
		virtual void Collide(FireGimmickCollision* _pOther);

		/*** キノコギミックオブジェクトとの当たり判定を行う */
		virtual void Collide(MushroomGimmickCollision* _pOther);

		/*** 木ギミックオブジェクトとの当たり判定を行う */
		virtual void Collide(WoodGimmickCollision* _pOther);

		/*** 回復ギミックオブジェクトとの当たり判定を行う */
		virtual void Collide(RecoveryGimmickCollision* _pOther);

		/*** エネミー生成ギミックオブジェクトとの当たり判定を行う */
		virtual void Collide(EnemyGeneratorCollision* _pOther);

		/*** ボタンギミックオブジェクトとの当たり判定を行う */
		virtual void Collide(ButtonGimmickCollision* _pOther);

		/*** 門ギミックオブジェクトとの当たり判定を行う */
		virtual void Collide(GateGimmickCollision* _pOther);

		/*** 雨雲ギミックオブジェクトとの当たり判定を行う */
		virtual void Collide(RainCloudGimmickCollision* _pOther);

		/*** 雨ギミックオブジェクトとの当たり判定を行う */
		virtual void Collide(RainGimmickCollision* _pOther);

		/*** プレイヤーオブジェクトとの当たり判定を行う */
		virtual void Collide(PlayerCollision* _pOther);

		/*** 薬品との当たり判定を行う */
		virtual void Collide(ChemicalCollision* _pOther);

		/*** 薬品との当たり判定を行う */
		virtual void Collide(ExplosionCollision* _pOther);

		/**
		 * 当たり判定ID取得
		 * @return 当たり判定ID
		 */
		int GetCollisionID() { return m_CollisionID; }

	private:
		static unsigned int m_CollisionBaseNum;	//!< 当たり判定オブジェクトの数.

		int					m_CollisionID;	//!< 当たり判定オブジェクトID.
		int					m_ID;			//!< ユニークID.

	};
}


#endif // !GAME_COLLISIONBASE_H
