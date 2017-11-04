/**
 * @file	ChipCollision.h
 * @brief	チップ衝突判定オブジェクトクラス定義
 * @author	morimoto
 */
#ifndef GAME_CHIPCOLLISION_H
#define GAME_CHIPCOLLISION_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\CollisionBase.h"


namespace Game
{
	/*** チップ衝突判定オブジェクトクラス */
	class ChipCollision : public CollisionBase
	{
	public:
		/*** 矩形データ構造体 */
		struct RECTANGLE
		{
			RECTANGLE() :
				Left(0),
				Top(0),
				Right(0),
				Bottom(0)
			{}

			RECTANGLE(float _left, float _top, float _right, float _bottom) :
				Left(_left),
				Top(_top),
				Right(_right),
				Bottom(_bottom)
			{}

			float Left;
			float Top;
			float Right;
			float Bottom;
		};

		/**
		 * コンストラクタ 
		 * @param[in] _id 当たり判定ID
		 */
		ChipCollision(int _id);

		/*** デストラクタ */
		virtual ~ChipCollision();

		/**
		 * Collide関数へのDispatch関数
		 * @param[in] _pOther 他オブジェクト
		 */
		virtual void Dispatch(CollisionBase* _pOther);

		/*** 空オブジェクトとの当たり判定を行う */
		virtual void Collide(EmptyCollision* _pOther);

		/*** 矩形オブジェクトとの当たり判定を行う */
		virtual void Collide(RectangleCollision* _pOther);

		/*** チップオブジェクトとの当たり判定を行う */
		virtual void Collide(ChipCollision* _pOther);

		/*** プレイヤーオブジェクトとの当たり判定を行う */
		virtual void Collide(PlayerCollision* _pOther);

		/**
		 * 矩形の追加
		 * @param[in] _rect 追加する矩形
		 */
		void AddRect(RECTANGLE _rect) { m_Rectangles.push_back(_rect); }

		/**
		 * 矩形の取得
		 * @param[in] _index 矩形のindex番号
		 * @return 矩形情報
		 */
		RECTANGLE GetRect(int _index) { return m_Rectangles[_index]; }

		/**
		 * 矩形の取得
		 * @return 矩形情報
		 */
		const std::vector<RECTANGLE>* GetRect(){ return &m_Rectangles; }

		/*** 矩形情報のクリア */
		void ClearRect() { m_Rectangles.clear(); }

	private:
		std::vector<RECTANGLE> m_Rectangles;	//!< 当たり判定用矩形.

	};
}


#endif // !GAME_CHIPCOLLISION_H
