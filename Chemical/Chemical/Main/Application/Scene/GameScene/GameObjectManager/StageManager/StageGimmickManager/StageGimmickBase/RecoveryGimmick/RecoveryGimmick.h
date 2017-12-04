/**
 * @file	RecoveryGimmick.h
 * @brief	回復ギミッククラス定義
 * @author	morimoto
 */
#ifndef GAME_RECOVERYGIMMICK_H
#define GAME_RECOVERYGIMMICK_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\StageGimmickBase.h"
#include "CollisionManager\CollisionBase\GimmickCollision\RecoveryGimmickCollision\RecoveryGimmickCollision.h"
#include "DirectX11\MultipleVertex2D\Dx11MultipleVertex2DUV.h"


namespace Game
{
	/*** 回復ギミッククラス */
	class RecoveryGimmick : public StageGimmickBase
	{
	public:
		/*** コンストラクタ */
		RecoveryGimmick();

		/*** デストラクタ */
		virtual ~RecoveryGimmick();

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

		static const int m_UpTime;
		static const int m_DownTime;

		std::vector<D3DXVECTOR2>			m_Positions;	//!< ギミックの座標.
		std::vector<D3DXVECTOR2>			m_GimmickUV;	//!< ギミックのUV.
		std::vector<int>					m_Times;		//!< ギミックの時間.
		RecoveryGimmickCollision*			m_pCollision;	//!< ギミックの当たり判定オブジェクト.
		Lib::Dx11::MultipleVertex2DUV*		m_pMultipleVertexUV;

	};
}


#endif // !GAME_RECOVERYGIMMICK_H
