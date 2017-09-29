/**
 * @file	Dx11Animation.cpp
 * @brief	2Dアニメーションクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Dx11Animation.h"

#include "..\..\..\Define\Define.h"
#include "..\..\..\Debugger\Debugger.h"


namespace Lib
{
	namespace Dx11
	{
		//----------------------------------------------------------------------
		// Static Private Variables
		//----------------------------------------------------------------------
		const float Animation::m_AnimationTime = 1.0f;


		//----------------------------------------------------------------------
		// Constructor	Destructor
		//----------------------------------------------------------------------
		Animation::Animation(LPCTSTR _pAnimationPath) :
			m_CurrentFrame(0),
			m_AnimationCounter(0.0f),
			m_AnimationSpeed(1.0f),
			m_AnimationPattern(ONE_ANIMATION),
			m_IsReverse(false),
			m_IsAnimationEnd(false),
			m_pAnimationFunc(&Animation::OneAnimationControl)
		{
			Load(_pAnimationPath);
		}

		Animation::~Animation()
		{
			Release();
		}


		//----------------------------------------------------------------------
		// Public Functions
		//----------------------------------------------------------------------
		void Animation::AnimationStart()
		{
			m_CurrentFrame = 0;
			m_AnimationCounter = 0;
			m_IsReverse = false;
			m_IsAnimationEnd = 0;
		}

		bool Animation::Update()
		{
			return (this->*m_pAnimationFunc)();
		}

		void Animation::SetAnimationPattern(Animation::ANIMATION_PATTERN _animationPattern)
		{
			// 設定されたパターンの関数ポインタをセット.
			switch (_animationPattern)
			{
			case ONE_ANIMATION:
				m_pAnimationFunc = &Animation::OneAnimationControl;
				break;
			case LOOP_ANIMATION:
				m_pAnimationFunc = &Animation::LoopAnimationControl;
				break;
			case REVERSE_ONE_ANIMATION:
				m_pAnimationFunc = &Animation::ReverseOneAnimationControl;
				break;
			case REVERSE_LOOP_ANIMATION:
				m_pAnimationFunc = &Animation::ReverseLoopAnimationControl;
				break;
			default:
				OutputErrorLog("AnimationPatternに無効な値が設定されました\n無視します");
				return;
				break;
			}

			m_CurrentFrame = 0;
			m_AnimationCounter = 0;
			m_AnimationPattern = _animationPattern;
		}

		void Animation::SetAnimationSpeed(float _animationSpeed)
		{
			m_AnimationSpeed = _animationSpeed;
		}

		void Animation::SetFrameNumber(int _frameNumber)
		{
			if (m_pFrame.size() <= static_cast<unsigned int>(_frameNumber))
			{
				return;
			}

			m_CurrentFrame = _frameNumber;
		}

		int Animation::GetFrameNumber()
		{
			return m_CurrentFrame;
		}

		int Animation::GetFrameMax()
		{
			return m_pFrame.size();
		}

		Animation::ANIMATION_FRAME* Animation::GetCurrentFrame() const
		{
			return m_pFrame[m_CurrentFrame];
		}


		//----------------------------------------------------------------------
		// Private Functions
		//----------------------------------------------------------------------
		void Animation::Load(LPCTSTR _pAnimationPath)
		{
			///@todo 読み込みに失敗した場合は現在のフレームをnullptrに設定するように修正する.

			FILE* pAnimationFile = nullptr;
			std::vector<float> AnimationData;
			long FileSize = 0;
			char* pBuffer = nullptr;
			char* pContext = nullptr;
			char* pDataStr = nullptr;

			fopen_s(&pAnimationFile, _pAnimationPath, "r");

			// ファイルサイズの取得.
			fseek(pAnimationFile, 0, SEEK_END);
			FileSize = ftell(pAnimationFile) + 1;
			fseek(pAnimationFile, 0, SEEK_SET);

			// ファイルのデータを格納するバッファ.
			pBuffer = new char[FileSize];
			ZeroMemory(pBuffer, FileSize);

			// ファイルの読み込み.
			fread(pBuffer, FileSize, 1, pAnimationFile);
			pBuffer[FileSize - 1] = '\0';

			// ファイル内のデータを見つけて取得.
			pBuffer = strstr(pBuffer, "{");
			strcpy_s(pBuffer, FileSize, strtok_s(pBuffer, "{}", &pContext));
			pDataStr = strtok_s(pBuffer, "{},\n", &pContext);

			while (1)
			{
				if (pDataStr == nullptr)
				{
					break;	// データ全てを取り出すまでループ
				}
				else
				{
					AnimationData.push_back(static_cast<float>(atof(pDataStr)));
				}

				pDataStr = strtok_s(nullptr, "{},\n", &pContext);
			}

			fclose(pAnimationFile);


			// 取り出したデータを追加する.
			for (unsigned int i = 0; i < AnimationData.size() / 5; i++)
			{
				m_pFrame.push_back(new ANIMATION_FRAME);
				m_pFrame[i]->FrameID = static_cast<int>(AnimationData[i * 5]);
				m_pFrame[i]->MinTu = AnimationData[i * 5 + 1];
				m_pFrame[i]->MinTv = AnimationData[i * 5 + 2];
				m_pFrame[i]->MaxTu = AnimationData[i * 5 + 3];
				m_pFrame[i]->MaxTv = AnimationData[i * 5 + 4];
			}

			delete pBuffer;
		}

		void Animation::Release()
		{
			for (auto itr = m_pFrame.begin(); itr != m_pFrame.end(); itr++)
			{
				SafeDelete(*itr);
			}
		}

		bool Animation::OneAnimationControl()
		{
			if (m_IsAnimationEnd == false)
			{
				m_AnimationCounter += m_AnimationSpeed;

				if (m_AnimationCounter >= m_AnimationTime)
				{
					m_AnimationCounter = 0.0f;
					m_CurrentFrame++;

					if (static_cast<int>(m_pFrame.size()) <= m_CurrentFrame)
					{
						m_CurrentFrame--;
						m_IsAnimationEnd = true;
						return true;
					}
				}
			}

			return false;
		}

		bool Animation::LoopAnimationControl()
		{
			m_AnimationCounter += m_AnimationSpeed;

			if (m_AnimationCounter >= m_AnimationTime)
			{
				m_AnimationCounter = 0.0f;
				m_CurrentFrame++;

				if (static_cast<int>(m_pFrame.size()) <= m_CurrentFrame)
				{
					m_CurrentFrame = 0;
				}
			}

			return false;
		}

		bool Animation::ReverseOneAnimationControl()
		{
			if (m_IsAnimationEnd == false)
			{
				m_AnimationCounter += m_AnimationSpeed;

				if (!m_IsReverse)
				{
					if (m_AnimationCounter >= m_AnimationTime)
					{
						m_AnimationCounter = 0.0f;
						m_CurrentFrame++;

						if (static_cast<int>(m_pFrame.size()) - 1 <= m_CurrentFrame)
						{
							m_IsReverse = true;
						}
					}
				}
				else
				{
					if (m_AnimationCounter >= m_AnimationTime)
					{
						m_AnimationCounter = 0.0f;
						m_CurrentFrame--;

						if (m_CurrentFrame < 0)
						{
							m_IsAnimationEnd = true;
							m_CurrentFrame = 0;
							m_IsReverse = false;
							return true;
						}
					}
				}
			}

			return false;
		}

		bool Animation::ReverseLoopAnimationControl()
		{
			m_AnimationCounter += m_AnimationSpeed;

			if (!m_IsReverse)
			{
				if (m_AnimationCounter >= m_AnimationTime)
				{
					m_AnimationCounter = 0.0f;
					m_CurrentFrame++;

					if (static_cast<int>(m_pFrame.size()) - 1 <= m_CurrentFrame)
					{
						m_IsReverse = true;
					}
				}
			}
			else
			{
				if (m_AnimationCounter >= m_AnimationTime)
				{
					m_AnimationCounter = 0.0f;
					m_CurrentFrame--;

					if (m_CurrentFrame < 0)
					{
						m_CurrentFrame = 0;
						m_IsReverse = false;
					}
				}
			}

			return false;
		}
	}
}

