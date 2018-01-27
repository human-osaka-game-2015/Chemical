/**
 * @file	ResultFile.h
 * @brief	リザルトファイルクラス定義
 * @author	morimoto
 */
#ifndef RESULTFILE_H
#define RESULTFILE_H

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include <stdio.h>


/*** リザルトファイルクラス */
class ResultFile
{
public:
	/*** コンストラクタ */
	ResultFile();

	/*** デストラクタ */
	~ResultFile();

	/**
	 * ファイルを開く。無ければ生成する
	 * @return 成功すればtrue
	 */
	bool Open();

	/*** ファイルを閉じる */
	void Close();

	/*** 設定したデータを書き込む */
	void Write();

	void SetSeconds(int _seconds) { m_Seconds = _seconds; }
	int GetSeconds() { return m_Seconds; }

	void SetMinute(int _minute) { m_Minute = _minute; }
	int GetMinute() { return m_Minute; }

	void SetScore(int _score) { m_Score = _score; }
	int GetScore() { return m_Score; }

	void SetClear(int _clear) { m_IsClear = _clear; }
	int GetClear() { return m_IsClear; }

	void SetStageNum(int _stageNum) { m_StageNum = _stageNum; }
	int GetStageNum() { return m_StageNum; }

private:
	int	m_Seconds;
	int m_Minute;
	int	m_Score;
	int m_IsClear;	//!< 1の場合はクリア 0の場合はオーバー.
	int	m_StageNum;

	FILE* m_pFile;

};


#endif // !RESULTFILE_H
