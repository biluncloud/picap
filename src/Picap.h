// Picap.h : main header file for the Picap application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CPicapApp:
// See Picap.cpp for the implementation of this class
//

class CPicapApp : public CWinApp
{
public:
	CPicapApp();


// Overrides
public:
	virtual BOOL InitInstance();
	BOOL SetDragCursor();
	BOOL RestoreCursor();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:
	HCURSOR m_normalCursor;
	HCURSOR m_dragCursor;
};

extern CPicapApp theApp;