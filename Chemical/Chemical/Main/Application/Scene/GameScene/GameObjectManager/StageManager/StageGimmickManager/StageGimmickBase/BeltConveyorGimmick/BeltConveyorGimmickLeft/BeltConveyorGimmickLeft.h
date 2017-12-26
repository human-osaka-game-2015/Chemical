/**
 * @file	BeltConveyorGimmickLeft.h
 * @brief	ベルトコンベア左端ギミッククラス定義
 * @author	morimoto
 */
#ifndef GAME_BELTCONVEYORLEFTGIMMICK_H
#define GAME_BELTCONVEYORLEFTGIMMICK_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageGimmickBase.h"
#include "CollisionManager\CollisionBase\GimmickCollision\BeltConveyorGimmickCollision\BeltConveyorGimmickCollision.h"
#include "DirectX11\MultipleVertex2D\Dx11MultipleVertex2DUV.h"


namespace Game
{
	/*** ベルトコンベア左端ギミッククラス */
	class BeltConveyorGimmickLeft : public StageGimmickBase
	{
	public:
		/*** コンストラクタ */
		BeltConveyorGimmickLeft();

		/*** デストラクタ */
		virtual ~BeltConveyorGimmickLeft();

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
		std::vector<int>					m_GimmickData;	//!< ギミックの付加情報.
		BeltConveyorGimmickCollision*		m_pCollision;
		Lib::Dx11::MultipleVertex2DUV*		m_pMultipleVertexUV;
		int									m_Time;

	};
}


#endif // !GAME_BELTCONVEYORLEFTGIMMICK_H
