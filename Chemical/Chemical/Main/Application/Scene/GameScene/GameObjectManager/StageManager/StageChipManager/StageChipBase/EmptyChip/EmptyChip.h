/**
 * @file	EmptyChip.h
 * @brief	空チップクラス定義
 * @author	morimoto
 */
#ifndef GAME_EMPTYCHIP_H
#define GAME_EMPTYCHIP_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\StageChipBase.h"


namespace Game
{
	/*** 空チップクラス */
	class EmptyChip : public StageChipBase
	{
	public:
		/*** コンストラクタ */
		EmptyChip();

		/*** デストラクタ*/
		virtual ~EmptyChip();

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

		/*** インスタンスバッファの解放 */
		virtual void ReleaseInstanceBuffer();

	};
}


#endif // !GAME_EMPTYCHIP_H
