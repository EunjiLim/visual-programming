#pragma once


// LevelBoxDlg ��ȭ �����Դϴ�.

class LevelBoxDlg : public CDialog
{
	DECLARE_DYNAMIC(LevelBoxDlg)

public:
	LevelBoxDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~LevelBoxDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_LEVEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLevel1();
	afx_msg void OnBnClickedButtonLevel2();
	afx_msg void OnBnClickedButtonLevel3();
	afx_msg void OnBnClickedButtonQuit();
};
