
// GameDoc.h : CGameDoc Ŭ������ �������̽�
//


#pragma once
#include "atltypes.h"


class CGameDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CGameDoc();
	DECLARE_DYNCREATE(CGameDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	CBitmap m_bmp[10][10];
	CSize m_bmCell;
	int m_nRow;
	int m_nCol;
	void ResizeWindow(void);
	int m_nRnd[100];
	UINT m_nBmpID[10][10];
	bool m_bRandom;
	void OnRandom(void);
	bool m_bShow[10][10];
	int m_nRowIndex;
	int m_nColIndex;
	UINT m_nBmpFirstID;
	UINT m_nBmpSecondID;
	bool m_bMouse;
	int m_level;
	bool m_bStart;
	bool m_bLevel;
	void Wait(DWORD Millisecond);
	int m_time;
	int m_nHint;
	CString m_strGame;
	bool m_bPause;
};
