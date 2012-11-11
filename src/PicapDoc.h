// PicapDoc.h : interface of the CPicapDoc class
//


#pragma once

#include <highgui.h>

class CPicapDoc : public CDocument
{
protected: // create from serialization only
	CPicapDoc();
	DECLARE_DYNCREATE(CPicapDoc)

// Attributes
public:

// Operations
public:
	bool OpenImage(CString &file_path);
	bool SaveImage(CString &file_path);
	bool SetParameters();
	CvvImage &GetImage();
	const CRect &GetROIRect() const;
	void SetROIRect(const CRect &rect);

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

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

// Attributes
private:
	bool DestroyData();

private:
	CvvImage m_image;
	CRect m_ROIRect;
};


