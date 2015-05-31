// EndDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Game.h"
#include "EndDlg.h"
#include "afxdialogex.h"
//������ �κ�
#include <iostream>
#include <fstream>
#include "NameDlg.h";
#include "GameDoc.h";
#include "MainFrm.h";
#include "RankDlg.h";
#include "GameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
///////////////////////////////////////////
using namespace std;
// CEndDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CEndDlg, CDialog)

	CEndDlg::CEndDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEndDlg::IDD, pParent)
	, m_strScore(_T(""))
	, m_strOver(_T(""))
{

}

CEndDlg::~CEndDlg()
{
}

void CEndDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SCORE, m_strScore);
	DDX_Text(pDX, IDC_EDIT_GAMEOVER, m_strOver);
}


BEGIN_MESSAGE_MAP(CEndDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &CEndDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CEndDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CEndDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CEndDlg �޽��� ó�����Դϴ�.

void CEndDlg::OnBnClickedButton1()
{

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//Doc�� �ִ� ��� ���� ����ϱ�
	CMainFrame *pFrame = (CMainFrame*) AfxGetMainWnd();

	CGameDoc   *pDoc = (CGameDoc*)pFrame->GetActiveDocument();

	//// ��� ���� �Լ�

	CString rank_name[10];			// ��ŷ ���Ϸ� ���� �о� ������ �̸��� ���� �迭,
	int rank_score[10];
	int i=0;

	//�ʱ� �� ��쿡 ��ŷ ���
	if(pDoc->m_level==1)
	{
		ifstream fin;
		fin.open("rank1.txt", ios::in);
		char data[80];

		for(i = 0 ; i<10 ; i++)				// ��ŷ ���Ϸ� ���� ���������� �о��.
		{
			fin.getline(data, 80);			// ���Ͽ� ���پ� �а� �Ǵµ�
			rank_name[i] = data;			// ù��° �ٿ��� �̸�,
			fin.getline(data, 80);			// �ι�° �ٿ��� ������ ����Ǿ� �ִ�.
			rank_score[i] = atoi(data);		// ������ 20���� �а� �Ǵ� ���̴�.
		}
		fin.close();

		for(i=9; i>=0; i--)
		{
			if(rank_name[i] == "")
			{
				rank_name[i] = "��� �Ǿ� ���� ����";
				rank_score[i] = 999999;
			}
			else
				break;
		}

		if(pDoc->m_time < rank_score[9])					///���� �ð�����  ���� ���� �ð���ª�� ���
		{
			CNameDlg dlg_name;						// ����ڷ� ���� �̸��� �Է¹޴´�.
			if(dlg_name.DoModal() == IDOK)
			{
				rank_score[9] = pDoc->m_time	;		// �ϴ� ������ �̸��� ���� 10� �÷�����
				rank_name[9] = dlg_name.m_Name;		// �ٽ� sorting�� �� ���̴�. 
			}

			int tmp_int;
			CString tmp_str;

			for(i=0;i<10;i++)							// ���� ������� ����� �� �����Ѵ�.
			{
				for(int j=i+1;j<10;j++)
				{
					if (rank_score[i] > rank_score[j])
					{
						tmp_int = rank_score[i];
						rank_score[i] = rank_score[j];
						rank_score[j] = tmp_int;

						tmp_str = rank_name[i];
						rank_name[i] = rank_name[j];
						rank_name[j] = tmp_str;
					}
				}
			}

			char tmp_char[20];
			ofstream fout("rank1.txt", ios::out);
			for(i=0;i<10;i++)						// �� ������ ������ ���Ͽ� �ٽ� ����.
			{
				//
				CString output;
				output.Format(L"%s",rank_name[i]);
				//const char *temp_rank_name[i]= (const char*)rank_name[i].GetBuffer(100);
				itoa(rank_score[i], tmp_char, 10);
				fout<<CW2A(output)<<endl;
				//���� �ִ���fout<<rank_name[i]<<"\n";
				fout<<rank_score[i]<<"\n";
			}
			fout.close();
			//////////////////////////

			CRankDlg dlg_rank;						// �������� ��ȭ���� ����.
			dlg_rank.DoModal();
		}
	}

	///�߱��� ��쿡 ��ŷ ���
	else if(pDoc->m_level==2)
	{
		ifstream fin;
		fin.open("rank2.txt");
		char data[80];


		for(i = 0 ; i<10 ; i++)				// ��ŷ ���Ϸ� ���� ���������� �о��.
		{
			fin.getline(data, 80);			// ���Ͽ� ���پ� �а� �Ǵµ�
			rank_name[i] = data;			// ù��° �ٿ��� �̸�,
			fin.getline(data, 80);			// �ι�° �ٿ��� ������ ����Ǿ� �ִ�.
			rank_score[i] = atoi(data);		// ������ 20���� �а� �Ǵ� ���̴�.
		}

		fin.close();

		for(i=9; i>=0; i--)
		{
			if(rank_name[i] == "")
			{
				rank_name[i] = "��� �Ǿ� ���� ����";
				rank_score[i] = 999999;
			}
			else
				break;
		}
		///////////////////////////////

		if(pDoc->m_time < rank_score[9])					///���� �ð�����  ���� ���� �ð���ª�� ���
		{
			CNameDlg dlg_name;						// ����ڷ� ���� �̸��� �Է¹޴´�.
			if(dlg_name.DoModal() == IDOK)
			{
				rank_score[9] = pDoc->m_time	;		// �ϴ� ������ �̸��� ���� 10� �÷�����
				rank_name[9] = dlg_name.m_Name;		// �ٽ� sorting�� �� ���̴�. 
			}

			int tmp_int;
			CString tmp_str;
			//

			for(i=0;i<10;i++)							// ���� ������� ����� �� �����Ѵ�.
			{
				for(int j=i+1;j<10;j++)
				{
					if (rank_score[i] > rank_score[j])
					{
						tmp_int = rank_score[i];
						rank_score[i] = rank_score[j];
						rank_score[j] = tmp_int;

						tmp_str = rank_name[i];
						rank_name[i] = rank_name[j];
						rank_name[j] = tmp_str;
					}
				}
			}
			char tmp_char[20];
			ofstream fout("rank2.txt");
			for(i=0;i<10;i++)						// �� ������ ������ ���Ͽ� �ٽ� ����.
			{
				//
				CString output;
				output.Format(L"%s",rank_name[i]);
				//const char *temp_rank_name[i]= (const char*)rank_name[i].GetBuffer(100);
				itoa(rank_score[i], tmp_char, 10);
				fout<<CW2A(output)<<endl;
				//���� �ִ���fout<<rank_name[i]<<"\n";
				fout<<rank_score[i]<<"\n";
			}
			fout.close();
			//////////////////////////

			CRankDlg dlg_rank;						// �������� ��ȭ���� ����.
			dlg_rank.DoModal();
		}
	}
	////////////��� �ϰ�쿡 ��ŷ���
	else
	{
		ifstream fin;
		fin.open("rank3.txt");
		char data[80];


		for(i = 0 ; i<10 ; i++)				// ��ŷ ���Ϸ� ���� ���������� �о��.
		{
			fin.getline(data, 80);			// ���Ͽ� ���پ� �а� �Ǵµ�
			rank_name[i] = data;			// ù��° �ٿ��� �̸�,
			fin.getline(data, 80);			// �ι�° �ٿ��� ������ ����Ǿ� �ִ�.
			rank_score[i] = atoi(data);		// ������ 20���� �а� �Ǵ� ���̴�.
		}

		fin.close();

		for(i=9; i>=0; i--)
		{
			if(rank_name[i] == "")
			{
				rank_name[i] = "��� �Ǿ� ���� ����";
				rank_score[i] = 999999;
			}
			else
				break;
		}
		///////////////////////////////

		if(pDoc->m_time < rank_score[9])					///���� �ð�����  ���� ���� �ð���ª�� ���
		{
			CNameDlg dlg_name;						// ����ڷ� ���� �̸��� �Է¹޴´�.
			if(dlg_name.DoModal() == IDOK)
			{
				rank_score[9] = pDoc->m_time	;		// �ϴ� ������ �̸��� ���� 10� �÷�����
				rank_name[9] = dlg_name.m_Name;		// �ٽ� sorting�� �� ���̴�. 
			}

			int tmp_int;
			CString tmp_str;

			//

			//

			for(i=0;i<10;i++)							// ���� ������� ����� �� �����Ѵ�.
			{
				for(int j=i+1;j<10;j++)
				{
					if (rank_score[i] > rank_score[j])
					{
						tmp_int = rank_score[i];
						rank_score[i] = rank_score[j];
						rank_score[j] = tmp_int;

						tmp_str = rank_name[i];
						rank_name[i] = rank_name[j];
						rank_name[j] = tmp_str;
					}
				}
			}
			char tmp_char[20];
			ofstream fout("rank3.txt");
			for(i=0;i<10;i++)						// �� ������ ������ ���Ͽ� �ٽ� ����.
			{
				//
				CString output;
				output.Format(L"%s",rank_name[i]);
				//const char *temp_rank_name[i]= (const char*)rank_name[i].GetBuffer(100);
				itoa(rank_score[i], tmp_char, 10);
				fout<<CW2A(output)<<endl;
				//���� �ִ���fout<<rank_name[i]<<"\n";
				fout<<rank_score[i]<<"\n";
			}
			fout.close();
			//////////////////////////

			CRankDlg dlg_rank;						// �������� ��ȭ���� ����.
			dlg_rank.DoModal();
		}
	}

}

void CEndDlg::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//���̾�α׿��� Doc������� ����ϱ�
	CMainFrame *pFrame = (CMainFrame*) AfxGetMainWnd();

	CGameView *pView = (CGameView*)pFrame->GetActiveView(); // Ȱ��ȭ�� ���� ������ ���Ѵ�.
	CGameDoc   *pDoc = (CGameDoc*)pFrame->GetActiveDocument();

	pDoc->m_bRandom = true;

	for(int n=0; n < pDoc->m_nRow; n++)
		for(int m=0; m < pDoc->m_nCol; m++)
			pDoc->m_bShow[n][m] = false;

	pDoc->m_nBmpFirstID = pDoc->m_nBmpSecondID = 0;
	pDoc->m_bMouse = false;
	pView->nMatchCount = 0;
	pView->m_bShowCard = true;

	EndDialog(2);
}


void CEndDlg::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnOK();
}




void CEndDlg::OnOK()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	CDialog::OnOK();
}
