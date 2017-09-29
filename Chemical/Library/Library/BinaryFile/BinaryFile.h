/**
 * @file	BinaryFile.h
 * @brief	バイナリファイルクラス定義
 * @author	morimoto
 */
#ifndef BINARYFILE_H
#define BINARYFILE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <Windows.h>


namespace Lib
{
	class BinaryFile
	{
	public:
		/**
		 * コンストラクタ
		 */
		BinaryFile();

		/**
		 * デストラクタ
		 */
		~BinaryFile();

		/**
		 * ファイル読み込み
		 * @param[in] _pFileName 読み込むファイル名
		 */
		bool Read(TCHAR* _pFileName);

		/**
		 * ファイル解放
		 */
		void Destroy();

		/**
		 * バイナリデータの取得
		 * @return バイナリデータ
		 */
		inline void* GetBinary() const
		{
			return m_pBinary;
		}

		/**
		 * バイナリデータサイズの取得
		 * @return バイナリデータサイズ
		 */
		inline size_t GetBinarySize() const
		{
			return m_BinarySize;
		}


	private:
		void*	m_pBinary;		//!< バイナリデータ.
		size_t	m_BinarySize;	//!< バイナリデータサイズ.


	};
}


#endif // !BINARYFILE_H
