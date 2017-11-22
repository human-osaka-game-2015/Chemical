/**
 * @file	WoodGimmick.h
 * @brief	木ギミッククラス定義
 * @author	morimoto
 */
#ifndef GAME_WOODGIMMICK_H
#define GAME_WOODGIMMICK_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\StageGimmickBase.h"


namespace Game
{
	/*** 木ギミッククラス */
	class WoodGimmick : public StageGimmickBase
	{
	public:
		/*** コンストラクタ */
		WoodGimmick();

		/*** デストラクタ */
		virtual ~WoodGimmick();

		/* 
		 * 初期化処理
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();
	};
}


#endif // GAME_WOODGIMMICK_H
