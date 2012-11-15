// OptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Picap.h"
#include "OptionsDlg.h"

// default settings
const int g_defWidthFactor = 1;
const int g_defHeigthFactor = 2;
const int g_defMinWidth = 40;
const int g_defMaxWidth = 95;
const int g_defMinHeight = 80;
const int g_defMaxHeight = 190;
const int g_defStepWidth = 5;
const int g_defStepHeight = 10;

// COptionsDlg dialog

IMPLEMENT_DYNAMIC(COptionsDlg, CDialog)

COptionsDlg::COptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsDlg::IDD, pParent)
	, m_widthFactor(g_defWidthFactor)
	, m_heigthFactor(g_defHeigthFactor)
	, m_minWidth(g_defMinWidth)
	, m_maxWidth(g_defMaxWidth)
	, m_minHeight(g_defMinHeight)
	, m_maxHeight(g_defMaxHeight)
	, m_stepWidth(g_defStepWidth)
	, m_stepHeight(g_defStepHeight)
{

}

COptionsDlg::~COptionsDlg()
{
}

void COptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_widthFactor);
	DDV_MinMaxInt(pDX, m_widthFactor, 1, 65535);
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
	DDX_Text(pDX, IDC_EDIT7, m_stepWidth);
	DDV_MinMaxInt(pDX, m_stepWidth, 1, 65535);
	
	m_stepHeight = m_stepWidth * m_heigthFactor / m_widthFactor;
}


BEGIN_MESSAGE_MAP(COptionsDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &COptionsDlg::OnBnClickedDefault)
END_MESSAGE_MAP()


// COptionsDlg message handlers

CPoint COptionsDlg::GetNextPosition(CPoint firstPt, CPoint currentPt) const
{
	CPoint candidatePt;
	currentPt -= firstPt;

	int factor = currentPt.x * currentPt.y >= 0 ? 1 : -1;

	if (m_widthFactor >= m_heigthFactor)
	{
		int xFactor = currentPt.x >= 0 ? 1 : -1;
		if (currentPt.x * xFactor < m_minWidth)
		{
			currentPt.x = m_minWidth * xFactor;
		}
		else if (currentPt.x * xFactor > m_maxWidth)
		{
			currentPt.x = m_maxWidth * xFactor;
		}
		else
		{
			currentPt.x = ((currentPt.x * xFactor - m_minWidth) / m_stepWidth * m_stepWidth + m_minWidth ) * xFactor;
		}
		candidatePt.x = currentPt.x;
		candidatePt.y = candidatePt.x * m_heigthFactor / m_widthFactor;
		candidatePt.y *= factor;
	}
	else
	{
		int yFactor = currentPt.y >= 0 ? 1 : -1;
		if (currentPt.y * yFactor < m_minHeight)
		{
			currentPt.y = m_minHeight * yFactor;
		}
		else if (currentPt.y * yFactor > m_maxHeight)
		{
			currentPt.y = m_maxHeight * yFactor;
		}
		else
		{
			currentPt.y = ((currentPt.y * yFactor - m_minHeight) / m_stepHeight * m_stepHeight + m_minHeight) * yFactor;
		}

		candidatePt.y = currentPt.y;
		candidatePt.x = candidatePt.y * m_widthFactor / m_heigthFactor;
		candidatePt.x *= factor;
	}

	return candidatePt + firstPt;
}
void COptionsDlg::OnBnClickedDefault()
{
	// TODO: Add your control notification handler code here
	m_widthFactor = g_defWidthFactor;
	m_heigthFactor = g_defHeigthFactor;
	m_minWidth = g_defMinWidth;
	m_maxWidth = g_defMaxWidth;
	m_minHeight = g_defMinHeight;
	m_maxHeight = g_defMaxHeight;
	m_stepWidth = g_defStepWidth;
	m_stepHeight = g_defStepHeight;
	
	UpdateData(FALSE);
}
