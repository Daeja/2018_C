#pragma once
#include "atlimage.h"
class CImageProcDoc
{
public:
	CImageProcDoc();
	~CImageProcDoc();
	// 입력 이미지
	unsigned char **m_OriginalImage;
	unsigned char **m_InputImage;
	unsigned char **m_InputImage_R;
	unsigned char **m_InputImage_G;
	unsigned char **m_InputImage_B;

	// 출력 이미지
	unsigned char **m_OriginalImage_R;
	unsigned char **m_OriginalImage_G;
	unsigned char **m_OriginalImage_B;
	unsigned char **m_OutputImage;
	unsigned char **m_OutputImage_R;
	unsigned char **m_OutputImage_G;
	unsigned char **m_OutputImage_B;

	// 이미지 사이즈
	int m_width;
	int m_height;
	int m_Re_width;
	int m_Re_height;

	// 확장자 구분 변수
	const char raw_upper[5] = ".RAW";
	const char raw_lower[5] = ".raw";
	const char jpg_upper[5] = ".JPG";
	const char jpg_lower[5] = ".jpg";
	char FNE[5];	// File Name Extension

	// 히스토그램
	double m_histogram[256];
	double m_histogram_R[256];
	double m_histogram_G[256];
	double m_histogram_B[256];
	double m_sum_of_hist[256];
	double m_sum_of_hist_R[256];
	double m_sum_of_hist_G[256];
	double m_sum_of_hist_B[256];
	unsigned char m_scale_hist[256];
	unsigned char m_scale_hist_R[256];
	unsigned char m_scale_hist_G[256];
	unsigned char m_scale_hist_B[256];

	template <typename T>
	T ** initMemory(T ** img, int width, int height);

	void OnBnClickedOpenFile(CString strPathName);
	void OnBnClickedSaveFile(CString strPathName);
	void OnBnClickedEqualImage();
	void OnBnClickedCloseDialog();
	void OnBnClickedBright(unsigned char m_Constant);
	void OnBnClickedDim(unsigned char m_Constant);
	void OnBnClickedMulti(float m_Constant);
	void OnBnClickedDivision(float m_Constant);
	void OnBnClickedNeg();
	void update_Extension_Func(unsigned char R, unsigned char G, unsigned char B);
	void OnBnClickedReturn();
	void OnBnClickedTempSave();
	void OnBnClickedAnd(unsigned char cons);
	void OnBnClickedOr(unsigned char cons);
	void OnBnClickedXor(unsigned char cons);
	void OnBnClickedParabolaCap();
	void OnBnClickedParabolaCup();
	void OnBnClickedStretching(unsigned char cons1, unsigned char cons2);
	void OnBnClickedHist();
	void OnBnClickedHistEqual();
	void OnBnClickedEndIn(unsigned char cons1, unsigned char cons2);
	void OnBnClickedVerticalEdge();
	void OnBnClickedHorizontalEdge();
	void OnBnClickedSimilarEdge();
	void OnBnClickedSubEdge();
	void OnBnClickedHorizontalRoberts();
	void OnBnClickedVerticalRoberts();
	void OnBnClickedHorizontalPrewitt();
	void OnBnClickedVerticalPrewitt();
	void OnBnClickedHorizontalSobel();
	void OnBnClickedVerticalSobel();
	void OnBnClickedSharp1();
	void OnBnClickedSharp2();
	void OnBnClickedBlur();
	void OnBnClickedEmbossing();
	void OnBnClickedZoomin1(double cons);
	void OnBnClickedZoomin2(double cons);
	void OnBnClickedZoomout1(double cons);
	void OnBnClickedZoomout2(double cons);
	double doubleABS(double num);
	void OnBnClickedPosterRasing(unsigned char cons);
	void OnBnClickedTesseractOcr(CString pathName);
	CImage bmpImg;
};

