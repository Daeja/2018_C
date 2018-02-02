#pragma once


// CConstant2Dlg 대화 상자입니다.

class CConstant2Dlg : public CDialog
{
	DECLARE_DYNAMIC(CConstant2Dlg)

public:
	CConstant2Dlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CConstant2Dlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	unsigned char m_Constant2_1;
	unsigned char m_Constant2_2;
};
