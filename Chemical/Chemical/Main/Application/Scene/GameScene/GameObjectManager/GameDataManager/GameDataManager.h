/**
 * @file   GameDataManager.h
 * @brief  GameDataManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAME_GAMEDATA_MANAGER_H
#define GAME_GAMEDATA_MANAGER_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "SingletonBase\SingletonBase.h"

#include <D3DX11.h>
#include <D3DX10.h>


namespace Game
{
	class GameDataManager : public Lib::SingletonBase<GameDataManager>
	{
	public:
		friend Lib::SingletonBase<GameDataManager>;

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

		/**
		 * スクリーン座標のポインタを設定
		 * @param[in] スクリーン座標のポインタ
		 */
		void SetScreenPosPtr(D3DXVECTOR2* _pScreenPos)
		{
			m_ScreenPos = _pScreenPos;
		}

		/**
		 * スクリーン座標を取得  
		 * @return スクリーン座標
		 */
		D3DXVECTOR2 GetScreenPos()
		{
			return *m_ScreenPos;
		}

		void SetTime(int _minute, int _seconds)
		{
			m_Seconds = _seconds;
			m_Minute = _minute;
		}

		int GetSeconds(){ return m_Seconds; }

		int GetMinute(){ return m_Minute; }

	private:
		/*** コンストラクタ */
		GameDataManager();

		/*** デストラクタ */
		virtual ~GameDataManager();
	
		D3DXVECTOR2* m_PlayerPos;
		D3DXVECTOR2* m_ScreenPos;
		int			 m_Seconds;		//!< 経過時間(秒).
		int			 m_Minute;		//!< 経過時間(分).

	};
}


#endif
