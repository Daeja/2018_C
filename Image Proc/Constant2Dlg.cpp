// Constant2Dlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Image Proc.h"
#include "Constant2Dlg.h"
#include "afxdialogex.h"


// CConstant2Dlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CConstant2Dlg, CDialog)

CConstant2Dlg::CConstant2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CONSTANT2, pParent)
	, m_Constant2_1(0)
	, m_Constant2_2(0)
{

}

CConstant2Dlg::~CConstant2Dlg()
{
}

void CConstant2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Constant2_1);
	DDX_Text(pDX, IDC_EDIT2, m_Constant2_2);
}


BEGIN_MESSAGE_MAP(CConstant2Dlg, CDialog)
END_MESSAGE_MAP()


// CConstant2Dlg 메시지 처리기입니다.
