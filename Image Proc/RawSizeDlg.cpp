// RawSizeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Image Proc.h"
#include "RawSizeDlg.h"
#include "afxdialogex.h"


// CRawSizeDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRawSizeDlg, CDialog)

CRawSizeDlg::CRawSizeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_RAW_SIZE, pParent)
	, m_Raw_width(0)
	, m_Raw_height(0)
{

}

CRawSizeDlg::~CRawSizeDlg()
{
}

void CRawSizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Raw_width);
	DDV_MinMaxInt(pDX, m_Raw_width, 0, 512);
	DDX_Text(pDX, IDC_EDIT2, m_Raw_height);
	DDV_MinMaxInt(pDX, m_Raw_height, 0, 512);
}


BEGIN_MESSAGE_MAP(CRawSizeDlg, CDialog)
END_MESSAGE_MAP()


// CRawSizeDlg 메시지 처리기입니다.
