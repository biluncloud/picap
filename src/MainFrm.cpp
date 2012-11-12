// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Picap.h"

#include "MainFrm.h"
#include "PicapDoc.h"
#include "strings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_OPEN, &CMainFrame::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CMainFrame::OnFileSave)
	ON_COMMAND(ID_TOOL_OPTION, &CMainFrame::OnToolOption)
	ON_WM_CHAR()
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




void CMainFrame::OnFileOpen()
{
	// TODO: Add your command handler code here
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, FILE_FILTER_STR);
	if(IDOK == dlg.DoModal())
	{
		CPicapDoc *pDoc = (CPicapDoc *)GetActiveDocument();
		if (!pDoc->OpenImage(dlg.GetFileName()))
		{
			MessageBox(OPEN_IMAGE_FAILED_STR);
			return;
		}
	}
}

void CMainFrame::OnFileSave()
{
	// TODO: Add your command handler code here
	CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, FILE_FILTER_STR);
	if(IDOK == dlg.DoModal())
	{
		CPicapDoc *pDoc = (CPicapDoc *)GetActiveDocument();
		if ((NULL == pDoc) || (NULL == pDoc->GetImage().GetImage()))
		{
			MessageBox(SAVE_IMAGE_NOT_READY_STR);
			return;
		}
		if (!pDoc->SaveImage(dlg.GetFileName()))
		{
			MessageBox(SAVE_IMAGE_FAILED_STR);
		}
	}
}

void CMainFrame::OnToolOption()
{
	// TODO: Add your command handler code here
	CPicapDoc *pDoc = (CPicapDoc *)GetActiveDocument();
	if (!pDoc->SetParameters())
	{
		MessageBox(SET_PARAM_FAILED_STR);
	}
}

void CMainFrame::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	switch (nChar)
	{
	case VK_ESCAPE: 
        // Process an escape. 
        
        break; 

    case VK_RETURN: 
        // Process a carriage return. 
         
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

	CFrameWnd::OnChar(nChar, nRepCnt, nFlags);
}
