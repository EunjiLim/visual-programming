
// GameDoc.cpp : CGameDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Game.h"
#endif

#include "GameDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGameDoc
#include "GameView.h"
#include "MainFrm.h"
#include "LevelBoxDlg.h"

IMPLEMENT_DYNCREATE(CGameDoc, CDocument)

BEGIN_MESSAGE_MAP(CGameDoc, CDocument)
END_MESSAGE_MAP()


// CGameDoc ����/�Ҹ�

CGameDoc::CGameDoc()
	: m_strGame(_T(""))
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
	m_bmCell = CSize(79, 81);
	m_bLevel = true;
	m_time = 0;

	if(m_bLevel)
	{
		LevelBoxDlg dlg;
		m_level = dlg.DoModal();
		m_bLevel = false;
	}

	if(m_level == 0)
	{
		exit(0);
	}
	else if(m_level == 1)
	{
		m_nRow = 3;
		m_nCol = 4;
		m_nHint = 1;
	}
	else if(m_level == 2)
	{
		m_nRow = 5;
		m_nCol = 6;
		m_nHint = 2;
	}
	else if(m_level == 3)
	{
		m_nRow = 6;
		m_nCol = 7;
		m_nHint = 3;
	}

	m_bRandom = true;
	m_bStart = false;
	m_bPause = true;

	for(int n=0; n < m_nRow; n++)
		for(int m=0; m < m_nCol; m++)
			m_bShow[n][m] = false;

	m_nBmpFirstID = m_nBmpSecondID = 0;
	m_bMouse = false;
}

CGameDoc::~CGameDoc()
{
}

BOOL CGameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.
	if(m_bLevel)
	{
		LevelBoxDlg dlg;
		m_level = dlg.DoModal();
		m_bLevel = false;
	}
	if(m_level == 0)
	{
		exit(0);
	}
	else if(m_level == 1)
	{
		m_nRow = 3;
		m_nCol = 4;
		m_nHint = 1;
	}
	else if(m_level == 2)
	{
		m_nRow = 4;
		m_nCol = 5;
		m_nHint = 2;
	}
	else if(m_level == 3)
	{
		m_nRow = 5;
		m_nCol = 6;
		m_nHint = 3;
	}

	m_bRandom = true;
	m_bStart = false;
	m_bPause = true;

	m_time = 0;
	m_strGame = _T("");

	for(int n=0; n < m_nRow; n++)
		for(int m=0; m < m_nCol; m++)
			m_bShow[n][m] = false;
			
	m_nBmpFirstID = m_nBmpSecondID = 0;
	m_bMouse = false;

	return TRUE;
}


// CGameDoc serialization

void CGameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CGameDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// �˻� ó���⸦ �����մϴ�.
void CGameDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CGameDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGameDoc ����

#ifdef _DEBUG
void CGameDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGameDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGameDoc ���


void CGameDoc::ResizeWindow(void)
{
	CMainFrame* pMain = (CMainFrame*) AfxGetMainWnd();

	CREATESTRUCT st;
	CREATESTRUCT& rst = st;

	pMain->PreCreateWindow(rst);

	rst.lpszName = _T("Game");
	rst.cx = (m_nRow + 1) * m_bmCell.cx + 180;
	rst.cy = (m_nCol + 1) * m_bmCell.cy + 100;

	CRect rect;
	pMain->GetClientRect(rect);
	pMain->MoveWindow(rect.left, rect.top, rst.cx, rst.cy);
}


void CGameDoc::OnRandom(void)
{
	srand((unsigned)time(NULL));

	BOOL bInsert = true;

	int nGrating = m_nRow * m_nCol;

	for(int n=0; n < nGrating; n++)
	{
		m_nRnd[n] = (rand() % (nGrating / 2)) + 1;

		for(int m=0; m < n; m++)
		{
			if(m_nRnd[n] == m_nRnd[m])
			{
				if(bInsert == false)
				{
					n--;
					bInsert = true;
					break;
				}
				bInsert = false;
			}
		}
	}

	int nCount = 0;

	for(int n=0; n<m_nRow; n++)
	{
		for(int m=0; m<m_nCol; m++)
		{
			m_nBmpID[n][m] = m_nRnd[nCount];
			nCount++;
		}
	}
}

void CGameDoc::Wait(DWORD Millisecond)
{
	MSG msg;
	DWORD dwStart;
	dwStart = GetTickCount();

	while(GetTickCount() - dwStart < Millisecond)
	{
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
