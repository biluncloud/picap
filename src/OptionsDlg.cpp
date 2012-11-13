// OptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Picap.h"
#include "OptionsDlg.h"


// COptionsDlg dialog

IMPLEMENT_DYNAMIC(COptionsDlg, CDialog)

COptionsDlg::COptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsDlg::IDD, pParent)
	, m_widthFactor(1)
	, m_heigthFactor(2)
	, m_minWidth(40)
	, m_maxWidth(95)
	, m_minHeight(80)
	, m_maxHeight(190)
	, m_step(5)
{

}

COptionsDlg::~COptionsDlg()
{
}

void COptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_widthFactor);
	DDV_MinMaxInt(pDX, m_widthFactor, 0, 65535);
	DDX_Text(pDX, IDC_EDIT2, m_heigthFactor);
	DDV_MinMaxInt(pDX, m_heigthFactor, 1, 65535);
	DDX_Text(pDX, IDC_EDIT3, m_minWidth);
	DDV_MinMaxInt(pDX, m_minWidth, 0, 65535);
	DDX_Text(pDX, IDC_EDIT4, m_maxWidth);
	DDV_MinMaxInt(pDX, m_maxWidth, 0, 65535);
	DDX_Text(pDX, IDC_EDIT5, m_minHeight);
	DDV_MinMaxInt(pDX, m_minHeight, 0, 65535);
	DDX_Text(pDX, IDC_EDIT6, m_maxHeight);
	DDV_MinMaxInt(pDX, m_maxHeight, 0, 65535);
	DDX_Text(pDX, IDC_EDIT7, m_step);
	DDV_MinMaxInt(pDX, m_step, 0, 65535);
}


BEGIN_MESSAGE_MAP(COptionsDlg, CDialog)
END_MESSAGE_MAP()


// COptionsDlg message handlers