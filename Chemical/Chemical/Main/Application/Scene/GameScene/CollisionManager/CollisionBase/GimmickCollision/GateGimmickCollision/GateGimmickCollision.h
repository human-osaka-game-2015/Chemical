/**
 * @file	GateGimmickCollision.h
 * @brief	門ギミック当たり判定クラス定義
 * @author	morimoto
 */
#ifndef GAME_GATEGIMMICKCOLLISION_H
#define GAME_GATEGIMMICKCOLLISION_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\GimmickCollision.h"

#include <Windows.h>


namespace Game
{
	/*** 門ギミック当たり判定クラス */
	class GateGimmickCollision : public GimmickCollision
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _id 当たり判定ID
		 */
		GateGimmickCollision(int _id);

		/*** デストラクタ */
		virtual ~GateGimmickCollision();

		/**
		 * Collide関数へのDispatch関数
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Dispatch(CollisionBase* _pOther);

		/*** 活性状態フラグ追加 */
		void AddIsActive(BYTE _isActive){ m_IsActives.push_back(_isActive); }

		/*** 活性状態フラグ取得 */
		std::vector<BYTE>* GetIsActive(){ return &m_IsActives; }

		/*** 活性状態フラグの削除 */
		void ClearIsActive(){ m_IsActives.clear(); }

	private:
		std::vector<BYTE>	m_IsActives;	//!< 当たり判定が活性状態か.

	};
}


#endif // !GAME_GATEGIMMICKCOLLISION_H
