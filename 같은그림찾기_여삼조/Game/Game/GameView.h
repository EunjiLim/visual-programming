
// GameView.h : CGameView 클래스의 인터페이스
//

#pragma once
#include "afxwin.h"
#include "afxext.h"


class CGameView : public CView
{
protected: // serialization에서만 만들어집니다.
	CGameView();
	DECLARE_DYNCREATE(CGameView)

// 특성입니다.
public:
	CGameDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	UINT m_nRowTempIndex;
	UINT m_nColTempIndex;
	int nMatchCount;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMatching(void);
	void OnSuccess(void);
	afx_msg void OnLevel1();
	afx_msg void OnUpdateLevel1(CCmdUI *pCmdUI);
	afx_msg void OnLevel2();
	afx_msg void OnUpdateLevel2(CCmdUI *pCmdUI);
	afx_msg void OnLevel3();
	afx_msg void OnUpdateLevel3(CCmdUI *pCmdUI);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMenuRestart();
	afx_msg void OnMenuNew();
	afx_msg void OnMenuRank();
	virtual void OnInitialUpdate();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	void ShowCard(void);
	bool m_bShowCard;
	int m_nHint;
	CBitmapButton m_button_start;
	CBitmapButton m_button_pause;
	CBitmapButton m_button_hint;
};

#ifndef _DEBUG  // GameView.cpp의 디버그 버전
inline CGameDoc* CGameView::GetDocument() const
   { return reinterpret_cast<CGameDoc*>(m_pDocument); }
#endif