#pragma once


// CRawSizeDlg ��ȭ �����Դϴ�.

class CRawSizeDlg : public CDialog
{
	DECLARE_DYNAMIC(CRawSizeDlg)

public:
	CRawSizeDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRawSizeDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RAW_SIZE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_Raw_width;
	int m_Raw_height;
};
