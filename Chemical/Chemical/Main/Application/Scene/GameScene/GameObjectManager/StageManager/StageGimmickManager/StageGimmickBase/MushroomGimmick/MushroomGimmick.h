/**
 * @file	MushroomGimmick.h
 * @brief	キノコギミッククラス定義
 * @author	morimoto
 */
#ifndef GAME_MUSHROOMGIMMICK_H
#define GAME_MUSHROOMGIMMICK_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\StageGimmickBase.h"
#include "CollisionManager\CollisionBase\GimmickCollision\MushroomGimmickCollision\MushroomGimmickCollision.h"
#include "DirectX11\MultipleVertex2D\Dx11MultipleVertex2DUV.h"


namespace Game
{
	/*** キノコギミッククラス */
	class MushroomGimmick : public StageGimmickBase
	{
	public:
		/*** コンストラクタ */
		MushroomGimmick();

		/*** デストラクタ */
		virtual ~MushroomGimmick();

		/* 
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

		/*** 更新処理 */
		virtual void Update();

		/*** 描画処理 */
		virtual void Draw();

		/**
		 * ギミックの追加 
		 * @param[in] _x 追加するチップのx位置
		 * @param[in] _y 追加するチップのy位置
		 */
		virtual void AddGimmick(int _x, int _y);

		/*** チップのクリア */
		virtual void ClearChip();

		/*** インスタンスバッファの生成 */
		virtual bool CreateInstanceBuffer();

		/*** インスタンスバッファの解放 */
		virtual void ReleaseInstanceBuffer();

	private:
		using GIMMICK_RECTANGLE = GimmickCollision::GIMMICK_RECTANGLE;

		static const D3DXVECTOR2 m_MushroomSize;	//!< キノコのサイズ.

		std::vector<D3DXVECTOR2>			m_Positions;	//!< ギミックの座標.
		std::vector<D3DXVECTOR2>			m_GimmickUV;	//!< ギミックのUV.
		MushroomGimmickCollision*			m_pCollision;	//!< ギミックの当たり判定オブジェクト.

		std::vector<D3DXVECTOR2>			m_Positions2;	//!< 変化後ギミックの座標.
		std::vector<D3DXVECTOR2>			m_GimmickUV2;	//!< 変化後ギミックのUV.
		MushroomGimmickCollision*			m_pCollision2;	//!< 変化後ギミックの当たり判定オブジェクト.	

		Lib::Dx11::MultipleVertex2DUV*		m_pMultipleVertexUV;
		Lib::Dx11::MultipleVertex2DUV*		m_pMultipleVertexUV2;

		int									m_GimmickNum2;

	};
}


#endif // !GAME_MUSHROOMGIMMICK_H
