// NameDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Game.h"
#include "NameDlg.h"
#include "afxdialogex.h"

//�߰� �κ�
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
// CNameDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CNameDlg, CDialog)

CNameDlg::CNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNameDlg::IDD, pParent)
{
	m_Name = _T("");
}

CNameDlg::~CNameDlg()
{
}

void CNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Name);
}


BEGIN_MESSAGE_MAP(CNameDlg, CDialog)
END_MESSAGE_MAP()


// CNameDlg �޽��� ó�����Դϴ�.

#include <iostream>

void CNameDlg::OnOK()
{
	//
	
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	UpdateData(true);
	CString tmp =m_Name;

	tmp.TrimLeft();				// ����ڷ� ���� �Է¹��� �ؽ�Ʈ�� �¿� ������ ���ְ�,
	tmp.TrimRight();
	if(tmp == "")				// �̸��� ���� �ʾ����� ���� �޼����� ������.
	{
		MessageBox((_T("�̸��� �Է��ϼ���..")), MB_OK);
	}
	else
		CDialog::OnOK();
	
	CDialog::OnOK();
}
