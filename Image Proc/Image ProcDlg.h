
// Image ProcDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CImageProcDlg 대화 상자
class CImageProcDlg : public CDialogEx
{
// 생성입니다.
public:
	CImageProcDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGEPROC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenFile();
	CStatic m_PicControl1;
	CStatic m_PicControl2;
	afx_msg void OnBnClickedCloseDialog();
	afx_msg void OnBnClickedSaveFile();
	afx_msg void OnBnClickedEqualImage();
	afx_msg void OnBnClickedBright();
	afx_msg void OnBnClickedDim();
	afx_msg void OnBnClickedMulti();
	afx_msg void OnBnClickedDivision();
	afx_msg void OnBnClickedNeg();
	void enableButton(bool flag);
	unsigned char m_edit_R;
	unsigned char m_edit_G;
	unsigned char m_edit_B;
	int m_slider_R;
	int m_slider_G;
	int m_slider_B;
	CSliderCtrl m_Slider_C_R;
	CSliderCtrl m_Slider_C_G;
	CSliderCtrl m_Slider_C_B;

	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CEdit m_edit_C_R;
	CEdit m_edit_C_G;
	CEdit m_edit_C_B;
	afx_msg void OnBnClickedExtensionFunc();
	afx_msg void OnEnChangeEditR();
	afx_msg void OnEnChangeEditG();
	afx_msg void OnEnChangeEditB();
	afx_msg void OnBnClickedReturn();
	afx_msg void OnBnClickedTempSave();
	afx_msg void OnBnClickedAnd();
	afx_msg void OnBnClickedOr();
	afx_msg void OnBnClickedXor();
	afx_msg void OnBnClickedParabolaCap();
	afx_msg void OnBnClickedParabolaCup();
	afx_msg void OnBnClickedStretching();
	afx_msg void OnBnClickedHist();
	afx_msg void OnBnClickedHistEqual();
	afx_msg void OnBnClickedEndIn();
	afx_msg void OnBnClickedVerticalEdge();
	afx_msg void OnBnClickedHorizontalEdge();
	afx_msg void OnBnClickedSimilarEdge();
	afx_msg void OnBnClickedSubEdge();
	afx_msg void OnBnClickedHorizontalRoberts();
	afx_msg void OnBnClickedVerticalRoberts();
	afx_msg void OnBnClickedHorizontalPrewitt();
	afx_msg void OnBnClickedVerticalPrewitt();
	afx_msg void OnBnClickedHorizontalSobel();
	afx_msg void OnBnClickedVerticalSobel();
	afx_msg void OnBnClickedSharp1();
	afx_msg void OnBnClickedSharp2();
	afx_msg void OnBnClickedBlur();
	afx_msg void OnBnClickedEmbossing();
	afx_msg void OnBnClickedZoomin1();
	afx_msg void OnBnClickedZoomin2();
	afx_msg void OnBnClickedZoomout1();
	afx_msg void OnBnClickedZoomout2();
	afx_msg void OnBnClickedPosterRasing();
};
