/**
 * @file	BackCharacter.h
 * @brief	バックキャラクタークラス定義
 * @author	morimoto
 */
#ifndef RESULT_BACKCHARACTER_H
#define RESULT_BACKCHARACTER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Object2DBase\Object2DBase.h"

#include "Application\ResultFile\ResultFile.h"


namespace Result
{
	/*** バックキャラクタークラス */
	class BackCharacter : public Object2DBase
	{
	public:
		/*** コンストラクタ */
		BackCharacter();

		/*** デストラクタ */
		virtual ~BackCharacter();

		/**
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

		/*** オブジェクトの更新 */
		virtual void Update();

		/*** オブジェクトの描画 */
		virtual void Draw();

	private:
		ResultFile	m_ResultFile;

	};
}


#endif // !RESULT_BACKCHARACTER_H
