
// GameDoc.h : CGameDoc 클래스의 인터페이스
//


#pragma once
#include "atltypes.h"


class CGameDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CGameDoc();
	DECLARE_DYNCREATE(CGameDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
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
