#pragma once
#include "afxcmn.h"


// CRankDlg 대화 상자입니다.

class CRankDlg : public CDialog
{
	DECLARE_DYNAMIC(CRankDlg)

public:
	CRankDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRankDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_RANK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonExit();
	CListCtrl m_List;
	virtual BOOL OnInitDialog();
	void InsertColumn(void);
	void AddData(void);
	afx_msg void OnBnClickedButtonScoreset();
};
