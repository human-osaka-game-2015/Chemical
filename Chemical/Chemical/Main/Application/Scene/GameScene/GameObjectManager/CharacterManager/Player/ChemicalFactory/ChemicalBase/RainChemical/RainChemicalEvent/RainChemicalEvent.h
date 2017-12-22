/**
 * @file   RainChemicalEvent.h
 * @brief  雨を降らせるインベントクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAME_RAINCHEMICALEVENT_H
#define GAME_RAINCHEMICALEVENT_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EventManager\EventBase\EventBase.h"
#include "GameObjectManager\CharacterManager\Player\ChemicalFactory\ChemicalBase\ChemicalBase.h"
#include <D3DX11.h>
#include <D3DX10.h>


namespace Game
{
	class RainChemicalEvent : public Lib::EventBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _eventID イベントのID
		 */
		RainChemicalEvent(unsigned int _eventID);

		/*** デストラクタ */
		virtual ~RainChemicalEvent();

		/**
		 * 雨を降らせる座標の設定関数 
		 * @param[in] _pos 雨を降らせる座標
		 */
		void SetRainPos(const D3DXVECTOR2& _pos){ m_RainPos = _pos; }

		/**
		 * 雨を降らせる座標の取得関数 
		 * @return 降らせる座標
		 */
		D3DXVECTOR2 GetRainPos(){ return m_RainPos; }

		/**
		 * 薬品の等級の設定関数
		 * @param[in] _chemicalGrade 薬品の等級
		 */
		void SetChemicalGrade(ChemicalBase::GRADE _chemicalGrade)
		{
			m_ChemicalGrade = _chemicalGrade;
		}

		/**
		 * 薬品の等級の取得関数
		 * @return 薬品の等級
		 */
		ChemicalBase::GRADE GetChemicalGrade(){ return m_ChemicalGrade; }

	private:
		D3DXVECTOR2			m_RainPos;
		ChemicalBase::GRADE m_ChemicalGrade;

	};
}


#endif
