#pragma once


// CNameDlg ��ȭ �����Դϴ�.

class CNameDlg : public CDialog
{
	DECLARE_DYNAMIC(CNameDlg)

public:
	CNameDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CNameDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_NAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_Name;
	virtual void OnOK();
};
