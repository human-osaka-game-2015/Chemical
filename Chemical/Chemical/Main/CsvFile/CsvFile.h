/**
 * @file	CsvFile.h
 * @brief	CSVファイルクラス定義
 * @author	morimoto
 */
#ifndef CSVFILE_H
#define CSVFILE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <stdio.h>
#include "Define\Define.h"


/*** CSVファイルクラス */
class CsvFile
{
public:
	/*** コンストラクタ */
	CsvFile();

	/**
	 * コンストラクタ
	 * @param[in] _pFilePath ファイルパス
	 * @param[in] _lineNum データ行数
	 */
	CsvFile(LPCTSTR _pFilePath, int _lineNum);

	/*** デストラクタ */
	~CsvFile();

	/**
	 * CSVデータの取得
	 * @return CSVデータ
	 */
	int** GetData(){ return m_ppData; }

	/**
	 * CSVの行数の取得
	 * @return CSVの行数
	 */
	int GetLineNum(){ return m_LineNum; }

	/**
	 * CSVの列数の取得
	 * @return CSVの列数
	 */
	int GetRowNum(){ return m_RowNum; }

private:
	/**
	 * 読み込み処理
	 * @param[in] _pFilePath ファイルパス
	 * @param[in] _lineNum データ行数
	 */
	void Load(LPCTSTR _pFilePath, int _lineNum);

	/*** 開放処理 */
	void Release();


	int**	m_ppData;	//!< CSVファイルデータ.
	int		m_LineNum;	//!< CSVファイルの行数.
	int		m_RowNum;	//!< CSVファイルの列数.

};


#endif // !CSVFILE_H
