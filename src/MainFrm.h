// MainFrm.h : interface of the CMainFrame class
//


#pragma once

#include "OptionsDlg.h"

class CPicapDoc;

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:
	const COptionsDlg *GetOptions() const;

	// This method will give the position within all the restriction
	// The nearest position to the current point will be given
	CPoint GetNextPosition(CPoint firstPt, CPoint currentPt) const;

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnToolOption();

// Attributes
private:
	COptionsDlg m_options;
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};


