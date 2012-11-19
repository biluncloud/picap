// PicapDoc.h : interface of the CPicapDoc class
//


#pragma once

#include <highgui.h>
#include <list>

class CPicapDoc : public CDocument
{
protected: // create from serialization only
	CPicapDoc();
	DECLARE_DYNCREATE(CPicapDoc)

// Attributes
public:

// Operations
public:
	bool LoadImage(CString &file_path);
	bool SaveImage(CString &file_path);
	CvvImage &GetImage();
	const CRect &GetROIRect() const;
	void SetROIRect(const CRect &rect);
	void ResetROIRect();
	int GetImageWidth();
	int GetImageHeight();
	BOOL IsWithinImage(CPoint point);

	BOOL OpenNextImage();
	BOOL OpenPreviousImage();

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CPicapDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL UpdateFileList(CString path);
	CString GetFolderByPath(CString path) const;
	CString GetFileNameByPath(CString path) const;
	BOOL IsFolderChanged(CString newFolder) const;
	BOOL BuildFileList(CString newFolder);
	BOOL UpdateFileIterator(CString path);
	BOOL IsImageFormat(CString fileName);

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

// Attributes
private:

private:
	CvvImage m_image;
	CRect m_ROIRect;

	WIN32_FIND_DATA m_findData;
	HANDLE m_findHandle;
	CString m_currentFolder;
	std::list<CString> m_fileList;
	std::list<CString>::iterator m_fileIter;
public:
	afx_msg void OnFileSave();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
};


