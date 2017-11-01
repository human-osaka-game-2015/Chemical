/**
 * @file	StageChipBase.h
 * @brief	ステージチップ基底クラス定義
 * @author	morimoto
 */
#ifndef GAME_STAGECHIPBASE_H
#define GAME_STAGECHIPBASE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "MultipleObject2DBase\MultipleObject2DBase.h"
#include "DirectX11\MultipleVertex2D\Dx11MultipleVertex2D.h"
#include "..\..\..\..\CollisionManager\CollisionBase\ChipCollision\ChipCollision.h"
#include "..\..\..\..\GameDefine.h"

#include <vector>


namespace Game
{
	/*** ステージチップ基底クラス */
	class StageChipBase : public MultipleObject2DBase
	{
	public:
		/**
		 * コンストラクタ 
		 * @param[in] _id 当たり判定ID
		 * @param[in] _textureName テクスチャ名
		 * @param[in] _taskName タスク名
		 */
		StageChipBase(int _id, LPCTSTR _textureName, LPCTSTR _taskName);

		/*** デストラクタ */
		virtual ~StageChipBase();

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
		 * チップの追加 
		 * @param[in] _x 追加するチップのx位置
		 * @param[in] _y 追加するチップのy位置
		 */
		virtual void AddChip(int _x, int _y);

		/*** チップのクリア */
		virtual void ClearChip();

		/*** インスタンスバッファの生成 */
		virtual bool CreateInstanceBuffer();

		/*** 当たり判定の生成 */
		virtual bool CreateCollision();

		/*** インスタンスバッファの解放 */
		virtual void ReleaseInstanceBuffer();

		/*** 当たり判定の解放 */
		virtual void ReleaseCollision();

	protected:
		ChipCollision*				m_pCollision;		//!< 当たり判定オブジェクト.
		std::vector<D3DXVECTOR2>	m_Positions;		//!< チップの座標.
		LPCTSTR						m_TextureName;		//!< 描画するテクスチャ名.
		LPCTSTR						m_TaskName;			//!< タスクの名前.

	};
}


#endif // !GAME_STAGECHIPBASE_H
