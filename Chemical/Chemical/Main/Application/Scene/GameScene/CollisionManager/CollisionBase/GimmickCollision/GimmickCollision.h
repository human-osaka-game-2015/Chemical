/**
 * @file	GimmickCollision.h
 * @brief	ギミック当たり判定クラス定義
 * @author	morimoto
 */
#ifndef GAME_GIMMICKCOLLISION_H
#define GAME_GIMMICKCOLLISION_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\CollisionBase.h"


namespace Game
{
	/*** ギミック当たり判定クラス */
	class GimmickCollision : public CollisionBase
	{
	public:
		/*** 矩形データ構造体 */
		struct GIMMICK_RECTANGLE
		{
			GIMMICK_RECTANGLE() :
				Left(0),
				Top(0),
				Right(0),
				Bottom(0),
				ID(0)
			{}

			GIMMICK_RECTANGLE(int _id) :
				Left(0),
				Top(0),
				Right(0),
				Bottom(0),
				ID(_id)
			{}

			GIMMICK_RECTANGLE(float _left, float _top, float _right, float _bottom, int _id) :
				Left(_left),
				Top(_top),
				Right(_right),
				Bottom(_bottom),
				ID(_id)
			{}

			float Left;
			float Top;
			float Right;
			float Bottom;
			int	ID;
		};

		/*** 衝突時のデータ */
		struct COLLISION_DATA
		{
			COLLISION_DATA(int _otherId, int _id) :
				OtherId(_otherId),
				Id(_id)
			{}

			int OtherId;	//!< 衝突した外部オブジェクトID.
			int Id;			//!< オブジェクトID.
		};

		/**
		 * コンストラクタ 
		 * @param[in] _id 当たり判定ID
		 */
		GimmickCollision(int _id);

		/*** デストラクタ */
		virtual ~GimmickCollision();

		/**
		 * Collide関数へのDispatch関数
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Dispatch(CollisionBase* _pOther);

		/**
		 * 当たり判定矩形の数を変更
		 * @param[in] _size サイズ
		 */
		void ResizeRect(int _size)
		{
			m_Rectangles.resize(_size);
		}

		/**
		 * 矩形の追加
		 * @param[in] _rect 追加する矩形
		 * @return 矩形のID
		 */
		int AddRect(GIMMICK_RECTANGLE _rect)
		{ 
			int ID = m_Rectangles.size();
			m_Rectangles.push_back(_rect); 
			return ID;
		}

		/**
		 * 矩形の取得
		 * @param[in] _index 矩形のID
		 * @return 矩形情報
		 */
		GIMMICK_RECTANGLE GetRect(int _id)
		{
			return m_Rectangles[_id]; 
		}

		/**
		 * 矩形の取得
		 * @return 矩形情報
		 */
		std::vector<GIMMICK_RECTANGLE>* GetRect() { return &m_Rectangles; }

		/*** 矩形情報のクリア */
		void ClearRect() { m_Rectangles.clear(); }

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

	protected:
		std::vector<GIMMICK_RECTANGLE>	m_Rectangles;	//!< 当たり判定用矩形.
		std::queue<COLLISION_DATA>		m_CollisionData;//!< 衝突時の情報	キュー.

	};
}


#endif // !GAME_GIMMICKCOLLISION_H
