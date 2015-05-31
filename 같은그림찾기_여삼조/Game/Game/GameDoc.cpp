
// GameDoc.cpp : CGameDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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


// CGameDoc 생성/소멸

CGameDoc::CGameDoc()
	: m_strGame(_T(""))
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
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

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.
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
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CGameDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
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

// 검색 처리기를 지원합니다.
void CGameDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CGameDoc 진단

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


// CGameDoc 명령


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
