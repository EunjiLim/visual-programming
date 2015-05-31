// RankDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Game.h"
#include "RankDlg.h"
#include "afxdialogex.h"


//�߰��κ�
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

// CRankDlg ��ȭ �����Դϴ�.
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


// CRankDlg �޽��� ó�����Դϴ�.


void CRankDlg::OnBnClickedButtonExit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CGameDoc* pDoc = (CGameDoc*)pFrame->GetActiveDocument();
	pDoc->m_bStart = false;
	EndDialog(0);
}


BOOL CRankDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	InsertColumn();				// ����Ʈ ��Ʈ���� �÷� ����
	AddData();					// �����͸� �߰���.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CRankDlg::InsertColumn(void)
{
	CRect rect;
	m_List.GetClientRect(&rect);

	LV_COLUMN col;		// ����Ʈ ��Ʈ���� �÷��� ���� ������ �����ϴ� ����ü


	col.mask = LVCF_FMT|LVCF_TEXT|LVCF_WIDTH;		// ������ �׸���� ���
	col.fmt = LVCFMT_CENTER;						// �÷� ����� �߾ӿ� ����ϵ��� ��

	for(int i=0; i<3;i++)
	{
		col.iSubItem = i;
		switch(i)
		{
		case 0:				// ù��° �÷� ���� ����
			col.cx = 50;
			col.pszText = L"����";
			break;

		case 1:				// �ι�° �÷� ���� ����
			col.cx = 140;
			col.pszText = L"��  ��";	
			break;

		case 2:				// ����° �÷� ���� ����
			col.cx = rect.Width() - 190;
			col.pszText = L"��  ��  ";
			col.fmt = LVCFMT_RIGHT;
			break;
		}
		m_List.InsertColumn(i, &col);	// �÷� �߰�
	}

	m_List.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);	// ����Ʈ ���⸦ ������� ����� ����
}


void CRankDlg::AddData(void)
{
	//Doc�� �ִ� ��� ���� ����ϱ�
	CMainFrame *pFrame = (CMainFrame*) AfxGetMainWnd();

	CGameDoc   *pDoc = (CGameDoc*)pFrame->GetActiveDocument();

	if(pDoc->m_level == 1)
	{
		LV_ITEM item;		// ���ο� �׸��� �߰��Ϸ��� LV_ITEM ����ü�� �׸� ���� ������ ���
		// ����Ʈ ��Ʈ���� InsertItem �Լ��� �̿��� ���ο� ���� �߰���

		item.iItem = m_List.GetItemCount();
		item.mask = LVIF_TEXT;				// ������ �׸� ���.
		item.iSubItem = 0;					// �����÷��� �ε���

		ifstream fin;
		fin.open("rank1.txt",ios::in);				// ������ ����.
		
		char data[80];
		int i=0;

		CString r_name[10];					// ������ ������ ����� �迭
		CString r_score[10];

		for(int i=0;i<10;i++)				// ������ ����� ���Ϸκ��� ���� ������ �о��.
		{					
			fin.getline(data, 80);			// ���Ͽ��� �ѹ��� ���پ� �о���µ�
			r_name[i] = data;				// ù��° �ٿ��� �̸�,
			fin.getline(data, 80);			// �ι�° �ٿ��� ������ ����ִ�.
			r_score[i] = data;				// �����δ� 20���� �о�´�.
		}
		fin.close();
		char tmp_ch[50];
		CString tmp_str;

		for(int i=9;i>=0;i--)
		{
			itoa(i + 1, tmp_ch, 10);
			if(i != 9)
				tmp_str = "    ";			// ��ġ�� �����ϱ� ���� ������ ��.
			else
				tmp_str = "  ";				// 10���� ���ڸ��Ƿ� ������ �� ĭ �۰�.

			tmp_str += tmp_ch;
			item.pszText = (LPTSTR)(LPCTSTR)tmp_str;

			m_List.InsertItem(&item);						// ���ο� �� �߰���.
			m_List.SetItemText(item.iItem, 1, r_name[i]);	// �� �÷��� �ؽ�Ʈ ����
			m_List.SetItemText(item.iItem, 2, r_score[i]);
		}
	}
	//�߱��� ��� ��ŷ ���
	else if(pDoc->m_level == 2)
	{
		LV_ITEM item;		// ���ο� �׸��� �߰��Ϸ��� LV_ITEM ����ü�� �׸� ���� ������ ���
		// ����Ʈ ��Ʈ���� InsertItem �Լ��� �̿��� ���ο� ���� �߰���

		item.iItem = m_List.GetItemCount();
		item.mask = LVIF_TEXT;				// ������ �׸� ���.
		item.iSubItem = 0;					// �����÷��� �ε���

		ifstream fin;
		fin.open("rank2.txt");				// ������ ����.
		char data[80];
		int i=0;

		CString r_name[10];					// ������ ������ ����� �迭
		CString r_score[10];

		for(int i=0;i<10;i++)				// ������ ����� ���Ϸκ��� ���� ������ �о��.
		{					
			fin.getline(data, 80);			// ���Ͽ��� �ѹ��� ���پ� �о���µ�
			r_name[i] = data;				// ù��° �ٿ��� �̸�,
			fin.getline(data, 80);			// �ι�° �ٿ��� ������ ����ִ�.
			r_score[i] = data;				// �����δ� 20���� �о�´�.
		}
		fin.close();

		char tmp_ch[50];
		CString tmp_str;
		for(i=9;i>=0;i--)
		{
			itoa(i + 1, tmp_ch, 10);
			if(i != 9)
				tmp_str = "    ";			// ��ġ�� �����ϱ� ���� ������ ��.
			else
				tmp_str = "  ";				// 10���� ���ڸ��Ƿ� ������ �� ĭ �۰�.

			tmp_str += tmp_ch;
			item.pszText = (LPTSTR)(LPCTSTR)tmp_str;

			m_List.InsertItem(&item);						// ���ο� �� �߰���.
			m_List.SetItemText(item.iItem, 1, r_name[i]);	// �� �÷��� �ؽ�Ʈ ����
			m_List.SetItemText(item.iItem, 2, r_score[i]);
		}
	}
	//����� ��� ��ŷ ���
	else
	{
		LV_ITEM item;		// ���ο� �׸��� �߰��Ϸ��� LV_ITEM ����ü�� �׸� ���� ������ ���
		// ����Ʈ ��Ʈ���� InsertItem �Լ��� �̿��� ���ο� ���� �߰���

		item.iItem = m_List.GetItemCount();
		item.mask = LVIF_TEXT;				// ������ �׸� ���.
		item.iSubItem = 0;					// �����÷��� �ε���

		ifstream fin;
		fin.open("rank3.txt");				// ������ ����.
		char data[80];
		int i=0;

		CString r_name[10];					// ������ ������ ����� �迭
		CString r_score[10];

		for(int i=0;i<10;i++)				// ������ ����� ���Ϸκ��� ���� ������ �о��.
		{					
			fin.getline(data, 80);			// ���Ͽ��� �ѹ��� ���پ� �о���µ�
			r_name[i] = data;				// ù��° �ٿ��� �̸�,
			fin.getline(data, 80);			// �ι�° �ٿ��� ������ ����ִ�.
			r_score[i] = data;				// �����δ� 20���� �о�´�.
		}
		fin.close();

		char tmp_ch[50];
		CString tmp_str;
		for(i=9;i>=0;i--)
		{
			itoa(i + 1, tmp_ch, 10);
			if(i != 9)
				tmp_str = "    ";			// ��ġ�� �����ϱ� ���� ������ ��.
			else
				tmp_str = "  ";				// 10���� ���ڸ��Ƿ� ������ �� ĭ �۰�.

			tmp_str += tmp_ch;
			item.pszText = (LPTSTR)(LPCTSTR)tmp_str;

			m_List.InsertItem(&item);						// ���ο� �� �߰���.
			m_List.SetItemText(item.iItem, 1, r_name[i]);	// �� �÷��� �ؽ�Ʈ ����
			m_List.SetItemText(item.iItem, 2, r_score[i]);
		}
	}
}


void CRankDlg::OnBnClickedButtonScoreset()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//Doc�� �ִ� ��� ���� ����ϱ�
	CMainFrame *pFrame = (CMainFrame*) AfxGetMainWnd();	
	CGameDoc   *pDoc = (CGameDoc*)pFrame->GetActiveDocument();	
	CString rank_name[10];			// ��ŷ ���Ϸ� ���� �о� ������ �̸��� ���� �迭,
	int rank_score[10];
	int i=0;
	ifstream fin;
	fin.open("rank1.txt");
	char data[80];
	for(i = 0 ; i<10 ; i++)				// ��ŷ ���Ϸ� ���� ���������� �о��.
	{
		fin.getline(data, 80);			// ���Ͽ� ���پ� �а� �Ǵµ�
		rank_name[i] = data;			// ù��° �ٿ��� �̸�,
		fin.getline(data, 80);			// �ι�° �ٿ��� ������ ����Ǿ� �ִ�.
		rank_score[i] = atoi(data);		// ������ 20���� �а� �Ǵ� ���̴�.		////
		rank_name[i]=(_T("��� ���� ����"));
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
		//���� �ִ���fout<<rank_name[i]<<"\n";
		fout<<rank_score[i]<<"\n";
	}
	fout.close();		
	
	int temp = 0;
	temp++;
	
	if(temp == 1){
		EndDialog(0);	
		CRankDlg dlg_rank;						// �������� ��ȭ���� ����.
		dlg_rank.DoModal();
	}
}
