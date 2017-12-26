/**
 * @file	Rain.h
 * @brief	雨ギミッククラス定義
 * @author	morimoto
 */
#ifndef GAME_RAIN_H
#define GAME_RAIN_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "MultipleObject2DBase\MultipleObject2DBase.h"
#include "CollisionManager\CollisionBase\GimmickCollision\RainGimmickCollision\RainGimmickCollision.h"
#include "DirectX11\MultipleVertex2D\Dx11MultipleVertex2DUV.h"

#include <vector>


namespace Game
{
	/*** 雨ギミッククラス */
	class Rain : public MultipleObject2DBase
	{
	public:
		/*** 雨の品質(サイズ) */
		enum GRADE
		{
			LOW_GRADE,
			NORMAL_GRADE,
			HIGH_GRADE,
			GRADE_MAX
		};

		/*** コンストラクタ */
		Rain(D3DXVECTOR2 _pos, GRADE _grade);

		/*** デストラクタ */
		virtual ~Rain();

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

		/*** オブジェクトの更新 */
		virtual void Update();

		/*** オブジェクトの描画 */
		virtual void Draw();

	private:
		using GIMMICK_RECTANGLE = GimmickCollision::GIMMICK_RECTANGLE;

		/*** インスタンスの生成 */
		bool CreateInstanceBuffer();

		/*** インスタンスの解放 */
		void ReleaseInstanceBuffer();

		/*** 粒の生成処理 */
		void GenerateParticle();

		static const int m_GimmickMaxLow;		//!< 最低品質ギミックの最大値.
		static const int m_GimmickMaxNormal;	//!< 通常品質ギミックの最大値.
		static const int m_GimmickMaxHigh;		//!< 最大品質ギミックの最大値.
		static const float m_Gravity;	//!< 重力値.

		LPCTSTR		m_TextureName;	//!< 描画するテクスチャ名.
		LPCTSTR		m_TaskName;		//!< タスクの名前.
		int			m_GimmickNum;	//!< ギミックの個数.

		D3DXVECTOR2 m_RainPos;		//!< 雨の基準座標.
		GRADE		m_Grade;		//!< 雨の品質.
		int			m_Time;			//!< 雨ギミックの基準時間.
		int			m_GimmickMax;	//!< ギミック最大値.

		std::vector<D3DXVECTOR2>	m_Positions;	//!< ギミックの座標.
		std::vector<D3DXVECTOR2>	m_GimmickUV;	//!< ギミックのUV.
		std::vector<int>			m_Times;		//!< ギミックの時間.
		RainGimmickCollision*		m_pCollision;	//!< ギミックの当たり判定オブジェクト.

		Lib::Dx11::MultipleVertex2DUV*		m_pMultipleVertexUV;

	};
}


#endif // !GAME_RAIN_H
