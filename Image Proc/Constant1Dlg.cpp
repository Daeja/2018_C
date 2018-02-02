// Constant1Dlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Image Proc.h"
#include "Constant1Dlg.h"
#include "afxdialogex.h"


// CConstant1Dlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CConstant1Dlg, CDialog)

CConstant1Dlg::CConstant1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CONSTANT1, pParent)
	, m_Constant(0)
{

}

CConstant1Dlg::~CConstant1Dlg()
{
}

void CConstant1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Constant);
	DDV_MinMaxDouble(pDX, m_Constant, 0, 255);
}


BEGIN_MESSAGE_MAP(CConstant1Dlg, CDialog)
END_MESSAGE_MAP()


// CConstant1Dlg 메시지 처리기입니다.
