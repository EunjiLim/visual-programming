
// GameView.h : CGameView Ŭ������ �������̽�
//

#pragma once
#include "afxwin.h"
#include "afxext.h"


class CGameView : public CView
{
protected: // serialization������ ��������ϴ�.
	CGameView();
	DECLARE_DYNCREATE(CGameView)

// Ư���Դϴ�.
public:
	CGameDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
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

#ifndef _DEBUG  // GameView.cpp�� ����� ����
inline CGameDoc* CGameView::GetDocument() const
   { return reinterpret_cast<CGameDoc*>(m_pDocument); }
#endif