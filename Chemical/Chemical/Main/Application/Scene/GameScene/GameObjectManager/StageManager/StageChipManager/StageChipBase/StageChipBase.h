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
#include "Object2DBase\Object2DBase.h"


namespace Game
{
	/*** ステージチップ基底クラス */
	class StageChipBase : public Object2DBase
	{
	public:
		/**
		 * コンストラクタ 
		 * @param[in] _textureName テクスチャ名
		 */
		StageChipBase(LPCTSTR _textureName);

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

	private:
		LPCTSTR m_TextureName;	//!< 描画するテクスチャ名.

	};
}


#endif // !GAME_STAGECHIPBASE_H
