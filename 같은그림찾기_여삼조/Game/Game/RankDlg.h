#pragma once
#include "afxcmn.h"


// CRankDlg ��ȭ �����Դϴ�.

class CRankDlg : public CDialog
{
	DECLARE_DYNAMIC(CRankDlg)

public:
	CRankDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRankDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_RANK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonExit();
	CListCtrl m_List;
	virtual BOOL OnInitDialog();
	void InsertColumn(void);
	void AddData(void);
	afx_msg void OnBnClickedButtonScoreset();
};
