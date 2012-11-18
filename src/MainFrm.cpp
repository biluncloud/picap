// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Picap.h"

#include "MainFrm.h"
#include "PicapDoc.h"
#include "PicapView.h"
#include "strings.h"
#include "OptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_TOOL_OPTION, &CMainFrame::OnToolOption)
//	ON_WM_DROPFILES()
ON_COMMAND(ID_TOOL_UNSELECT, &CMainFrame::OnToolUnselect)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnToolOption()
{
	// TODO: Add your command handler code here
    COptionsDlg::GetInstance()->DoModal();
}

void CMainFrame::OnToolUnselect()
{
	// TODO: Add your command handler code here
	((CPicapView *)GetActiveView())->UnselectRegion();
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	CPicapDoc *pDoc = (CPicapDoc *)GetActiveDocument();
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_ESCAPE: 
	        // Process an escape. 
			OnToolUnselect();
	        break; 

	    case VK_RETURN: 
	        // Process a carriage return. 
			//pDoc->OnFileSave();
	AfxGetApp()->OpenDocumentFile(_T("C:\\Documents and Settings\\Administrator\\×ÀÃæ\\ÉêÍ¬Ñ§\\2.jpg"));
	        break; 

	    case VK_LEFT: 
	        break; 

	    case VK_RIGHT: 
	        break; 

	    case VK_UP: 
	        break; 

	    case VK_DOWN: 
	        break; 
			
	    case VK_PRIOR: 
	        break; 

	    case VK_NEXT: 
	        break; 

	    case VK_HOME: 
	        break; 

	    case VK_END: 
	        break; 

		default:
			break;
		}
	}

	return CFrameWnd::PreTranslateMessage(pMsg);
}
