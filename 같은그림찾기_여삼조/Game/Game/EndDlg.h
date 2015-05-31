#pragma once


// CEndDlg 대화 상자입니다.

class CEndDlg : public CDialog
{
	DECLARE_DYNAMIC(CEndDlg)

public:
	CEndDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CEndDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_END };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strScore;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	virtual void OnOK();
	CString m_strOver;
};
