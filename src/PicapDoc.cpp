// PicapDoc.cpp : implementation of the CPicapDoc class
//

#include "stdafx.h"
#include "Picap.h"

#include "PicapDoc.h"
#include "strings.h"
#include "OptionsDlg.h"

#include <cxcore.h>
#include <highgui.h>

// For wchar_t *
#include <atlconv.h>

// for find method
#include <algorithm>

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
	: m_findHandle(NULL)
	, m_currentFolder("")
{
	// TODO: add one-time construction code here

}

CPicapDoc::~CPicapDoc()
{
	if (m_findHandle)
	{
		FindClose(m_findHandle);
	}
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

BOOL CPicapDoc::UpdateFileList(CString path)
{
	// if the folder is changed, the file list needs to be updated
	CString folder = GetFolderByPath(path);
	if (IsFolderChanged(folder))
	{
		m_currentFolder = folder;
		if (!BuildFileList(folder))
		{
			return FALSE;
		}
		// file iterator needs to be updated
		if (!UpdateFileIterator(path))
		{
			return FALSE;
		}
	}

	return TRUE;
}

CString CPicapDoc::GetFolderByPath(CString path) const
{
	return path.Left(path.ReverseFind(_T('\\')));
}

CString CPicapDoc::GetFileNameByPath(CString path) const
{
	return path.Right(path.GetLength() - path.ReverseFind(_T('\\')) - 1);
}

BOOL CPicapDoc::IsFolderChanged(CString newFolder) const
{
	if (m_currentFolder.IsEmpty() || m_currentFolder != newFolder)
		return TRUE;

	return FALSE;
}

BOOL CPicapDoc::BuildFileList(CString newFolder)
{
	if (m_findHandle)
	{
		FindClose(m_findHandle);
		m_findHandle = NULL;
	}

	newFolder += _T("\\*");
	m_findHandle = FindFirstFile(newFolder, &m_findData);
	if (m_findHandle == INVALID_HANDLE_VALUE) 
	{
		CString errorStr = INVALID_FILE_HANDLE_STR;
		errorStr.Format(_T("%s GetLastError reports %d"), INVALID_FILE_HANDLE_STR, GetLastError());
		return FALSE;
	} 
	else 
	{
		m_fileList.clear();
		if (IsImageFormat(m_findData.cFileName))
		{
			m_fileList.push_back(m_findData.cFileName);
		}
		while (FindNextFile(m_findHandle, &m_findData) != 0)
		{
			if (IsImageFormat(m_findData.cFileName))
			{
				m_fileList.push_back(m_findData.cFileName);
			}
		}

		FindClose(m_findHandle);
		m_findHandle = NULL;
	}

	return TRUE;
}

BOOL CPicapDoc::UpdateFileIterator(CString path)
{
	if (m_fileList.empty() || path.IsEmpty())
	{
		return FALSE;
	}

	CString fileName = GetFileNameByPath(path);
	m_fileIter = std::find(m_fileList.begin(), m_fileList.end(), fileName);
	if (m_fileIter == m_fileList.end())
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPicapDoc::IsImageFormat(CString fileName)
{
	int index = fileName.ReverseFind(_T('.'));
	if (-1 == index)
	{
		return FALSE;
	}

	CString ext = fileName.Right(fileName.GetLength() - index - 1);
	CString imgFormat[4] = {
		_T("bmp"),
		_T("jpg"),
		_T("png"),
		_T("gif")
	};
	BOOL isFind = FALSE;
	for (int i = 0; i < 4; i++)
	{
		if (ext == imgFormat[i])
		{
			isFind = TRUE;
		}
	}

	return isFind;
}

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

BOOL CPicapDoc::IsWithinImage(CPoint point)
{
	return COptionsDlg::GetInstance()->IsPositionAvailable(point);
}

BOOL CPicapDoc::OpenNextImage()
{
	if (m_fileList.empty())
	{
		return TRUE;
	}

	if (++m_fileIter == m_fileList.end())
	{
		--m_fileIter;
		AfxMessageBox(LAST_FILE_STR);
		return FALSE;
	}

	AfxGetApp()->OpenDocumentFile(m_currentFolder + _T("\\") + *m_fileIter);
	return TRUE;
}

BOOL CPicapDoc::OpenPreviousImage()
{
	if (m_fileList.empty())
	{
		return TRUE;
	}

	if (m_fileIter == m_fileList.begin())
	{
		AfxMessageBox(LAST_FILE_STR);
		return FALSE;
	}

	AfxGetApp()->OpenDocumentFile(m_currentFolder + _T("\\") + *(--m_fileIter));
	return TRUE;
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

	if (!UpdateFileList(CString(lpszPathName)))
	{
		AfxMessageBox(UPDATE_FILE_LIST_FAILED_STR);
		return FALSE;
	}

	// TODO:  Add your specialized creation code here
	if (!LoadImage(CString(lpszPathName)))
	{
		AfxMessageBox(LOAD_IMAGE_FAILED_STR);
		return FALSE;
	}

    COptionsDlg::GetInstance()->SetImageSize(GetImageWidth(), GetImageHeight());

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

