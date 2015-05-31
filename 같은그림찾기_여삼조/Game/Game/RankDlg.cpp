// RankDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Game.h"
#include "RankDlg.h"
#include "afxdialogex.h"


//추가부분
#include <iostream>
#include <fstream>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//

#include "MainFrm.h"
#include "GameDoc.h"

// CRankDlg 대화 상자입니다.
using namespace std;


IMPLEMENT_DYNAMIC(CRankDlg, CDialog)

	CRankDlg::CRankDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRankDlg::IDD, pParent)
{

}

CRankDlg::~CRankDlg()
{
}

void CRankDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
}


BEGIN_MESSAGE_MAP(CRankDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CRankDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_SCORESET, &CRankDlg::OnBnClickedButtonScoreset)
END_MESSAGE_MAP()


// CRankDlg 메시지 처리기입니다.


void CRankDlg::OnBnClickedButtonExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CGameDoc* pDoc = (CGameDoc*)pFrame->GetActiveDocument();
	pDoc->m_bStart = false;
	EndDialog(0);
}


BOOL CRankDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	InsertColumn();				// 리스트 컨트롤의 컬럼 생성
	AddData();					// 데이터를 추가함.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CRankDlg::InsertColumn(void)
{
	CRect rect;
	m_List.GetClientRect(&rect);

	LV_COLUMN col;		// 리스트 컨트롤의 컬럼에 대한 정보를 저장하는 구조체


	col.mask = LVCF_FMT|LVCF_TEXT|LVCF_WIDTH;		// 설정할 항목들을 명시
	col.fmt = LVCFMT_CENTER;						// 컬럼 헤더를 중앙에 출력하도록 함

	for(int i=0; i<3;i++)
	{
		col.iSubItem = i;
		switch(i)
		{
		case 0:				// 첫번째 컬럼 정보 설정
			col.cx = 50;
			col.pszText = L"순위";
			break;

		case 1:				// 두번째 컬럼 정보 설정
			col.cx = 140;
			col.pszText = L"이  름";	
			break;

		case 2:				// 세번째 컬럼 정보 설정
			col.cx = rect.Width() - 190;
			col.pszText = L"점  수  ";
			col.fmt = LVCFMT_RIGHT;
			break;
		}
		m_List.InsertColumn(i, &col);	// 컬럼 추가
	}

	m_List.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);	// 리스트 보기를 목록으로 보기로 설정
}


void CRankDlg::AddData(void)
{
	//Doc에 있는 멤버 변수 사용하기
	CMainFrame *pFrame = (CMainFrame*) AfxGetMainWnd();

	CGameDoc   *pDoc = (CGameDoc*)pFrame->GetActiveDocument();

	if(pDoc->m_level == 1)
	{
		LV_ITEM item;		// 새로운 항목을 추가하려면 LV_ITEM 구조체에 항목에 대한 정보를 담아
		// 리스트 컨트롤의 InsertItem 함수를 이용해 새로운 행을 추가함

		item.iItem = m_List.GetItemCount();
		item.mask = LVIF_TEXT;				// 설정할 항목 명시.
		item.iSubItem = 0;					// 서브컬럼의 인덱스

		ifstream fin;
		fin.open("rank1.txt",ios::in);				// 파일을 연다.
		
		char data[80];
		int i=0;

		CString r_name[10];					// 순위와 점수가 저장될 배열
		CString r_score[10];

		for(int i=0;i<10;i++)				// 순위가 저장된 파일로부터 순위 정보를 읽어옴.
		{					
			fin.getline(data, 80);			// 파일에서 한번에 두줄씩 읽어오는데
			r_name[i] = data;				// 첫번째 줄에는 이름,
			fin.getline(data, 80);			// 두번째 줄에는 점수가 들어있다.
			r_score[i] = data;				// 실제로는 20줄을 읽어온다.
		}
		fin.close();
		char tmp_ch[50];
		CString tmp_str;

		for(int i=9;i>=0;i--)
		{
			itoa(i + 1, tmp_ch, 10);
			if(i != 9)
				tmp_str = "    ";			// 위치를 조정하기 위해 공백을 둠.
			else
				tmp_str = "  ";				// 10위는 두자리므로 공백을 한 칸 작게.

			tmp_str += tmp_ch;
			item.pszText = (LPTSTR)(LPCTSTR)tmp_str;

			m_List.InsertItem(&item);						// 새로운 행 추가함.
			m_List.SetItemText(item.iItem, 1, r_name[i]);	// 각 컬럼의 텍스트 설정
			m_List.SetItemText(item.iItem, 2, r_score[i]);
		}
	}
	//중급일 경우 랭킹 등록
	else if(pDoc->m_level == 2)
	{
		LV_ITEM item;		// 새로운 항목을 추가하려면 LV_ITEM 구조체에 항목에 대한 정보를 담아
		// 리스트 컨트롤의 InsertItem 함수를 이용해 새로운 행을 추가함

		item.iItem = m_List.GetItemCount();
		item.mask = LVIF_TEXT;				// 설정할 항목 명시.
		item.iSubItem = 0;					// 서브컬럼의 인덱스

		ifstream fin;
		fin.open("rank2.txt");				// 파일을 연다.
		char data[80];
		int i=0;

		CString r_name[10];					// 순위와 점수가 저장될 배열
		CString r_score[10];

		for(int i=0;i<10;i++)				// 순위가 저장된 파일로부터 순위 정보를 읽어옴.
		{					
			fin.getline(data, 80);			// 파일에서 한번에 두줄씩 읽어오는데
			r_name[i] = data;				// 첫번째 줄에는 이름,
			fin.getline(data, 80);			// 두번째 줄에는 점수가 들어있다.
			r_score[i] = data;				// 실제로는 20줄을 읽어온다.
		}
		fin.close();

		char tmp_ch[50];
		CString tmp_str;
		for(i=9;i>=0;i--)
		{
			itoa(i + 1, tmp_ch, 10);
			if(i != 9)
				tmp_str = "    ";			// 위치를 조정하기 위해 공백을 둠.
			else
				tmp_str = "  ";				// 10위는 두자리므로 공백을 한 칸 작게.

			tmp_str += tmp_ch;
			item.pszText = (LPTSTR)(LPCTSTR)tmp_str;

			m_List.InsertItem(&item);						// 새로운 행 추가함.
			m_List.SetItemText(item.iItem, 1, r_name[i]);	// 각 컬럼의 텍스트 설정
			m_List.SetItemText(item.iItem, 2, r_score[i]);
		}
	}
	//고급일 경우 랭킹 등록
	else
	{
		LV_ITEM item;		// 새로운 항목을 추가하려면 LV_ITEM 구조체에 항목에 대한 정보를 담아
		// 리스트 컨트롤의 InsertItem 함수를 이용해 새로운 행을 추가함

		item.iItem = m_List.GetItemCount();
		item.mask = LVIF_TEXT;				// 설정할 항목 명시.
		item.iSubItem = 0;					// 서브컬럼의 인덱스

		ifstream fin;
		fin.open("rank3.txt");				// 파일을 연다.
		char data[80];
		int i=0;

		CString r_name[10];					// 순위와 점수가 저장될 배열
		CString r_score[10];

		for(int i=0;i<10;i++)				// 순위가 저장된 파일로부터 순위 정보를 읽어옴.
		{					
			fin.getline(data, 80);			// 파일에서 한번에 두줄씩 읽어오는데
			r_name[i] = data;				// 첫번째 줄에는 이름,
			fin.getline(data, 80);			// 두번째 줄에는 점수가 들어있다.
			r_score[i] = data;				// 실제로는 20줄을 읽어온다.
		}
		fin.close();

		char tmp_ch[50];
		CString tmp_str;
		for(i=9;i>=0;i--)
		{
			itoa(i + 1, tmp_ch, 10);
			if(i != 9)
				tmp_str = "    ";			// 위치를 조정하기 위해 공백을 둠.
			else
				tmp_str = "  ";				// 10위는 두자리므로 공백을 한 칸 작게.

			tmp_str += tmp_ch;
			item.pszText = (LPTSTR)(LPCTSTR)tmp_str;

			m_List.InsertItem(&item);						// 새로운 행 추가함.
			m_List.SetItemText(item.iItem, 1, r_name[i]);	// 각 컬럼의 텍스트 설정
			m_List.SetItemText(item.iItem, 2, r_score[i]);
		}
	}
}


void CRankDlg::OnBnClickedButtonScoreset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//Doc에 있는 멤버 변수 사용하기
	CMainFrame *pFrame = (CMainFrame*) AfxGetMainWnd();	
	CGameDoc   *pDoc = (CGameDoc*)pFrame->GetActiveDocument();	
	CString rank_name[10];			// 랭킹 파일로 부터 읽어 저장할 이름과 점수 배열,
	int rank_score[10];
	int i=0;
	ifstream fin;
	fin.open("rank1.txt");
	char data[80];
	for(i = 0 ; i<10 ; i++)				// 랭킹 파일로 부터 순위정보를 읽어옴.
	{
		fin.getline(data, 80);			// 파일에 두줄씩 읽게 되는데
		rank_name[i] = data;			// 첫번째 줄에는 이름,
		fin.getline(data, 80);			// 두번째 줄에는 점수가 저장되어 있다.
		rank_score[i] = atoi(data);		// 실제로 20줄을 읽게 되는 것이다.		////
		rank_name[i]=(_T("등록 되지 않음"));
		rank_score[i]=999999;
	}	fin.close();
	////////////////////	
	char tmp_char[20]={999999};
	ofstream fout("rank1.txt");

	for(int i=0; i<10 ; i++)
	{
		CString output;
		output.Format(L"%s",rank_name[i]);
		//const char *temp_rank_name[i]= (const char*)rank_name[i].GetBuffer(100);
		itoa(rank_score[i], tmp_char, 10);
		fout<<CW2A(output)<<endl;
		//원래 있던것fout<<rank_name[i]<<"\n";
		fout<<rank_score[i]<<"\n";
	}
	fout.close();		
	
	int temp = 0;
	temp++;
	
	if(temp == 1){
		EndDialog(0);	
		CRankDlg dlg_rank;						// 순위보기 대화상자 보기.
		dlg_rank.DoModal();
	}
}
