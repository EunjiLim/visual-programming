// LevelBoxDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Game.h"
#include "LevelBoxDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "GameDoc.h"
#include "GameView.h"

// LevelBoxDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(LevelBoxDlg, CDialog)

LevelBoxDlg::LevelBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(LevelBoxDlg::IDD, pParent)
{

}

LevelBoxDlg::~LevelBoxDlg()
{
}

void LevelBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LevelBoxDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_LEVEL1, &LevelBoxDlg::OnBnClickedButtonLevel1)
	ON_BN_CLICKED(IDC_BUTTON_LEVEL2, &LevelBoxDlg::OnBnClickedButtonLevel2)
	ON_BN_CLICKED(IDC_BUTTON_LEVEL3, &LevelBoxDlg::OnBnClickedButtonLevel3)
	ON_BN_CLICKED(ID_BUTTON_QUIT, &LevelBoxDlg::OnBnClickedButtonQuit)
END_MESSAGE_MAP()


// LevelBoxDlg 메시지 처리기입니다.


void LevelBoxDlg::OnBnClickedButtonLevel1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EndDialog(1);
}


void LevelBoxDlg::OnBnClickedButtonLevel2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EndDialog(2);
}


void LevelBoxDlg::OnBnClickedButtonLevel3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EndDialog(3);
}

void LevelBoxDlg::OnBnClickedButtonQuit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EndDialog(0);
}
