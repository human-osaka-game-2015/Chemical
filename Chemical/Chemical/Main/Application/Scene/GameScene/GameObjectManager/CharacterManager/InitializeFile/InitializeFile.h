/**
 * @file   InitializeFile.h
 * @brief  InitializeFileクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAME_INITIALIZEFILE_H
#define GAME_INITIALIZEFILE_H
#include <D3DX11.h>
#include <D3DX10.h>
#include <vector>

namespace Game
{
	class InitializeFile
	{
	public:
		/*** コンストラクタ */
		InitializeFile(int _stageNum);

		/*** デストラクタ */
		~InitializeFile();

		/**
		 * プレイヤーの初期座標を取得する
		 * @return プレイヤーの初期座標
		 */
		const D3DXVECTOR2& GetPlayerInitPos()
		{
			return m_PlayerInitPos;
		}

		/**
		 * 敵の初期座標のvectorを取得する
		 * @return 敵の初期座標のvector
		 */
		const std::vector<D3DXVECTOR2>& GetEnemysInitPos()
		{
			return m_EnemysInitPos;
		}

		const std::vector<int>& GetEnemysPattern()
		{
			return m_EnemysPattern;
		}

	private:
		enum
		{
			NONE,
			PLAYER,
			ENEMY
		};

		/**
		 * 初期化時に必要なデータを読み込む
		 * @param[in] _stageNum 読み込むステージ番号
		 */
		void Load(int _stageNum);

		D3DXVECTOR2				 m_PlayerInitPos;
		std::vector<D3DXVECTOR2> m_EnemysInitPos;
		std::vector<int>		 m_EnemysPattern;
	};
}


#endif
