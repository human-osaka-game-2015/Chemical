/**
 * @file	EmptyGimmick.h
 * @brief	空ギミッククラス定義
 * @author	morimoto
 */
#ifndef GAME_EMPTYGIMMICK_H
#define GAME_EMPTYGIMMICK_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\StageGimmickBase.h"


namespace Game
{
	/*** 空ギミッククラス */
	class EmptyGimmick : public StageGimmickBase
	{
	public:
		/*** コンストラクタ */
		EmptyGimmick();

		/*** デストラクタ */
		virtual ~EmptyGimmick();

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

	};
}


#endif // !GAME_EMPTYGIMMICK_H
