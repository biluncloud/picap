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

void CPicapView::OnDraw(CDC* /*pDC*/)
{
	CPicapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
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
