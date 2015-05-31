
// GameView.cpp : CGameView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Game.h"
#endif

#include "GameDoc.h"
#include "GameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGameView
#include "LevelBoxDlg.h"
#include "RankDlg.h"
#include "EndDlg.h"
IMPLEMENT_DYNCREATE(CGameView, CView)

BEGIN_MESSAGE_MAP(CGameView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGameView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_LEVEL1, &CGameView::OnLevel1)
	ON_UPDATE_COMMAND_UI(ID_LEVEL1, &CGameView::OnUpdateLevel1)
	ON_COMMAND(ID_LEVEL2, &CGameView::OnLevel2)
	ON_UPDATE_COMMAND_UI(ID_LEVEL2, &CGameView::OnUpdateLevel2)
	ON_COMMAND(ID_LEVEL3, &CGameView::OnLevel3)
	ON_UPDATE_COMMAND_UI(ID_LEVEL3, &CGameView::OnUpdateLevel3)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_COMMAND(ID_MENU_RESTART, &CGameView::OnMenuRestart)
	ON_COMMAND(ID_MENU_NEW, &CGameView::OnMenuNew)
	ON_COMMAND(ID_MENU_RANK, &CGameView::OnMenuRank)
END_MESSAGE_MAP()

// CGameView 생성/소멸

CGameView::CGameView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	nMatchCount = 0;
	m_bShowCard = true;
}

CGameView::~CGameView()
{
	delete m_button_start;
	delete m_button_pause;
	delete m_button_hint;
}

BOOL CGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGameView 그리기
void CGameView::OnDraw(CDC* pDC)
{
	CGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	CString str1, str2, str3;
	CString str4, str5, str6, str7;

	CRect rect;
	this->GetClientRect(&rect);

	str1.Format(_T("맞춘 카드"));
	str2.Format(_T("시간"));
	str3.Format(_T("남은 카드"));

	str4.Format(_T("%d"), nMatchCount);
	str5.Format(_T("%d"), pDoc->m_time);
	str6.Format(_T("%d"), (pDoc->m_nRow)*(pDoc->m_nCol)/2-nMatchCount);

	str7.Format(_T("남은 힌트 : %d"), pDoc->m_nHint);
	pDC->SetTextColor(RGB(0, 0, 100));
	
	CFont myFont, *pOldFont;
	myFont.CreateFont(15, 0, 0, 0, FW_NORMAL, false, false, false, DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("돋움체"));
	pOldFont = pDC->SelectObject(&myFont);
	
	pDC->TextOutW(rect.Width()/4-30, 30, str1);
	pDC->TextOutW(rect.Width()/2, 30, str2);
	pDC->TextOutW(rect.Width()/4*3-25, 30, str3);

	pDC->TextOutW(rect.Width()/4-30, rect.Height()-40, str7);

	pDC->SelectObject(pOldFont);
	myFont.DeleteObject();

	myFont.CreateFont(15, 0, 0, 0, FW_BOLD, false, false, false, DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("돋움체"));
	pOldFont = pDC->SelectObject(&myFont);

	pDC->TextOutW(rect.Width()/4, 50, str4);
	pDC->TextOutW(rect.Width()/2+10, 50, str5);
	pDC->TextOutW(rect.Width()/4*3+10, 50, str6);
	pDC->TextOutW(rect.Width()/4*3-20, rect.Height()-40, pDoc->m_strGame);
	
	pDC->SelectObject(pOldFont);
	myFont.DeleteObject();

	if(pDoc->m_bRandom)
	{
		pDoc->OnRandom();
		pDoc->m_bRandom = false;
	}

	int nCount = 0;

	CDC memDC;
	CBitmap* pOldBmp;

	memDC.CreateCompatibleDC(pDC);
	// false이면 가려짐
	for(int n=0; n<pDoc->m_nRow; n++)
	{
		for(int m=0; m<pDoc->m_nCol; m++)
		{
			if(pDoc->m_bShow[n][m] == true)
			{
				pDoc->m_bmp[n][m].LoadBitmap(IDB_BITMAP1 + pDoc->m_nRnd[nCount]);

				pOldBmp = memDC.SelectObject(&pDoc->m_bmp[n][m]);

				pDC->BitBlt(pDoc->m_bmCell.cx*(m+1), pDoc->m_bmCell.cy*(n+1),
					pDoc->m_bmCell.cx, pDoc->m_bmCell.cy,
					&memDC, 0, 0, SRCCOPY);

				pDoc->m_bmp[n][m].DeleteObject();
			}

			nCount++;
			
			if(pDoc->m_bShow[n][m] == false)
			{
				CBitmap bmp;
				bmp.LoadBitmap(IDB_BITMAP1);
				pOldBmp = memDC.SelectObject(&bmp);

				pDC->BitBlt(pDoc->m_bmCell.cx*(m+1), pDoc->m_bmCell.cy*(n+1),
					pDoc->m_bmCell.cx, pDoc->m_bmCell.cy,
					&memDC, 0, 0, SRCCOPY);
				bmp.DeleteObject();
			}
		}
	}

	memDC.SelectObject(pOldBmp);
	pDoc->ResizeWindow();
}

// CGameView 인쇄


void CGameView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}


BOOL CGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CGameView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGameView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGameView 진단

#ifdef _DEBUG
void CGameView::AssertValid() const
{
	CView::AssertValid();
}

void CGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGameDoc* CGameView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGameDoc)));
	return (CGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CGameView 메시지 처리기


void CGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CGameDoc* pDoc = GetDocument();

	if(pDoc->m_bStart == false || pDoc->m_bPause == true)
	{
		AfxMessageBox(_T("시작 버튼을 눌러주세요^.~"));
		return;
	}

	pDoc->m_nRowIndex = point.y / pDoc->m_bmCell.cy - 1;
	pDoc->m_nColIndex = point.x / pDoc->m_bmCell.cx - 1;

	if( pDoc->m_bShow[pDoc->m_nRowIndex][pDoc->m_nColIndex] == true
		|| pDoc->m_nBmpSecondID != 0
		|| pDoc->m_nRowIndex > pDoc->m_nRow - 1
		|| pDoc->m_nRowIndex > pDoc->m_nCol - 1
		|| pDoc->m_nRowIndex < 0
		|| pDoc->m_nColIndex < 0)
		return;

	// 마우스가 가지고 있는 인덱스 값의 그림을 보여줌
	pDoc->m_bShow[pDoc->m_nRowIndex][pDoc->m_nColIndex] = true;

	CRect rect;
	SetRect(&rect, pDoc->m_nRowIndex * (pDoc->m_bmCell.cx + 1),
		pDoc->m_nColIndex * (pDoc->m_bmCell.cy + 1),
		pDoc->m_nRowIndex * (pDoc->m_bmCell.cy + 2),
		pDoc->m_nColIndex * (pDoc->m_bmCell.cy + 2));
	InvalidateRect(rect);

	// 마우스가 클릭한 곳의 인덱스 및 그림 아이디 저장
	if(pDoc->m_nBmpFirstID == 0)
	{
		pDoc->m_nBmpFirstID = pDoc->m_nBmpID[pDoc->m_nRowIndex][pDoc->m_nColIndex];
		m_nRowTempIndex = pDoc->m_nRowIndex;
		m_nColTempIndex = pDoc->m_nColIndex;
		pDoc->m_bMouse = true;
	}
	else
	{
		pDoc->m_nBmpSecondID = pDoc->m_nBmpID[pDoc->m_nRowIndex][pDoc->m_nColIndex];
		pDoc->m_bMouse = false;
	}

	OnMatching();
	CView::OnLButtonDown(nFlags, point);
}

void CGameView::OnMatching(void)
{
	CGameDoc* pDoc = GetDocument();

	if(pDoc->m_nBmpFirstID == pDoc->m_nBmpSecondID
		&& pDoc->m_bMouse == false)
	{
		pDoc->m_bShow[m_nRowTempIndex][m_nColTempIndex] = true;
		pDoc->m_bShow[pDoc->m_nRowIndex][pDoc->m_nColIndex] = true;
		pDoc->m_nBmpFirstID = pDoc->m_nBmpSecondID = 0;
		m_nRowTempIndex = m_nColTempIndex = 0;

		nMatchCount++;
	}
	else if(pDoc->m_nBmpFirstID != pDoc->m_nBmpSecondID && pDoc->m_bMouse==false)
	{
		CDC*	pDC = GetDC();
		CDC		memDC;
		CBitmap	bmp;

		memDC.CreateCompatibleDC(pDC);
		bmp.LoadBitmap(IDB_BITMAP1 + pDoc->m_nBmpSecondID);

		CBitmap* pOldBmp = memDC.SelectObject(&bmp);
		pDC->BitBlt(pDoc->m_bmCell.cx * (pDoc->m_nColIndex + 1),
			pDoc->m_bmCell.cy * (pDoc->m_nRowIndex + 1),
			pDoc->m_bmCell.cx, pDoc->m_bmCell.cy,
			&memDC, 0, 0, SRCCOPY);

		bmp.DeleteObject();
		memDC.SelectObject(pOldBmp);
		Sleep(400);

		pDoc->m_bShow[m_nRowTempIndex][m_nColTempIndex] = false;
		pDoc->m_bShow[pDoc->m_nRowIndex][pDoc->m_nColIndex] = false;
		pDoc->m_nBmpFirstID = pDoc->m_nBmpSecondID = 0;
		m_nRowTempIndex = m_nColTempIndex = 0;
	}

	Invalidate();
	if(nMatchCount == (pDoc->m_nRow * pDoc->m_nCol)/2)
	{
		pDoc->m_bStart = false;
		Invalidate();
		OnSuccess();
	}
}


void CGameView::OnSuccess(void)
{
	CGameDoc* pDoc = GetDocument();
	CString strMsg1, strMsg2;
	strMsg1.Format(_T("게임 기록: %d"), pDoc->m_time);
	strMsg2.Format(_T("다시 시작하시겠습니까?"));

	CEndDlg dlg;
	dlg.m_strScore = strMsg1;
	dlg.m_strOver = strMsg2;
	
	int res = dlg.DoModal();

	if(res == 2)
	{
		pDoc->m_bRandom = true;

		for(int n=0; n < pDoc->m_nRow; n++)
			for(int m=0; m < pDoc->m_nCol; m++)
				pDoc->m_bShow[n][m] = false;

		pDoc->m_nBmpFirstID = pDoc->m_nBmpSecondID = 0;
		pDoc->m_bMouse = false;
		nMatchCount = 0;
		m_bShowCard = true;
		pDoc->OnNewDocument();
	}
}

void CGameView::OnLevel1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGameDoc* pDoc = GetDocument();
	pDoc->m_level = 1;

	pDoc->m_strGame = _T("");
	pDoc->m_nHint = 1;
	nMatchCount = 0;
	pDoc->OnNewDocument();
	Invalidate();
}

void CGameView::OnUpdateLevel1(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CGameDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->m_level == 1);
}

void CGameView::OnLevel2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGameDoc* pDoc = GetDocument();
	pDoc->m_level = 2;

	pDoc->m_strGame = _T("");
	pDoc->m_nHint = 2;
	nMatchCount = 0;

	pDoc->OnNewDocument();
	Invalidate();
}

void CGameView::OnUpdateLevel2(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CGameDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->m_level == 2);
}

void CGameView::OnLevel3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGameDoc* pDoc = GetDocument();
	pDoc->m_level = 3;

	pDoc->m_strGame = _T("");
	pDoc->m_nHint = 3;
	nMatchCount = 0;

	pDoc->OnNewDocument();

	Invalidate();
}

void CGameView::OnUpdateLevel3(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CGameDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->m_level == 3);
}


void CGameView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CGameDoc* pDoc = GetDocument();
	
	if(pDoc->m_bStart) 
		pDoc->m_time++;
	Invalidate();

	CView::OnTimer(nIDEvent);
}


void CGameView::OnMenuRestart()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGameDoc* pDoc = GetDocument();
	nMatchCount = 0;
	pDoc->OnNewDocument();
}



void CGameView::OnMenuNew()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CGameDoc* pDoc = GetDocument();

	pDoc->m_bLevel = true;
	m_bShowCard = true;
	pDoc->m_time = 0;
	nMatchCount = 0;
	pDoc->OnNewDocument();
}


void CGameView::OnMenuRank()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	KillTimer(1);
	CGameDoc* pDoc = GetDocument();
	pDoc->m_strGame = _T("일시 정지중");
	pDoc->m_bPause = true;
	Invalidate();

	CRankDlg dlg;
	dlg.DoModal();
}



void CGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_button_start.Create(NULL, BS_OWNERDRAW,
		CRect(10, 100, 70, 160), this, 100);
	m_button_start.LoadBitmaps(IDB_BITMAP_START, IDB_BITMAP_START_DOWN, IDB_BITMAP_START_DOWN);

	m_button_pause.Create(NULL, BS_OWNERDRAW,
		CRect(10, 170, 70, 230), this, 101);
	m_button_pause.LoadBitmaps(IDB_BITMAP_PAUSE, IDB_BITMAP_PAUSE_DOWN, IDB_BITMAP_PAUSE_DOWN);

	m_button_hint.Create(NULL, BS_OWNERDRAW,
		CRect(10, 240, 70, 300), this, 102);
	m_button_hint.LoadBitmaps(IDB_BITMAP_HINT, IDB_BITMAP_HINT_DOWN, IDB_BITMAP_HINT_DOWN);
	// 기본이미지, 눌렀을때, 포커스온, 비활성화

	m_button_start.ShowWindow(SW_SHOW);
	m_button_pause.ShowWindow(SW_SHOW);
	m_button_hint.ShowWindow(SW_SHOW);
}

BOOL CGameView::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CGameDoc* pDoc = GetDocument();

	CDC* pDC = GetDC();
	CRect rect;
	this->GetClientRect(&rect);
	
	if(wParam == 100)
	{
		if(pDoc->m_bPause == true)
		{
			if(pDoc->m_bStart == false)
			{
				ShowCard();
				pDoc->m_bStart = true;
			}
			pDoc->m_bPause = false;
			SetTimer(1, 1000, NULL);

			pDoc->m_strGame = _T("게임중");
			Invalidate();
		}
		else
			return false;
	}

	if(wParam == 101)
	{
		if(pDoc->m_bPause == true)
			return false;

		else
		{
			KillTimer(1);
			pDoc->m_bPause = true;
			pDoc->m_strGame = _T("일시 정지중");
			Invalidate();
		}
	}

	if(wParam == 102)
	{
		if(pDoc->m_bStart == false || pDoc->m_bPause == true)
		{
			return false;
		}
		
		KillTimer(1);
		if(pDoc->m_nHint > 0)
		{
			pDoc->m_bPause = true;
			AfxMessageBox(_T("전체 카드를 4초간 보여줍니다.\n힌트를 사용하시면 시간기록이 5초 추가됩니다."));
			CString str;
			str.Format(_T("남은 힌트 : %d개\n힌트를 사용하시겠습니까?"), pDoc->m_nHint);
			int res = AfxMessageBox(str, MB_YESNO);
			if(res == IDYES)
			{
				m_bShowCard = true;
				pDoc->m_nHint--;
				ShowCard();
				pDoc->m_time += 5;
				m_bShowCard = false;
			}
		}
		else
			AfxMessageBox(_T("힌트를 모두 사용하였습니다."));

		pDoc->m_bPause = false;
		SetTimer(1, 1000, NULL);
	}

	return CView::OnCommand(wParam, lParam);
}


void CGameView::ShowCard(void)
{
	if(!m_bShowCard)
		return;

	CGameDoc* pDoc = GetDocument();

	CDC memDC;
	CBitmap* pOldBmp;
	CDC* pDC = GetDC();

	int nCount = 0;
	bool m_bShowNow[10][10];

	memDC.CreateCompatibleDC(pDC);
	// false이면 가려짐
	
	for(int n=0; n < pDoc->m_nRow; n++)
		for(int m=0; m < pDoc->m_nCol; m++)
			m_bShowNow[n][m] = pDoc->m_bShow[n][m];

	for(int n=0; n < pDoc->m_nRow; n++)
		for(int m=0; m < pDoc->m_nCol; m++)
			pDoc->m_bShow[n][m] = true;

	for(int n=0; n<pDoc->m_nRow; n++)
	{
		for(int m=0; m<pDoc->m_nCol; m++)
		{
			pDoc->m_bmp[n][m].LoadBitmap(IDB_BITMAP1 + pDoc->m_nRnd[nCount]);

			pOldBmp = memDC.SelectObject(&pDoc->m_bmp[n][m]);

			pDC->BitBlt(pDoc->m_bmCell.cx*(m+1), pDoc->m_bmCell.cy*(n+1),
				pDoc->m_bmCell.cx, pDoc->m_bmCell.cy,
				&memDC, 0, 0, SRCCOPY);

			pDoc->m_bmp[n][m].DeleteObject();

			nCount++;
		}
	}

	pDoc->Wait(4000);

	nCount = 0;
	for(int n=0; n<pDoc->m_nRow; n++)
	{
		for(int m=0; m<pDoc->m_nCol; m++)
		{
			pDoc->m_bShow[n][m] = m_bShowNow[n][m];
			if(pDoc->m_bShow[n][m] == false)
			{
				CBitmap bmp;
				bmp.LoadBitmap(IDB_BITMAP1);
				pOldBmp = memDC.SelectObject(&bmp);

				pDC->BitBlt(pDoc->m_bmCell.cx*(m+1), pDoc->m_bmCell.cy*(n+1),
					pDoc->m_bmCell.cx, pDoc->m_bmCell.cy,
					&memDC, 0, 0, SRCCOPY);
				bmp.DeleteObject();
			}

			else 
			{
				pDC->BitBlt(pDoc->m_bmCell.cx*(m+1), pDoc->m_bmCell.cy*(n+1),
					pDoc->m_bmCell.cx, pDoc->m_bmCell.cy,
					&memDC, 0, 0, SRCCOPY);

				pDoc->m_bmp[n][m].DeleteObject();

				nCount++;
			}
		}
	}
	Invalidate();
	ReleaseDC(pDC);
}
