#pragma once


// COptionsDlg dialog
class COptionsDlg : public CDialog
{
	DECLARE_DYNAMIC(COptionsDlg)

public:
    static COptionsDlg *GetInstance();

// Dialog Data
	enum { IDD = IDD_OPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// The width factor of Width:Height
	int m_widthFactor;
	// The height factor of Width:Height
	int m_heigthFactor;
	int m_minWidth;
	int m_maxWidth;
	int m_minHeight;
	int m_maxHeight;
	int m_stepWidth;
	int m_stepHeight;

public:
	// This method will give the position within all the restriction
	// The nearest position to the current point will be given
	CPoint GetNextPosition(CPoint firstPt, CPoint currentPt) const;
	afx_msg void OnBnClickedDefault();

private:
    // Explict constructor is forbidden
	COptionsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionsDlg();

    static COptionsDlg *m_instance;

    // The copy constructor and assign operator are forbidden
    COptionsDlg(COptionsDlg &rhs);
    COptionsDlg &operator = (COptionsDlg &rhs);
};
