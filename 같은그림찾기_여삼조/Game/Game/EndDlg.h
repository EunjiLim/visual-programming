#pragma once


// CEndDlg ��ȭ �����Դϴ�.

class CEndDlg : public CDialog
{
	DECLARE_DYNAMIC(CEndDlg)

public:
	CEndDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CEndDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_END };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strScore;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	virtual void OnOK();
	CString m_strOver;
};
