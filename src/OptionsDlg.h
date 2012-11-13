#pragma once


// COptionsDlg dialog

class COptionsDlg : public CDialog
{
	DECLARE_DYNAMIC(COptionsDlg)

public:
	COptionsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionsDlg();

// Dialog Data
	enum { IDD = IDD_OPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// The width factor of Width:Heigth
	int m_widthFactor;
	// The height factor of Width:Height
	int m_heigthFactor;
	int m_minWidth;
	int m_maxWidth;
	int m_minHeight;
	int m_maxHeight;
	int m_step;
};
