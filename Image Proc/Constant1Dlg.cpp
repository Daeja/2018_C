// Constant1Dlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Image Proc.h"
#include "Constant1Dlg.h"
#include "afxdialogex.h"


// CConstant1Dlg ��ȭ �����Դϴ�.

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


// CConstant1Dlg �޽��� ó�����Դϴ�.
