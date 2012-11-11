// PicapView.cpp : implementation of the CPicapView class
//

#include "stdafx.h"
#include "Picap.h"

#include "PicapDoc.h"
#include "PicapView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPicapView

IMPLEMENT_DYNCREATE(CPicapView, CView)

BEGIN_MESSAGE_MAP(CPicapView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CHAR()
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
	pDoc->GetImage().DrawToHDC(pDC->m_hDC, &rect);

	// Draw the rectangle area
	if (m_isStarted)
	{
		CBrush brush;
		brush.CreateStockObject(NULL_BRUSH);
		CPen pen(PS_DASH, 1, RGB(0, 0, 0));
		
		CBrush* pOldBrush=pDC->SelectObject(&brush);
		CPen* pOldPen = pDC->SelectObject(&pen);

		pDC->Rectangle(CalcBoundRect(m_startPoint, m_finishPoint));

		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);
	}
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
		if (m_isStarted && !m_isFinished)
		{
			// ReleaseCapture();

			m_isFinished = TRUE;
			m_finishPoint = point;

			CPicapDoc* pDoc = GetDocument();
			CRect ROIRect = CalcBoundRect(m_startPoint, m_finishPoint);
			pDoc->SetROIRect(ROIRect);
			
			InvalidateRect(&ROIRect);
		}
		// The first point is already set, this time is the second point
		else
		{
			// SetCapture();

			m_isStarted = TRUE;
			m_isFinished = FALSE;

			CPicapDoc* pDoc = GetDocument();
			CRect ROIRect = CalcBoundRect(m_startPoint, m_finishPoint);
			InvalidateRect(&ROIRect);

			m_startPoint = point;
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
			CRect ROIRect = CalcBoundRect(m_startPoint, m_finishPoint);
			InvalidateRect(&ROIRect);

			m_finishPoint = point;
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

void CPicapView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnChar(nChar, nRepCnt, nFlags);
}

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
