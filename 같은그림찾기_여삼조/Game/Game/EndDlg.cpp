// EndDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Game.h"
#include "EndDlg.h"
#include "afxdialogex.h"
//수정된 부분
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
// CEndDlg 대화 상자입니다.

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


// CEndDlg 메시지 처리기입니다.

void CEndDlg::OnBnClickedButton1()
{

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//Doc에 있는 멤버 변수 사용하기
	CMainFrame *pFrame = (CMainFrame*) AfxGetMainWnd();

	CGameDoc   *pDoc = (CGameDoc*)pFrame->GetActiveDocument();

	//// 기록 저장 함수

	CString rank_name[10];			// 랭킹 파일로 부터 읽어 저장할 이름과 점수 배열,
	int rank_score[10];
	int i=0;

	//초급 일 경우에 랭킹 등록
	if(pDoc->m_level==1)
	{
		ifstream fin;
		fin.open("rank1.txt", ios::in);
		char data[80];

		for(i = 0 ; i<10 ; i++)				// 랭킹 파일로 부터 순위정보를 읽어옴.
		{
			fin.getline(data, 80);			// 파일에 두줄씩 읽게 되는데
			rank_name[i] = data;			// 첫번째 줄에는 이름,
			fin.getline(data, 80);			// 두번째 줄에는 점수가 저장되어 있다.
			rank_score[i] = atoi(data);		// 실제로 20줄을 읽게 되는 것이다.
		}
		fin.close();

		for(i=9; i>=0; i--)
		{
			if(rank_name[i] == "")
			{
				rank_name[i] = "등록 되어 있지 않음";
				rank_score[i] = 999999;
			}
			else
				break;
		}

		if(pDoc->m_time < rank_score[9])					///최저 시간보다  게임 수행 시간이짧을 경우
		{
			CNameDlg dlg_name;						// 사용자로 부터 이름을 입력받는다.
			if(dlg_name.DoModal() == IDOK)
			{
				rank_score[9] = pDoc->m_time	;		// 일단 점수와 이름을 순위 10등에 올려놓고
				rank_name[9] = dlg_name.m_Name;		// 다시 sorting을 할 것이다. 
			}

			int tmp_int;
			CString tmp_str;

			for(i=0;i<10;i++)							// 점수 순서대로 등수를 재 정렬한다.
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
			for(i=0;i<10;i++)						// 재 정렬한 순위를 파일에 다시 저장.
			{
				//
				CString output;
				output.Format(L"%s",rank_name[i]);
				//const char *temp_rank_name[i]= (const char*)rank_name[i].GetBuffer(100);
				itoa(rank_score[i], tmp_char, 10);
				fout<<CW2A(output)<<endl;
				//원래 있던것fout<<rank_name[i]<<"\n";
				fout<<rank_score[i]<<"\n";
			}
			fout.close();
			//////////////////////////

			CRankDlg dlg_rank;						// 순위보기 대화상자 보기.
			dlg_rank.DoModal();
		}
	}

	///중급일 경우에 랭킹 등록
	else if(pDoc->m_level==2)
	{
		ifstream fin;
		fin.open("rank2.txt");
		char data[80];


		for(i = 0 ; i<10 ; i++)				// 랭킹 파일로 부터 순위정보를 읽어옴.
		{
			fin.getline(data, 80);			// 파일에 두줄씩 읽게 되는데
			rank_name[i] = data;			// 첫번째 줄에는 이름,
			fin.getline(data, 80);			// 두번째 줄에는 점수가 저장되어 있다.
			rank_score[i] = atoi(data);		// 실제로 20줄을 읽게 되는 것이다.
		}

		fin.close();

		for(i=9; i>=0; i--)
		{
			if(rank_name[i] == "")
			{
				rank_name[i] = "등록 되어 있지 않음";
				rank_score[i] = 999999;
			}
			else
				break;
		}
		///////////////////////////////

		if(pDoc->m_time < rank_score[9])					///최저 시간보다  게임 수행 시간이짧을 경우
		{
			CNameDlg dlg_name;						// 사용자로 부터 이름을 입력받는다.
			if(dlg_name.DoModal() == IDOK)
			{
				rank_score[9] = pDoc->m_time	;		// 일단 점수와 이름을 순위 10등에 올려놓고
				rank_name[9] = dlg_name.m_Name;		// 다시 sorting을 할 것이다. 
			}

			int tmp_int;
			CString tmp_str;
			//

			for(i=0;i<10;i++)							// 점수 순서대로 등수를 재 정렬한다.
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
			for(i=0;i<10;i++)						// 재 정렬한 순위를 파일에 다시 저장.
			{
				//
				CString output;
				output.Format(L"%s",rank_name[i]);
				//const char *temp_rank_name[i]= (const char*)rank_name[i].GetBuffer(100);
				itoa(rank_score[i], tmp_char, 10);
				fout<<CW2A(output)<<endl;
				//원래 있던것fout<<rank_name[i]<<"\n";
				fout<<rank_score[i]<<"\n";
			}
			fout.close();
			//////////////////////////

			CRankDlg dlg_rank;						// 순위보기 대화상자 보기.
			dlg_rank.DoModal();
		}
	}
	////////////고급 일경우에 랭킹등록
	else
	{
		ifstream fin;
		fin.open("rank3.txt");
		char data[80];


		for(i = 0 ; i<10 ; i++)				// 랭킹 파일로 부터 순위정보를 읽어옴.
		{
			fin.getline(data, 80);			// 파일에 두줄씩 읽게 되는데
			rank_name[i] = data;			// 첫번째 줄에는 이름,
			fin.getline(data, 80);			// 두번째 줄에는 점수가 저장되어 있다.
			rank_score[i] = atoi(data);		// 실제로 20줄을 읽게 되는 것이다.
		}

		fin.close();

		for(i=9; i>=0; i--)
		{
			if(rank_name[i] == "")
			{
				rank_name[i] = "등록 되어 있지 않음";
				rank_score[i] = 999999;
			}
			else
				break;
		}
		///////////////////////////////

		if(pDoc->m_time < rank_score[9])					///최저 시간보다  게임 수행 시간이짧을 경우
		{
			CNameDlg dlg_name;						// 사용자로 부터 이름을 입력받는다.
			if(dlg_name.DoModal() == IDOK)
			{
				rank_score[9] = pDoc->m_time	;		// 일단 점수와 이름을 순위 10등에 올려놓고
				rank_name[9] = dlg_name.m_Name;		// 다시 sorting을 할 것이다. 
			}

			int tmp_int;
			CString tmp_str;

			//

			//

			for(i=0;i<10;i++)							// 점수 순서대로 등수를 재 정렬한다.
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
			for(i=0;i<10;i++)						// 재 정렬한 순위를 파일에 다시 저장.
			{
				//
				CString output;
				output.Format(L"%s",rank_name[i]);
				//const char *temp_rank_name[i]= (const char*)rank_name[i].GetBuffer(100);
				itoa(rank_score[i], tmp_char, 10);
				fout<<CW2A(output)<<endl;
				//원래 있던것fout<<rank_name[i]<<"\n";
				fout<<rank_score[i]<<"\n";
			}
			fout.close();
			//////////////////////////

			CRankDlg dlg_rank;						// 순위보기 대화상자 보기.
			dlg_rank.DoModal();
		}
	}

}

void CEndDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//다이얼로그에서 Doc멤버변수 사용하기
	CMainFrame *pFrame = (CMainFrame*) AfxGetMainWnd();

	CGameView *pView = (CGameView*)pFrame->GetActiveView(); // 활성화된 뷰의 포인터 구한다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}




void CEndDlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CDialog::OnOK();
}
