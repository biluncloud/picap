// PicapDoc.cpp : implementation of the CPicapDoc class
//

#include "stdafx.h"
#include "Picap.h"

#include "PicapDoc.h"

#include <cxcore.h>
#include <highgui.h>

// For wchar_t *
#include <atlconv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPicapDoc

IMPLEMENT_DYNCREATE(CPicapDoc, CDocument)

BEGIN_MESSAGE_MAP(CPicapDoc, CDocument)
END_MESSAGE_MAP()


// CPicapDoc construction/destruction

CPicapDoc::CPicapDoc()
{
	// TODO: add one-time construction code here

}

CPicapDoc::~CPicapDoc()
{
}

BOOL CPicapDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CPicapDoc serialization

void CPicapDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CPicapDoc diagnostics

#ifdef _DEBUG
void CPicapDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPicapDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPicapDoc commands
bool CPicapDoc::OpenImage(CString &file_path)
{
	USES_CONVERSION;
	// Destroy the data first
	if (!DestroyData())
	{
		return false;
	}

	m_image.Load(W2A(file_path.GetBuffer()));
	if (NULL == m_image.GetImage())
	{
		return false;
	}

	UpdateAllViews(NULL);

	return true;
}

bool CPicapDoc::SaveImage(CString &file_path)
{
	return true;
}

bool CPicapDoc::SetParameters()
{
	return true;
}

CvvImage &CPicapDoc::GetImage()
{
	return m_image;
}

const CRect &CPicapDoc::GetROIRect() const
{
	return m_ROIRect;
}

void CPicapDoc::SetROIRect(const CRect &rect)
{
	m_ROIRect = rect;
}

bool CPicapDoc::DestroyData()
{
	if (NULL != m_image.GetImage())
	{
		m_image.Destroy();
	}

	return true;
}
