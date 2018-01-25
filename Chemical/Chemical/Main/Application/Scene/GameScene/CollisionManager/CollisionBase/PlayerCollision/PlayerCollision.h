/**
 * @file   PlayerCollision.h
 * @brief  PlayerCollisionクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAME_PLAYER_COLLISION_H
#define GAME_PLAYER_COLLISION_H

#include "..\RectangleCollisionBase\RectangleCollisionBase.h"
#include "GameObjectManager\CharacterManager\Player\ChemicalFactory\ChemicalBase\ChemicalBase.h"
#include <D3DX11.h>
#include <D3DX10.h>

namespace Game
{
	class PlayerCollision : public RectangleCollisionBase
	{
	public:
		/*** 衝突時のデータ */
		struct COLLISION_DATA
		{
			COLLISION_DATA(int _otherId, int _id, ChemicalBase::GRADE _grade) :
				OtherId(_otherId),
				Id(_id),
				Grade(_grade)
			{}

			int OtherId;	//!< 衝突した外部オブジェクトID.
			int Id;			//!< オブジェクトID.
			ChemicalBase::GRADE Grade;
		};

		/*** コンストラクタ */
		PlayerCollision();

		/*** デストラクタ */
		virtual ~PlayerCollision();

		/**
		 * Collide関数へのDispatch関数
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Dispatch(CollisionBase* _pOther);

		/**
		 * チップオブジェクトとの当たり判定を行う 
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Collide(ChipCollision* _pOther);

		/**
		 * きのこと当たり判定を行う 
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Collide(MushroomGimmickCollision* _pOther);

		/**
		 * 回復アイテムと当たり判定を行う
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Collide(RecoveryGimmickCollision* _pOther);

		/**
		 * 門と当たり判定を行う
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Collide(GateGimmickCollision* _pOther);

		/**
		 * ブロックとの当たり判定を行う 
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Collide(BlockGimmickCollision* _pOther);

		/**
		 * ベルトコンベアとの当たり判定を行う
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Collide(BeltConveyorGimmickCollision* _pOther);

		/**
		 * ワープオブジェクトとの当たり判定を行う
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Collide(WarpGimmickCollision* _pOther);

		/**
		 * 移動速度上昇オブジェクトとの当たり判定を行う
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Collide(SpeedUpGimmickCollision* _pOther);

		/**
		* 衝突時のデータをキーにプッシュ
		* @param[in] _data 衝突データ
		*/
		void PushCollisionData(COLLISION_DATA _data)
		{
			m_CollisionData.push(_data);
		}

		/***
		* 衝突時のデータをポップ
		* @return 衝突データ
		*/
		COLLISION_DATA PopCollisionData()
		{
			COLLISION_DATA Data = m_CollisionData.front();
			m_CollisionData.pop();
			return Data;
		}

		/**
		* 衝突データの中身が空かどうか
		* @return 空であればtrue
		*/
		bool IsCollisionDataEmpty()
		{
			return m_CollisionData.empty();
		}


		/*** 当たり判定差分の初期化 */
		void ResetCollisionDiff(){ m_CollisionDiff = D3DXVECTOR2(0, 0); }

		void ResetConveyorMove(){ m_ConveyorMove = D3DXVECTOR2(0,0); }

		void ResetWarpHit()
		{
			m_IsOldWarpHit = m_IsWarpHit;
			m_IsWarpHit = false; 
		}

		/**
		 * 当たり判定の差分を取得する
		 * @return _collisionDiff 当たった差分
		 */
		D3DXVECTOR2 GetCollisionDiff(){ return m_CollisionDiff; }

		D3DXVECTOR2 GetConveyorMove(){ return m_ConveyorMove; }

		bool GetIsWarp(){ return m_IsWarp; }

	private:
		D3DXVECTOR2				   m_ConveyorMove;  //!< ベルトコンベアを踏んだ際の移動量
		D3DXVECTOR2				   m_CollisionDiff; //!< 当たった時の差分
		std::queue<COLLISION_DATA> m_CollisionData;//!< 衝突時の情報	キュー.
		bool					   m_IsWarpHit;
		bool					   m_IsOldWarpHit;
		bool					   m_IsWarp; //!< ワープ出来るか?

	};
}


#endif
