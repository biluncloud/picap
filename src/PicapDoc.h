// PicapDoc.h : interface of the CPicapDoc class
//


#pragma once


class CPicapDoc : public CDocument
{
protected: // create from serialization only
	CPicapDoc();
	DECLARE_DYNCREATE(CPicapDoc)

// Attributes
public:

// Operations
public:

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
};


