/**
 * @file	SoilTop.h
 * @brief	土の上部クラス定義
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "..\..\StageChipBase.h"


namespace Game
{
	/*** 土の上部クラス */
	class SoilTop : public StageChipBase
	{
	public:
		/*** コンストラクタ*/
		SoilTop();

		/*** デストラクタ */
		virtual ~SoilTop();

	private:
		using RECTANGLE = ChipCollision::RECTANGLE;
		std::vector<RECTANGLE> m_Rectangles;

	};
}

