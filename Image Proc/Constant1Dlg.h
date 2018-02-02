#pragma once


// CConstant1Dlg 대화 상자입니다.

class CConstant1Dlg : public CDialog
{
	DECLARE_DYNAMIC(CConstant1Dlg)

public:
	CConstant1Dlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CConstant1Dlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_Constant;
};
