/**
 * @file   InitializeData.h
 * @brief  InitializeDataクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAME_INITIALIZEDATA_H
#define GAME_INITIALIZEDATA_H
#include "SingletonBase\SingletonBase.h"

#include <D3DX11.h>
#include <D3DX10.h>
#include <vector>

namespace Game
{
	class InitializeData
	{
		friend Lib::SingletonBase<InitializeData>;
	public:
		/**
		 * 初期化時に必要なデータを読み込む
		 * @param[in] _stageNum 読み込むステージ番号
		 */
		void Load(int _stageNum);

		/**
		 * プレイヤーの初期座標を取得する
		 * @return プレイヤーの初期座標
		 */
		D3DXVECTOR2 GetPlayerInitPos()
		{
			return m_PlayerPos;
		}

		/**
		 * 敵の初期座標のvectorを取得する
		 * @return 敵の初期座標のvector
		 */
		std::vector<D3DXVECTOR2> GetEnemysInitPos()
		{
			return m_EnemysPos;
		}

	private:
		enum
		{
			NON,
			PLAYER,
			ENEMY
		};
		InitializeData();
		~InitializeData();

		D3DXVECTOR2				 m_PlayerPos;
		std::vector<D3DXVECTOR2> m_EnemysPos;

	};
}


#endif
