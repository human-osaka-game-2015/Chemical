/**
 * @file	StageGimmickBase.h
 * @brief	ステージギミック基底クラス定義
 * @author	morimoto
 */
#ifndef GAME_STAGEGIMMICKBASE_H
#define GAME_STAGEGIMMICKBASE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "MultipleObject2DBase\MultipleObject2DBase.h"
#include "..\..\..\..\GameDefine.h"

#include <vector>


namespace Game
{
	/** ステージギミック基底クラス */
	class StageGimmickBase : public MultipleObject2DBase
	{
	public:
		/**
		 * コンストラクタ 
		 * @param[in] _textureName テクスチャ名
		 * @param[in] _taskName タスク名
		 */
		StageGimmickBase(LPCTSTR _textureName, LPCTSTR _taskName);

		/*** デストラクタ */
		virtual ~StageGimmickBase();

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

	protected:
		LPCTSTR						m_TextureName;	//!< 描画するテクスチャ名.
		LPCTSTR						m_TaskName;		//!< タスクの名前.
		int							m_GimmickNum;	//!< ギミックの個数.

	};
}


#endif // !GAME_STAGEGIMMICKBASE_H
