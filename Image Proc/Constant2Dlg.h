#pragma once


// CConstant2Dlg ��ȭ �����Դϴ�.

class CConstant2Dlg : public CDialog
{
	DECLARE_DYNAMIC(CConstant2Dlg)

public:
	CConstant2Dlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CConstant2Dlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	unsigned char m_Constant2_1;
	unsigned char m_Constant2_2;
};
