#pragma once


// CConstant1Dlg ��ȭ �����Դϴ�.

class CConstant1Dlg : public CDialog
{
	DECLARE_DYNAMIC(CConstant1Dlg)

public:
	CConstant1Dlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CConstant1Dlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	double m_Constant;
};
