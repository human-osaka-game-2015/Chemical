/**
 * @file	WoodGimmick.h
 * @brief	木ギミッククラス定義
 * @author	morimoto
 */
#ifndef GAME_WOODGIMMICK_H
#define GAME_WOODGIMMICK_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\StageGimmickBase.h"
#include "CollisionManager\CollisionBase\GimmickCollision\WoodGimmickCollision\WoodGimmickCollision.h"
#include "DirectX11\MultipleVertex2D\Dx11MultipleVertex2DUV.h"


namespace Game
{
	/*** 木ギミッククラス */
	class WoodGimmick : public StageGimmickBase
	{
	public:
		/*** コンストラクタ */
		WoodGimmick();

		/*** デストラクタ */
		virtual ~WoodGimmick();

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

		static const D3DXVECTOR2			m_WoodGimmickSize;

		std::vector<D3DXVECTOR2>			m_Positions;	//!< ギミックの座標.
		std::vector<D3DXVECTOR2>			m_GimmickUV;	//!< ギミックのUV.
		WoodGimmickCollision*				m_pCollision;	//!< ギミックの当たり判定オブジェクト.
		Lib::Dx11::MultipleVertex2DUV*		m_pMultipleVertexUV;
		int									m_Time;
	};
}


#endif // GAME_WOODGIMMICK_H
