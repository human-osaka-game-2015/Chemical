/**
 * @file	2D四角形衝突判定オブジェクトクラス定義
 * @brief	CollisionQuad2D.h
 * @author	morimoto
 */
#ifndef LIB_COLLISIONQUAD2D_H
#define LIB_COLLISIONQUAD2D_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <D3DX11.h>
#include <D3DX10.h>
#include <vector>
#include <string>

#include "..\CollisionBase.h"


namespace Lib
{
	/**
	 * 2D四角形衝突判定オブジェクトクラス
	 */
	class CollisionQuad2D : public CollisionBase
	{
	public:
		/**
		 * 矩形のあたり判定の位置
		 */
		enum HIT
		{
			TOP_HIT = 1,	//!< 上部が当たっている.
			LEFT_HIT = 2,	//!< 左側が当たっている.
			RIGHT_HIT = 4,	//!< 右側が当たっている.
			BOTTOM_HIT = 8	//!< 画部が当たっている.
		};

		/**
		 * 衝突判定オブジェクトの情報を格納する構造体
		 */
		struct COLLISION_INFO
		{
			LPCSTR	pName;		//!< 当たったオブジェクトの名前.
			BYTE	HitData;	//!< 当たった部分.
		};

		/**
		 * コンストラクタ
		 */
		CollisionQuad2D();

		/**
		 * デストラクタ
		 */
		virtual ~CollisionQuad2D();

		/**
		 * 衝突オブジェクトの情報を追加する
		 * @param[in] _pName 衝突したオブジェクトの名前
		 */
		void AddCollisionInfo(COLLISION_INFO* _pInfo)
		{
			m_CollisionInfos.push_back(*_pInfo);
		}

		/**
		 * 衝突オブジェクトの情報を取得する
		 * @return 衝突したオブジェクトの名前が格納されたコンテナ
		 */
		std::vector<COLLISION_INFO>* GetCollisionInfo()
		{
			return &m_CollisionInfos;
		}

		/**
		 * 衝突オブジェクトの情報を破棄する
		 */
		void ClearCollisionInfo()
		{
			m_CollisionInfos.clear();
		}

		/**
		 * あたり判定座標の設定
		 * @param[in] _pPos 設定する座標
		 */
		inline void SetPos(D3DXVECTOR2* _pPos)
		{
			m_Pos = *_pPos;
		}

		/**
		 * あたり判定座標の取得
		 * @return あたりの座標
		 */
		inline const D3DXVECTOR2& GetPos()
		{
			return m_Pos;
		}

		/**
		 * あたり判定サイズの設定
		 * @param[in] _pSize 設定するサイズ
		 */
		inline void SetSize(D3DXVECTOR2* _pSize)
		{
			m_Size = *_pSize;
		}

		/**
		 * あたり判定サイズの取得
		 * @return あたりのサイズ
		 */
		inline const D3DXVECTOR2& GetSize()
		{
			return m_Size;
		}

		/**
		 * オブジェクトの名前を設定
		 * @param[in] _pName 設定する名前
		 */
		inline void SetName(LPCTSTR _pName)
		{
			m_Name = _pName;
		}

		/**
		 * オブジェクトの名前を取得
		 * @return オブジェクトの名前
		 */
		inline LPCTSTR GetName()
		{
			return m_Name.c_str();
		}


	private:
		D3DXVECTOR2		m_Pos;	//!< あたり判定の座標.
		D3DXVECTOR2		m_Size;	//!< あたり判定のサイズ.
		std::string		m_Name;	//!< あたり判定オブジェクトの名前.

		std::vector<COLLISION_INFO> m_CollisionInfos;	//!< 衝突したオブジェクトの情報.

	};
}


#endif // !LIB_COLLISIONQUAD2D_H
