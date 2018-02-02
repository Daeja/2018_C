#pragma once


// CRawSizeDlg 대화 상자입니다.

class CRawSizeDlg : public CDialog
{
	DECLARE_DYNAMIC(CRawSizeDlg)

public:
	CRawSizeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRawSizeDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RAW_SIZE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_Raw_width;
	int m_Raw_height;
};
