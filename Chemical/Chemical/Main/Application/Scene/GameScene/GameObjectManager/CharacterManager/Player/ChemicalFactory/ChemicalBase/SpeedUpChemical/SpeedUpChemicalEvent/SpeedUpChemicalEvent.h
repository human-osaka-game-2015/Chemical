/**
 * @file   SpeedUpChemicalEvent.h
 * @brief  踏んだら足が速くなるインベントクラスのヘッダファイル
 * @author kotani
 */

#ifndef GAME_SPEEDUPCHEMICALEVENT_H
#define GAME_SPEEDUPCHEMICALEVENT_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "EventManager\EventBase\EventBase.h"
#include "GameObjectManager\CharacterManager\Player\ChemicalFactory\ChemicalBase\ChemicalBase.h"
#include <D3DX11.h>
#include <D3DX10.h>

namespace Game
{
	class SpeedUpChemicalEvent : public Lib::EventBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _eventID イベントのID
		 */
		SpeedUpChemicalEvent(unsigned int _eventID);

		/*** デストラクタ */
		virtual ~SpeedUpChemicalEvent();

		/**
		 * 移動速度が上がる座標の設定関数
		 * @param[in] _pos 雨を降らせる座標
		 */
		void SetSpeedUpPos(const D3DXVECTOR2& _pos){ m_SpeedUpPos = _pos; }

		/**
		 * 移動速度が上がる座標の取得関数
		 * @return 降らせる座標
		 */
		D3DXVECTOR2 GetSpeedUpPos(){ return m_SpeedUpPos; }

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
		D3DXVECTOR2			m_SpeedUpPos;
		ChemicalBase::GRADE m_ChemicalGrade;

	};
}


#endif
