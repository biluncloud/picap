// PicapView.cpp : implementation of the CPicapView class
//

#include "stdafx.h"
#include "Picap.h"

#include "PicapDoc.h"
#include "PicapView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef MIN
#define MIN(a, b)  ((a) > (b) ? (b) : (a))
#endif

#ifndef MAX
#define MAX(a, b)  ((a) < (b) ? (b) : (a))
#endif

// CPicapView

IMPLEMENT_DYNCREATE(CPicapView, CView)

BEGIN_MESSAGE_MAP(CPicapView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
//	ON_WM_CHAR()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_TOOL_UNSELECT, &CPicapView::OnToolUnselect)
END_MESSAGE_MAP()

// CPicapView construction/destruction

CPicapView::CPicapView()
	: m_isStarted(FALSE)
	, m_isFinished(FALSE)
{
	// TODO: add construction code here

}

CPicapView::~CPicapView()
{
}

BOOL CPicapView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPicapView drawing

void CPicapView::OnDraw(CDC* pDC)
{
	CPicapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	// Draw the image first
	if (NULL == pDoc->GetImage().GetImage())
	{
		return;
	}

	RECT rect = {
		0,
		0, 
		pDoc->GetImage().Width() - 1, 
		pDoc->GetImage().Height() - 1
	};

	// Buffering for rendering
	CDC dcCompatible;
	dcCompatible.CreateCompatibleDC(pDC);	
	CBitmap bitmapCompatible;
	bitmapCompatible.CreateCompatibleBitmap(pDC, pDoc->GetImage().Width(), pDoc->GetImage().Height());
	CBitmap* pOldBitmap = dcCompatible.SelectObject(&bitmapCompatible);
	pDoc->GetImage().DrawToHDC(dcCompatible.m_hDC, &rect);
		
	CRect clientRect;
	GetClientRect(&clientRect);

	CDC dcCompatibleBk;
	CBitmap bitmapCompatibleBk;
	bitmapCompatibleBk.CreateCompatibleBitmap(pDC, clientRect.Width(), clientRect.Height());
	dcCompatibleBk.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmapBk = dcCompatibleBk.SelectObject(&bitmapCompatibleBk);
	dcCompatibleBk.FillSolidRect(&clientRect, RGB(192, 192, 192));

	// Draw the rectangle area
	if (m_isStarted)
	{
		CBrush brush;
		brush.CreateStockObject(NULL_BRUSH);
		CPen pen(PS_DOT, 1, RGB(0, 0, 0));
		
		CBrush* pOldBrush=dcCompatible.SelectObject(&brush);
		CPen* pOldPen = dcCompatible.SelectObject(&pen);

		dcCompatible.Rectangle(CalcBoundRect(m_startPoint, m_finishPoint));

		dcCompatible.SelectObject(pOldPen);
		dcCompatible.SelectObject(pOldBrush);
	}

	dcCompatibleBk.BitBlt(0, 0, pDoc->GetImage().Width(), pDoc->GetImage().Height(), &dcCompatible, 0, 0, SRCCOPY);
	pDC->BitBlt(0, 0, clientRect.Width(), clientRect.Height(), &dcCompatibleBk, 0, 0, SRCCOPY);

	dcCompatible.SelectObject(pOldBitmap);
	dcCompatibleBk.SelectObject(pOldBitmapBk);
}


// CPicapView diagnostics

#ifdef _DEBUG
void CPicapView::AssertValid() const
{
	CView::AssertValid();
}

void CPicapView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPicapDoc* CPicapView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPicapDoc)));
	return (CPicapDoc*)m_pDocument;
}
#endif //_DEBUG


// CPicapView message handlers

void CPicapView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (IsImageOpened())
	{
		// The first point is already set, this time is the second point
		if (m_isStarted && !m_isFinished)
		{
			m_isFinished = TRUE;
			CMainFrame* pFrame = (CMainFrame* )GetParentFrame();
			m_finishPoint = pFrame->GetNextPosition(m_startPoint, point);

			CPicapDoc* pDoc = GetDocument();
			CRect ROIRect = CalcBoundRect(m_startPoint, m_finishPoint);
			pDoc->SetROIRect(ROIRect);
			
			InvalidateRect(&ROIRect);
		}
		else
		{
			m_isStarted = TRUE;
			m_isFinished = FALSE;

			CPicapDoc* pDoc = GetDocument();
			CRect ROIRect = CalcBoundRect(m_startPoint, m_finishPoint, point);
			InvalidateRect(&ROIRect);

			m_startPoint = m_finishPoint = point;
		}
	}

	CView::OnLButtonDown(nFlags, point);
}

void CPicapView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (IsImageOpened())
	{
		if (m_isStarted && !m_isFinished)
		{
			CPicapDoc* pDoc = GetDocument();
			CRect ROIRect = CalcBoundRect(m_startPoint, m_finishPoint, point);
			InvalidateRect(&ROIRect);

			CMainFrame* pFrame = (CMainFrame* )GetParentFrame();
			m_finishPoint = pFrame->GetNextPosition(m_startPoint, point);
		}
	}

	CView::OnMouseMove(nFlags, point);
}

void CPicapView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (IsImageOpened())
	{
		return;
	}

	CView::OnLButtonUp(nFlags, point);
}

//void CPicapView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: Add your message handler code here and/or call default
//
//	switch (nChar)
//	{
//	case VK_ESCAPE: 
//        // Process an escape. 
//        
//        break; 
//
//    case VK_RETURN: 
//        // Process a carriage return. 
//         
//        break; 
//
//    case VK_LEFT: 
//        break; 
//
//    case VK_RIGHT: 
//        break; 
//
//    case VK_UP: 
//        break; 
//
//    case VK_DOWN: 
//        break; 
//		
//    case VK_PRIOR: 
//        break; 
//
//    case VK_NEXT: 
//        break; 
//
//    case VK_HOME: 
//        break; 
//
//    case VK_END: 
//        break; 
//
//	default:
//		break;
//	}
// 
//	CView::OnChar(nChar, nRepCnt, nFlags);
//}

// Calculate the bound rect of this two point
CRect CPicapView::CalcBoundRect(const CPoint &pt1, const CPoint &pt2)
{
	CPoint topLeftPt, bottomRight;
	topLeftPt.x = (pt1.x < pt2.x) ? pt1.x : pt2.x;
	topLeftPt.y = (pt1.y < pt2.y) ? pt1.y : pt2.y;

	bottomRight.x = (pt1.x >= pt2.x) ? pt1.x : pt2.x;
	bottomRight.y = (pt1.y >= pt2.y) ? pt1.y : pt2.y;

	return CRect(topLeftPt, bottomRight);
}

// Calculate the bound rect of this three point
CRect CPicapView::CalcBoundRect(const CPoint &pt1, const CPoint &pt2, const CPoint &pt3)
{
	CPoint topLeftPt, bottomRight;
	topLeftPt.x = MIN(MIN(pt1.x, pt2.x), pt3.x);
	topLeftPt.y = MIN(MIN(pt1.y, pt2.y), pt3.y);

	bottomRight.x = MAX(MAX(pt1.x, pt2.x), pt3.x);
	bottomRight.y = MAX(MAX(pt1.y, pt2.y), pt3.y);

	return CRect(topLeftPt, bottomRight);
}

BOOL CPicapView::IsImageOpened() const
{
	CPicapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return FALSE;
	}

	if (NULL == pDoc->GetImage().GetImage())
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPicapView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	// If the image is opened, don't erase the background
	CPicapDoc* pDoc = GetDocument();
	if (pDoc && (NULL != pDoc->GetImage().GetImage()))
		return TRUE;

	// Just draw the white background
	CRect clientRect;
	GetClientRect(&clientRect);

	CDC dcCompatibleBk;
	CBitmap bitmapCompatibleBk;
	bitmapCompatibleBk.CreateCompatibleBitmap(pDC, clientRect.Width(), clientRect.Height());
	dcCompatibleBk.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmapBk = dcCompatibleBk.SelectObject(&bitmapCompatibleBk);
	dcCompatibleBk.FillSolidRect(&clientRect, RGB(192,192,192));

	pDC->BitBlt(0, 0, clientRect.Width(), clientRect.Height(), &dcCompatibleBk, 0, 0, SRCCOPY);

	dcCompatibleBk.SelectObject(pOldBitmapBk);

	// To avoid flashing
	return TRUE;
	// return CView::OnEraseBkgnd(pDC);
}

void CPicapView::OnToolUnselect()
{
	// TODO: Add your command handler code here
	CPicapDoc* pDoc = GetDocument();
	pDoc->ResetROIRect();

	if (m_isStarted && m_isFinished)
	{
		CRect ROIRect = CalcBoundRect(m_startPoint, m_finishPoint);
		InvalidateRect(&ROIRect);
	}

	m_isStarted = m_isFinished = FALSE;
}
