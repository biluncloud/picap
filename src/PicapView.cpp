// PicapView.cpp : implementation of the CPicapView class
//

#include "stdafx.h"
#include "Picap.h"

#include "PicapDoc.h"
#include "PicapView.h"
#include "MainFrm.h"
#include "OptionsDlg.h"

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
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CPicapView construction/destruction

CPicapView::CPicapView()
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
	
	// Draw the image on the buffer
	pDoc->GetImage().DrawToHDC(dcCompatible.m_hDC, &rect);
		
	CRect clientRect;
	GetClientRect(&clientRect);

	// Draw the background on the buffer
	CDC dcCompatibleBk;
	CBitmap bitmapCompatibleBk;
	bitmapCompatibleBk.CreateCompatibleBitmap(pDC, clientRect.Width(), clientRect.Height());
	dcCompatibleBk.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmapBk = dcCompatibleBk.SelectObject(&bitmapCompatibleBk);
	dcCompatibleBk.FillSolidRect(&clientRect, RGB(192, 192, 192));

	m_selectedRegion.DrawRegion(&dcCompatible);

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
		int width = GetDocument()->GetImageWidth();
		int height = GetDocument()->GetImageHeight();
		BOOL isWithinImage = !(point.x < 0 || point.x >= width || point.y < 0 || point.y >= height);
		if (isWithinImage)
		{
	        CRect invalidRegion = m_selectedRegion.UpdateRegion(point);
	        if (!invalidRegion.IsRectEmpty())
	        {
	            InvalidateRect(&invalidRegion);
	        }

	        if (m_selectedRegion.IsRegionOK())
	        {
				CPicapDoc* pDoc = GetDocument();
				pDoc->SetROIRect(m_selectedRegion.GetRegion());
	        }
		}

	}

	CView::OnLButtonDown(nFlags, point);
}

void CPicapView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (IsImageOpened())
	{
		int width = GetDocument()->GetImageWidth();
		int height = GetDocument()->GetImageHeight();
		BOOL isWithinImage = !(point.x < 0 || point.x >= width || point.y < 0 || point.y >= height);
		if (isWithinImage)
		{
			CRect invalidRegion = m_selectedRegion.UpdateTrasitionRegion(point);
	        if (!invalidRegion.IsRectEmpty())
	        {
	            InvalidateRect(&invalidRegion);
	        }
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

void CPicapView::UnselectRegion()
{
	// TODO: Add your command handler code here
	CPicapDoc* pDoc = GetDocument();
	pDoc->ResetROIRect();

	m_selectedRegion.ResetRegion();
	// Update all the area
	Invalidate();
	UpdateWindow();
}

CPicapView::CSelectedRegion::CSelectedRegion()
	: m_isStarted(FALSE)
	, m_isFinished(FALSE)
	, m_startPoint(0, 0)
	, m_finishPoint(0, 0)
{
}

void CPicapView::CSelectedRegion::DrawRegion(CDC* pDC)
{
	// Draw the rectangle area
	if (m_isStarted)
	{
		CBrush brush;
		brush.CreateStockObject(NULL_BRUSH);
		CPen pen(PS_DOT, 1, RGB(0, 0, 0));
		
		CBrush* pOldBrush=pDC->SelectObject(&brush);
		CPen* pOldPen = pDC->SelectObject(&pen);

		pDC->Rectangle(CalcBoundRect(m_startPoint, m_finishPoint));

		// Draw the width and height
		CString textStr;
		textStr.Format(_T("%dx%d"), 
			abs(m_finishPoint.x - m_startPoint.x), 
			abs(m_finishPoint.y - m_startPoint.y));
		pDC->DrawText(textStr, 
			CalcBoundRect(m_startPoint, m_finishPoint),
			DT_CENTER | DT_VCENTER);

		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);
	}
}

CRect CPicapView::CSelectedRegion::UpdateRegion(CPoint point)
{
	CRect oldRegion = GetInvalidRegion();
	// The first point is already set, this time the second point will be updated
	if (m_isStarted && !m_isFinished)
	{
		// Update the selected region
		m_isFinished = TRUE;
		m_finishPoint = COptionsDlg::GetInstance()->GetNextPosition(m_startPoint, point);
	}
	else
	{
		// Update the selected region
		m_isStarted = TRUE;
		m_isFinished = FALSE;
		m_startPoint = m_finishPoint = point;
	}

	return oldRegion;
}

CRect CPicapView::CSelectedRegion::UpdateTrasitionRegion(CPoint point)
{
	CRect oldRegion(0, 0, 0, 0);
	if (m_isStarted && !m_isFinished)
	{
		oldRegion = CalcBoundRect(m_startPoint, m_finishPoint);

		m_finishPoint = COptionsDlg::GetInstance()->GetNextPosition(m_startPoint, point);
	}

	return oldRegion;
}

CRect CPicapView::CSelectedRegion::ResetRegion()
{
	CRect oldRegion(0, 0, 0, 0);
	if (m_isStarted && m_isFinished)
	{
		oldRegion = CalcBoundRect(m_startPoint, m_finishPoint);
	}
	m_isStarted = m_isFinished = FALSE;

	return oldRegion;
}

BOOL CPicapView::CSelectedRegion::IsRegionOK() const
{
	if (m_isStarted && m_isFinished)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

// This only returns the selected region, exclude the text area
CRect CPicapView::CSelectedRegion::GetRegion() const
{
    return CalcBoundRect(m_startPoint, m_finishPoint);
}

// Calculate the bound rect of this two point
CRect CPicapView::CSelectedRegion::CalcBoundRect(const CPoint &pt1, const CPoint &pt2) const
{
	CPoint topLeftPt, bottomRight;
	topLeftPt.x = (pt1.x < pt2.x) ? pt1.x : pt2.x;
	topLeftPt.y = (pt1.y < pt2.y) ? pt1.y : pt2.y;

	bottomRight.x = (pt1.x >= pt2.x) ? pt1.x : pt2.x;
	bottomRight.y = (pt1.y >= pt2.y) ? pt1.y : pt2.y;

	return CRect(topLeftPt, bottomRight);
}

// Calculate the bound rect of this three point
CRect CPicapView::CSelectedRegion::CalcBoundRect(const CPoint &pt1, const CPoint &pt2, const CPoint &pt3) const
{
	CPoint topLeftPt, bottomRight;
	topLeftPt.x = MIN(MIN(pt1.x, pt2.x), pt3.x);
	topLeftPt.y = MIN(MIN(pt1.y, pt2.y), pt3.y);

	bottomRight.x = MAX(MAX(pt1.x, pt2.x), pt3.x);
	bottomRight.y = MAX(MAX(pt1.y, pt2.y), pt3.y);

	return CRect(topLeftPt, bottomRight);
}

// This returns the invalid region, include the text area
CRect CPicapView::CSelectedRegion::GetInvalidRegion() const
{
	return CalcBoundRect(m_startPoint, m_finishPoint);
}
