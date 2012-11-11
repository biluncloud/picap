// PicapDoc.cpp : implementation of the CPicapDoc class
//

#include "stdafx.h"
#include "Picap.h"

#include "PicapDoc.h"

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
