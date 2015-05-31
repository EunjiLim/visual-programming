// NameDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Game.h"
#include "NameDlg.h"
#include "afxdialogex.h"

//추가 부분
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
// CNameDlg 대화 상자입니다.

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


// CNameDlg 메시지 처리기입니다.

#include <iostream>

void CNameDlg::OnOK()
{
	//
	
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	UpdateData(true);
	CString tmp =m_Name;

	tmp.TrimLeft();				// 사용자로 부터 입력받은 텍스트의 좌우 공백을 없애고,
	tmp.TrimRight();
	if(tmp == "")				// 이름을 쓰지 않았을때 에러 메세지를 보여줌.
	{
		MessageBox((_T("이름을 입력하세요..")), MB_OK);
	}
	else
		CDialog::OnOK();
	
	CDialog::OnOK();
}
