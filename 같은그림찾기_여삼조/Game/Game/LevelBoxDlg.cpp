// LevelBoxDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Game.h"
#include "LevelBoxDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "GameDoc.h"
#include "GameView.h"

// LevelBoxDlg ��ȭ �����Դϴ�.

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


// LevelBoxDlg �޽��� ó�����Դϴ�.


void LevelBoxDlg::OnBnClickedButtonLevel1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	EndDialog(1);
}


void LevelBoxDlg::OnBnClickedButtonLevel2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	EndDialog(2);
}


void LevelBoxDlg::OnBnClickedButtonLevel3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	EndDialog(3);
}

void LevelBoxDlg::OnBnClickedButtonQuit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	EndDialog(0);
}
