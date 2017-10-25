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
#include "Object2DBase\Object2DBase.h"


namespace Game
{
	/** ステージギミック基底クラス */
	class StageGimmickBase : public Object2DBase
	{
	public:
		/**
		 * コンストラクタ 
		 * @param[in] _textureName テクスチャ名
		 */
		StageGimmickBase(LPCTSTR _textureName);

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

	private:
		LPCTSTR m_TextureName;	//!< 描画するテクスチャ名.

	};
}


#endif // !GAME_STAGEGIMMICKBASE_H
