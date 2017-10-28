/**
 * @file   GameDataManager.h
 * @brief  GameDataManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAME_GAMEDATA_MANAGER_H
#define GAME_GAMEDATA_MANAGER_H
#include "SingletonBase\SingletonBase.h"
#include <D3DX10.h>

namespace Game
{
	class GameDataManager : public Lib::SingletonBase<GameDataManager>
	{
		friend Lib::SingletonBase<GameDataManager>;
	public:
		/**
		 * プレイヤーの座標のポインタをセットする 
		 * @param[in] プレイヤー座標のポインタ
		 */
		void SetPlayerPosPtr(D3DXVECTOR2* _pPlayerPos)
		{
			m_PlayerPos = _pPlayerPos;
		}

		/**
		 * プレイヤー座標を取得する  
		 * @return プレイヤー座標
		 */
		D3DXVECTOR2 GetPlayerPos()
		{
			return *m_PlayerPos;
		}

	private:
		/*** コンストラクタ */
		GameDataManager();

		/*** デストラクタ */
		virtual ~GameDataManager();
	
		D3DXVECTOR2* m_PlayerPos;
	
	};
}


#endif
