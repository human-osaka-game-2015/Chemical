/**
 * @file	BeltConveyorGimmickCollision.h
 * @brief	ベルトコンベアギミック当たり判定クラス定義
 * @author	morimoto
 */
#ifndef GAME_BELTCONVEYORGIMMICKCOLLISION_H
#define GAME_BELTCONVEYORGIMMICKCOLLISION_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\GimmickCollision.h"

#include <Windows.h>


namespace Game
{
	/*** ベルトコンベアギミック当たり判定クラス */
	class BeltConveyorGimmickCollision : public GimmickCollision
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _id 当たり判定ID
		 */
		BeltConveyorGimmickCollision(int _id);

		/*** デストラクタ */
		~BeltConveyorGimmickCollision();

		/**
		 * Collide関数へのDispatch関数
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Dispatch(CollisionBase* _pOther);

		/*** プレイヤーオブジェクトとの当たり判定を行う */
		virtual void Collide(PlayerCollision* _pOther);

		/**
		 * オブジェクトの向き情報を設定する 
		 * @param[in] _isLeft オブジェクトの向き情報 0の場合がLeft 1の場合がRight
		 */
		void AddIsLeft(BYTE _isLeft){ m_IsLeft.push_back(_isLeft); }

		/*** オブジェクトの向き情報を取得する */
		std::vector<BYTE>* GetIsLeft(){ return &m_IsLeft; }

		/*** オブジェクトの向き情報を削除 */
		void ClearIsLeft(){ m_IsLeft.clear(); }

	private:
		std::vector<BYTE> m_IsLeft;	//!< オブジェクトの向き情報.

	};
}


#endif // !GAME_BELTCONVEYORGIMMICKCOLLISION_H
