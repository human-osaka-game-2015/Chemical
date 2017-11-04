/**
 * @file	CharacterManager.h
 * @brief	キャラクター管理クラス定義
 * @author	morimoto
 */
#ifndef GAME_CHARACTERMANAGER_H
#define GAME_CHARACTERMANAGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ObjectManagerBase\ObjectBase\ObjectBase.h"

#include <vector>

namespace Game
{
	class Player;
	class Enemy;

	/*** キャラクター管理クラス */
	class CharacterManager : public Lib::ObjectBase
	{
	public:
		/*** コンストラクタ */
		CharacterManager();

		/*** デストラクタ */
		virtual ~CharacterManager();

		/**
		 * 初期化処理
		 * @return 初期化に成功したか
		 */
		virtual bool Initialize();

		/*** 終了処理 */
		virtual void Finalize();

	private:
		Player* m_pPlayer;
		std::vector<Enemy*> m_pEnemys;


	};
}


#endif // !GAME_CHARACTERMANAGER_H
