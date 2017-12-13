/**
 * @file	EnemyGenerator.h
 * @brief	エネミー生成ギミッククラス定義
 * @author	morimoto
 */
#ifndef GAME_ENEMYGENERATOR_H
#define GAME_ENEMYGENERATOR_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "CollisionManager\CollisionBase\GimmickCollision\EnemyGeneratorCollision\EnemyGeneratorCollision.h"
#include "..\StageGimmickBase.h"
#include "DirectX11\MultipleVertex2D\Dx11MultipleVertex2DUV.h"
#include "EnemyGeneratorEvent\EnemyGeneratorEvent.h"


namespace Game
{
	/*** エネミー生成ギミッククラス */
	class EnemyGenerator : public StageGimmickBase
	{
	public:
		/*** コンストラクタ */
		EnemyGenerator();

		/*** デストラクタ */
		virtual ~EnemyGenerator();

		/**
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
		 * @param[in] _data ギミックに対する付加情報
		 */
		virtual void AddGimmick(int _x, int _y, int _data);

		/*** チップのクリア */
		virtual void ClearChip();

		/*** インスタンスバッファの生成 */
		virtual bool CreateInstanceBuffer();

		/*** インスタンスバッファの解放 */
		virtual void ReleaseInstanceBuffer();

	private:
		using GIMMICK_RECTANGLE = GimmickCollision::GIMMICK_RECTANGLE;

		std::vector<D3DXVECTOR2>			m_Positions;	//!< ギミックの座標.
		std::vector<D3DXVECTOR2>			m_GimmickUV;	//!< ギミックのUV.
		std::vector<int>					m_Times;		//!< ギミックの時間.
		EnemyGeneratorCollision*			m_pCollision;	//!< ギミックの当たり判定オブジェクト.
		Lib::Dx11::MultipleVertex2DUV*		m_pMultipleVertexUV;

		EnemyGeneratorEvent*				m_pEvent;	//!< エネミー生成イベント.

	};
}


#endif // !GAME_ENEMYGENERATOR_H
