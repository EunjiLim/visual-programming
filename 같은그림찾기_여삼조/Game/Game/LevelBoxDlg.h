#pragma once


// LevelBoxDlg 대화 상자입니다.

class LevelBoxDlg : public CDialog
{
	DECLARE_DYNAMIC(LevelBoxDlg)

public:
	LevelBoxDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~LevelBoxDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_LEVEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLevel1();
	afx_msg void OnBnClickedButtonLevel2();
	afx_msg void OnBnClickedButtonLevel3();
	afx_msg void OnBnClickedButtonQuit();
};
