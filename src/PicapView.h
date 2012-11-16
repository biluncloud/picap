// PicapView.h : interface of the CPicapView class
//


#pragma once


class CPicapView : public CView
{
protected: // create from serialization only
	CPicapView();
	DECLARE_DYNCREATE(CPicapView)

// Attributes
public:
	CPicapDoc* GetDocument() const;
	BOOL IsImageOpened() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CPicapView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	class CSelectedRegion
	{
	public:
		CSelectedRegion();
		CRect CalcBoundRect(const CPoint &pt1, const CPoint &pt2);
		CRect CalcBoundRect(const CPoint &pt1, const CPoint &pt2, const CPoint &pt3);

		void DrawRegion(CDC* pDC);
	private:
		BOOL m_isStarted;
		BOOL m_isFinished;
		CPoint m_startPoint;
		CPoint m_finishPoint;
	};

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

private:
	CSelectedRegion m_selectedRegion;

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnToolUnselect();
};

#ifndef _DEBUG  // debug version in PicapView.cpp
inline CPicapDoc* CPicapView::GetDocument() const
   { return reinterpret_cast<CPicapDoc*>(m_pDocument); }
#endif

