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

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PicapView.cpp
inline CPicapDoc* CPicapView::GetDocument() const
   { return reinterpret_cast<CPicapDoc*>(m_pDocument); }
#endif

