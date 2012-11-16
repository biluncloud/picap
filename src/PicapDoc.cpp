// PicapDoc.cpp : implementation of the CPicapDoc class
//

#include "stdafx.h"
#include "Picap.h"

#include "PicapDoc.h"
#include "strings.h"

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
	ON_COMMAND(ID_FILE_SAVE, &CPicapDoc::OnFileSave)
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
bool CPicapDoc::LoadImage(CString &file_path)
{
	USES_CONVERSION;
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
	if (NULL == m_image.GetImage())
	{
		return false;
	}

	if (!m_ROIRect.IsRectEmpty())
	{
		// If the ROI is selected, only this selected area would be saved
		cvSetImageROI(m_image.GetImage(), 
			cvRect(m_ROIRect.left, m_ROIRect.top, m_ROIRect.Width(), m_ROIRect.Height()));
	}

	USES_CONVERSION;
	bool ret = m_image.Save(W2A(file_path.GetBuffer()));
	cvResetImageROI(m_image.GetImage());

	return ret;
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

void CPicapDoc::ResetROIRect()
{
	m_ROIRect.SetRectEmpty();
}

void CPicapDoc::OnFileSave()
{
	// TODO: Add your command handler code here
	CFileDialog dlg(FALSE, DEFAULT_SAVE_EXT_STR, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, FILE_FILTER_STR);
	if(IDOK == dlg.DoModal())
	{
		if (!SaveImage(dlg.GetFileName()))
		{
			AfxMessageBox(SAVE_IMAGE_FAILED_STR);
		}
	}
}

BOOL CPicapDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  Add your specialized creation code here
	if (!LoadImage(CString(lpszPathName)))
	{
		AfxMessageBox(LOAD_IMAGE_FAILED_STR);
		return FALSE;
	}

	return TRUE;
}

void CPicapDoc::DeleteContents()
{
	// TODO: Add your specialized code here and/or call the base class
	if (NULL != m_image.GetImage())
	{
		m_image.Destroy();
	}

	CDocument::DeleteContents();
}

int CPicapDoc::GetImageWidth()
{
	return (m_image.GetImage() == NULL) ? 0 : m_image.Width();
}

int CPicapDoc::GetImageHeight()
{
	return (m_image.GetImage() == NULL) ? 0 : m_image.Height();
}
