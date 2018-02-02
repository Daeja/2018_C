#include "stdafx.h"
#include "Image ProcDoc.h"
#include "RawSizeDlg.h"

CImageProcDoc::CImageProcDoc()
	: m_OriginalImage(NULL)
	, m_OriginalImage_R(NULL)
	, m_OriginalImage_G(NULL)
	, m_OriginalImage_B(NULL)
{
	m_width = 0;
	m_height = 0;
	m_Re_width = 0;
	m_Re_height = 0;
}


CImageProcDoc::~CImageProcDoc()
{
}


template <typename T>
T ** CImageProcDoc::initMemory(T ** img, int width, int height)
{
	img = (T **)malloc(sizeof(T *) * height);
	for (int i = 0; i < height; i++)
		img[i] = (T *)malloc(sizeof(T) * width);

	return img;
}


void CImageProcDoc::OnBnClickedOpenFile(CString strPathName)
{
	CRawSizeDlg dlg;
	char dot = '.';
	char * pStr;

	//입력받은 wchar_t 변수의 길이를 구함
	int strSize = WideCharToMultiByte(CP_ACP, 0, strPathName, -1, NULL, 0, NULL, NULL);

	//char* 메모리 할당
	pStr = new char[strSize];

	//형 변환 
	WideCharToMultiByte(CP_ACP, 0, strPathName, -1, pStr, strSize, 0, 0);

	for (int i = 0; i < 5; i++)
		FNE[i] = pStr[strSize - 5 + i];

	if (strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0) {
		INT_PTR yn = dlg.DoModal();
		
		if (yn != IDOK) return;

		if (m_OriginalImage != NULL) {
			for (int i = 0; i < m_height; i++)
				free(m_OriginalImage[i]);
			free(m_OriginalImage);
		}
		m_InputImage = NULL;

		if (m_InputImage != NULL) {
			for (int i = 0; i < m_height; i++)
				free(m_InputImage[i]);
			free(m_InputImage);
		}
		m_InputImage = NULL;

		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		CFile  File;

		File.Open(strPathName, CFile::modeRead | CFile::typeBinary);

		double fLength = (double)File.GetLength();

		m_width = dlg.m_Raw_width;
		m_height = dlg.m_Raw_height;

		m_OriginalImage = initMemory(m_OriginalImage, m_width, m_height);

		m_InputImage = initMemory(m_InputImage, m_width, m_height);

		for (int i = 0; i < m_height; i++)
			File.Read(m_OriginalImage[i], m_width);

		for (int i = 0; i < m_height; i++)
			for (int k = 0; k < m_width; k++)
				m_InputImage[i][k] = m_OriginalImage[i][k];

		File.Close();
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OriginalImage_R != NULL) {
			for (int i = 0; i < m_height; i++) {
				free(m_OriginalImage_R[i]);
				free(m_OriginalImage_G[i]);
				free(m_OriginalImage_B[i]);
			}
			free(m_OriginalImage_R);
			free(m_OriginalImage_G);
			free(m_OriginalImage_B);
		}
		m_OriginalImage_R = NULL;
		m_OriginalImage_G = NULL;
		m_OriginalImage_B = NULL;

		if (m_InputImage_R != NULL) {
			for (int i = 0; i < m_height; i++) {
				free(m_InputImage_R[i]);
				free(m_InputImage_G[i]);
				free(m_InputImage_B[i]);
			}
			free(m_InputImage_R);
			free(m_InputImage_G);
			free(m_InputImage_B);
		}
		m_InputImage_R = NULL;
		m_InputImage_G = NULL;
		m_InputImage_B = NULL;

		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		bmpImg.Load(strPathName);

		// Image Size
		m_height = bmpImg.GetHeight();
		m_width = bmpImg.GetWidth();

		// Allocate Memory
		// Red Color
		m_OriginalImage_R = initMemory(m_OriginalImage_R, m_width, m_height);
		m_InputImage_R = initMemory(m_InputImage_R, m_width, m_height);

		// Green Color
		m_OriginalImage_G = initMemory(m_OriginalImage_G, m_width, m_height);
		m_InputImage_G = initMemory(m_InputImage_G, m_width, m_height);

		// Blue Color
		m_OriginalImage_B = initMemory(m_OriginalImage_B, m_width, m_height);
		m_InputImage_B = initMemory(m_InputImage_B, m_width, m_height);

		// HDD -> Memory
		COLORREF pixel;
		for (int i = 0; i < m_height; i++)
			for (int k = 0; k < m_width; k++) {
				pixel = bmpImg.GetPixel(k, i);
				m_OriginalImage_R[i][k] = (UCHAR)GetRValue(pixel);
				m_OriginalImage_G[i][k] = (UCHAR)GetGValue(pixel);
				m_OriginalImage_B[i][k] = (UCHAR)GetBValue(pixel);
			}

		for (int i = 0; i < m_height; i++)
			for (int k = 0; k < m_width; k++) {
				pixel = bmpImg.GetPixel(i, k);
				m_InputImage_R[i][k] = m_OriginalImage_R[i][k];
				m_InputImage_G[i][k] = m_OriginalImage_G[i][k];
				m_InputImage_B[i][k] = m_OriginalImage_B[i][k];
			}
	}
}


void CImageProcDoc::OnBnClickedCloseDialog()
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_InputImage != NULL) {
			for (int i = 0; i < m_height; i++)
				free(m_InputImage[i]);
			free(m_InputImage);
		}
		m_InputImage = NULL;

		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_InputImage_R != NULL) {
			for (int i = 0; i < m_height; i++) {
				free(m_InputImage_R[i]);
				free(m_InputImage_G[i]);
				free(m_InputImage_B[i]);
			}
			free(m_InputImage_R);
			free(m_InputImage_G);
			free(m_InputImage_B);
		}
		m_InputImage_R = NULL;
		m_InputImage_G = NULL;
		m_InputImage_B = NULL;

		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;
	}

	exit(0);
}


void CImageProcDoc::OnBnClickedSaveFile(CString strPathName)
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		CFile File;

		if (strPathName.Right(4) != ".raw" || strPathName.Right(4) != ".RAW")
			strPathName += ".raw";

		File.Open(strPathName, CFile::modeCreate | CFile::modeReadWrite);

		for (int i = 0; i < m_Re_height; i++)
			File.Write(m_OutputImage[i], m_Re_width);

		File.Close();
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		CImage save_bmpImg;
		COLORREF pixel;

		if (strPathName.Right(4) != ".jpg" || strPathName.Right(4) != ".JPG")
			strPathName += ".jpg";

		save_bmpImg.Create(m_Re_width, m_Re_height, 32);

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				pixel = RGB(m_OutputImage_R[i][k], m_OutputImage_G[i][k], m_OutputImage_B[i][k]);
				save_bmpImg.SetPixel(k, i, pixel);
			}

		save_bmpImg.Save(strPathName);
	}
}


void CImageProcDoc::OnBnClickedEqualImage()
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// 메모리 할당(출력 영상)
		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				m_OutputImage[i][k] = m_InputImage[i][k];
			}
		}
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage_R[i][k] = m_InputImage_R[i][k];
				m_OutputImage_G[i][k] = m_InputImage_G[i][k];
				m_OutputImage_B[i][k] = m_InputImage_B[i][k];
			}
	}
}


void CImageProcDoc::OnBnClickedBright(unsigned char m_Constant)
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// 메모리 할당(출력 영상)
		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				if (m_InputImage[i][k] + m_Constant > 255) m_OutputImage[i][k] = 255;
				else m_OutputImage[i][k] = m_InputImage[i][k] + m_Constant;
			}
		}
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				if (m_InputImage_R[i][k] + m_Constant > 255) m_OutputImage_R[i][k] = 255;
				else m_OutputImage_R[i][k] = m_InputImage_R[i][k] + m_Constant;

				if (m_InputImage_G[i][k] + m_Constant > 255) m_OutputImage_G[i][k] = 255;
				else m_OutputImage_G[i][k] = m_InputImage_G[i][k] + m_Constant;

				if (m_InputImage_B[i][k] + m_Constant > 255) m_OutputImage_B[i][k] = 255;
				else m_OutputImage_B[i][k] = m_InputImage_B[i][k] + m_Constant;
			}
	}
}


void CImageProcDoc::OnBnClickedDim(unsigned char m_Constant)
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// 메모리 할당(출력 영상)
		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				if (m_InputImage[i][k] - m_Constant < 0) m_OutputImage[i][k] = 0;
				else m_OutputImage[i][k] = m_InputImage[i][k] - m_Constant;
			}
		}
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				if (m_InputImage_R[i][k] - m_Constant < 0) m_OutputImage_R[i][k] = 0;
				else m_OutputImage_R[i][k] = m_InputImage_R[i][k] - m_Constant;

				if (m_InputImage_G[i][k] - m_Constant < 0) m_OutputImage_G[i][k] = 0;
				else m_OutputImage_G[i][k] = m_InputImage_G[i][k] - m_Constant;

				if (m_InputImage_B[i][k] - m_Constant < 0) m_OutputImage_B[i][k] = 0;
				else m_OutputImage_B[i][k] = m_InputImage_B[i][k] - m_Constant;
			}
	}
}


void CImageProcDoc::OnBnClickedMulti(float m_Constant)
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// 메모리 할당(출력 영상)
		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		for (int i = 0; i < m_height; i++)
			for (int k = 0; k < m_width; k++)
				if ((unsigned char)((float)m_InputImage[i][k] * m_Constant) > 255) m_OutputImage[i][k] = 255;
				else m_OutputImage[i][k] = (unsigned char)((float)m_InputImage[i][k] * m_Constant);
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				if ((unsigned char)((float)m_InputImage_R[i][k] * m_Constant) > 255) m_OutputImage_R[i][k] = 255;
				else m_OutputImage_R[i][k] = (unsigned char)((float)m_InputImage_R[i][k] * m_Constant);

				if ((unsigned char)((float)m_InputImage_G[i][k] * m_Constant) > 255) m_OutputImage_G[i][k] = 255;
				else m_OutputImage_G[i][k] = (unsigned char)((float)m_InputImage_G[i][k] * m_Constant);

				if ((unsigned char)((float)m_InputImage_B[i][k] * m_Constant) > 255) m_OutputImage_B[i][k] = 255;
				else m_OutputImage_B[i][k] = (unsigned char)((float)m_InputImage_B[i][k] * m_Constant);
			}
	}
}


void CImageProcDoc::OnBnClickedDivision(float m_Constant)
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// 메모리 할당(출력 영상)
		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				if ((unsigned char)((float)m_InputImage[i][k] / m_Constant) < 1) m_OutputImage[i][k] = 0;
				else m_OutputImage[i][k] = (unsigned char)((float)m_InputImage[i][k] / m_Constant);
			}
		}
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				if ((unsigned char)((float)m_InputImage_R[i][k] / m_Constant) < 1) m_OutputImage_R[i][k] = 0;
				else m_OutputImage_R[i][k] = (unsigned char)((float)m_InputImage_R[i][k] / m_Constant);

				if ((unsigned char)((float)m_InputImage_G[i][k] / m_Constant) < 1) m_OutputImage_G[i][k] = 0;
				else m_OutputImage_G[i][k] = (unsigned char)((float)m_InputImage_G[i][k] / m_Constant);

				if ((unsigned char)((float)m_InputImage_B[i][k] / m_Constant) < 1) m_OutputImage_B[i][k] = 0;
				else m_OutputImage_B[i][k] = (unsigned char)((float)m_InputImage_B[i][k] / m_Constant);
			}
	}
}


void CImageProcDoc::OnBnClickedNeg()
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// 메모리 할당(출력 영상)
		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				m_OutputImage[i][k] = m_InputImage[i][k] - 128;
			}
		}
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage_R[i][k] = m_InputImage_R[i][k] - 128;
				m_OutputImage_G[i][k] = m_InputImage_G[i][k] - 128;
				m_OutputImage_B[i][k] = m_InputImage_B[i][k] - 128;
			}
	}
}


void CImageProcDoc::update_Extension_Func(unsigned char R, unsigned char G, unsigned char B)
{
	for (int i = 0; i < m_Re_height; i++)
		for (int k = 0; k < m_Re_width; k++) {
			if ((m_InputImage_R[i][k]) + R > 255) m_OutputImage_R[i][k] = 255;
			else m_OutputImage_R[i][k] = m_InputImage_R[i][k] + R;

			if ((m_InputImage_G[i][k]) + G > 255) m_OutputImage_G[i][k] = 255;
			else m_OutputImage_G[i][k] = m_InputImage_G[i][k] + G;

			if ((m_InputImage_B[i][k]) + B > 255) m_OutputImage_B[i][k] = 255;
			else m_OutputImage_B[i][k] = m_InputImage_B[i][k] + B;
		}
}


void CImageProcDoc::OnBnClickedReturn()
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		for (int i = 0; i < m_height; i++)
			for (int k = 0; k < m_width; k++) {
				m_InputImage[i][k] = m_OriginalImage[i][k];
			}
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		for (int i = 0; i < m_height; i++)
			for (int k = 0; k < m_width; k++) {
				m_InputImage_R[i][k] = m_OriginalImage_R[i][k];
				m_InputImage_G[i][k] = m_OriginalImage_G[i][k];
				m_InputImage_B[i][k] = m_OriginalImage_B[i][k];
			}
	}

	OnBnClickedEqualImage();
}


void CImageProcDoc::OnBnClickedTempSave()
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		for (int i = 0; i < m_height; i++)
			for (int k = 0; k < m_width; k++) {
				m_InputImage[i][k] = m_OutputImage[i][k];
			}
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		for (int i = 0; i < m_height; i++)
			for (int k = 0; k < m_width; k++) {
				m_InputImage_R[i][k] = m_OutputImage_R[i][k];
				m_InputImage_G[i][k] = m_OutputImage_G[i][k];
				m_InputImage_B[i][k] = m_OutputImage_B[i][k];
			}
	}

	OnBnClickedEqualImage();
}


void CImageProcDoc::OnBnClickedAnd(unsigned char cons)
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// 메모리 할당(출력 영상)
		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				m_OutputImage[i][k] = m_InputImage[i][k] & cons;
			}
		}
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage_R[i][k] = m_InputImage_R[i][k] & cons;
				m_OutputImage_G[i][k] = m_InputImage_G[i][k] & cons;
				m_OutputImage_B[i][k] = m_InputImage_B[i][k] & cons;
			}
	}
}


void CImageProcDoc::OnBnClickedOr(unsigned char cons)
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// 메모리 할당(출력 영상)
		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				m_OutputImage[i][k] = m_InputImage[i][k] | cons;
			}
		}
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage_R[i][k] = m_InputImage_R[i][k] | cons;
				m_OutputImage_G[i][k] = m_InputImage_G[i][k] | cons;
				m_OutputImage_B[i][k] = m_InputImage_B[i][k] | cons;
			}
	}
}


void CImageProcDoc::OnBnClickedXor(unsigned char cons)
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// 메모리 할당(출력 영상)
		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				m_OutputImage[i][k] = m_InputImage[i][k] ^ cons;
			}
		}
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage_R[i][k] = m_InputImage_R[i][k] ^ cons;
				m_OutputImage_G[i][k] = m_InputImage_G[i][k] ^ cons;
				m_OutputImage_B[i][k] = m_InputImage_B[i][k] ^ cons;
			}
	}
}


void CImageProcDoc::OnBnClickedParabolaCap()
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		m_Re_height = m_height;
		m_Re_width = m_width;

		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		double LUT[256];
		for (int i = 0; i < 256; i++)
			LUT[i] = 255.0 - (255.0 * pow(((i / 128.0) - 1.0), 2));

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage[i][k] = LUT[m_InputImage[i][k]];
			}
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		double LUT[256];
		for (int i = 0; i < 256; i++)
			LUT[i] = 255.0 - (255.0 * pow(((i / 128.0) - 1.0), 2));

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage_R[i][k] = LUT[m_InputImage_R[i][k]];
				m_OutputImage_G[i][k] = LUT[m_InputImage_G[i][k]];
				m_OutputImage_B[i][k] = LUT[m_InputImage_B[i][k]];
			}
	}
}


void CImageProcDoc::OnBnClickedParabolaCup()
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		m_Re_height = m_height;
		m_Re_width = m_width;

		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		double LUT[256];
		for (int i = 0; i < 256; i++)
			LUT[i] = (255.0 * pow(((i / 128.0) - 1.0), 2));

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage[i][k] = (unsigned char)LUT[m_InputImage[i][k]];
			}
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		double LUT[256];
		for (int i = 0; i < 256; i++)
			LUT[i] = (255.0 * pow(((i / 128.0) - 1.0), 2));

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage_R[i][k] = (unsigned char)LUT[m_InputImage_R[i][k]];
				m_OutputImage_G[i][k] = (unsigned char)LUT[m_InputImage_G[i][k]];
				m_OutputImage_B[i][k] = (unsigned char)LUT[m_InputImage_B[i][k]];
			}
	}
}


void CImageProcDoc::OnBnClickedStretching(unsigned char cons1, unsigned char cons2)
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OriginalImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OriginalImage[i]);
			free(m_OriginalImage);
		}
		m_OriginalImage = NULL;

		m_Re_height = m_height;
		m_Re_width = m_width;

		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		unsigned char high = cons2;
		unsigned char low = cons1;
		unsigned char in, out;

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				if (m_InputImage[i][k] > high) high = m_InputImage[i][k];
				if (m_InputImage[i][k] < low) low = m_InputImage[i][k];
			}

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				in = m_InputImage[i][k];

				out = (int)((double)(in - low) / (double)(high - low) * 255.0);

				if (out > 255)
					out = 255;
				if (out < 0)
					out = 0;

				m_OutputImage[i][k] = out;
			}
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		unsigned char high = cons2;
		unsigned char low = cons1;
		unsigned char in, out;

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				// R
				if (m_InputImage_R[i][k] > high) high = m_InputImage_R[i][k];
				if (m_InputImage_R[i][k] < low) low = m_InputImage_R[i][k];

				in = m_InputImage_R[i][k];
				out = (int)((double)(in - low) / (double)(high - low) * 255.0);

				if (out > 255) out = 255;
				if (out < 0) out = 0;

				m_OutputImage_R[i][k] = out;
			}

		high = cons2;
		low = cons1;

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {

				// G
				if (m_InputImage_G[i][k] > high) high = m_InputImage_G[i][k];
				if (m_InputImage_G[i][k] < low) low = m_InputImage_G[i][k];

				in = m_InputImage_G[i][k];
				out = (int)((double)(in - low) / (double)(high - low) * 255.0);

				if (out > 255) out = 255;
				if (out < 0) out = 0;

				m_OutputImage_G[i][k] = out;
			}

		high = cons2;
		low = cons1;

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				// B
				if (m_InputImage_B[i][k] > high) high = m_InputImage_B[i][k];
				if (m_InputImage_B[i][k] < low) low = m_InputImage_B[i][k];

				in = m_InputImage_B[i][k];
				out = (int)((double)(in - low) / (double)(high - low) * 255.0);

				if (out > 255) out = 255;
				if (out < 0) out = 0;

				m_OutputImage_B[i][k] = out;
			}
	}
}


void CImageProcDoc::OnBnClickedHist()
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = 256;
		m_Re_width = 256;

		// 메모리 할당(출력 영상)
		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		double MIN, MAX;
		for (int i = 0; i < 256; i++) // 초기화
			m_histogram[i] = 0;
		// 빈도수 조사
		for (int i = 0; i < m_height; i++)
			for (int k = 0; k < m_width; k++)
				m_histogram[m_InputImage[i][k]]++;
		// 정규화
		MIN = MAX = m_histogram[0];
		for (int i = 0; i < 256; i++) {
			if (m_histogram[i] > MAX)
				MAX = m_histogram[i];
			if (m_histogram[i] < MIN)
				MIN = m_histogram[i];
		}
		//정규화된 히스토 그램.
		for (int i = 0; i < 256; i++)
			m_scale_hist[i] = (unsigned char)((m_histogram[i] - MIN) / (MAX - MIN) * 255.0);

		// 출력 영상 흰색으로 초기화
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++)
				m_OutputImage[i][k] = 255;

		// 화면 출력
		for (int i = 0; i < 256; i++) {
			for (int k = 0; k < m_scale_hist[i]; k++) {
				m_OutputImage[256 - k - 1][i] = 0;
			}
		}
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		m_Re_height = 256;
		m_Re_width = 256;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		double MIN_R, MIN_G, MIN_B;
		double MAX_R, MAX_G, MAX_B;
		// 초기화
		for (int i = 0; i < 256; i++) {
			m_histogram_R[i] = 0;
			m_histogram_G[i] = 0;
			m_histogram_B[i] = 0;
		}

		// 빈도수 조사
		for (int i = 0; i < m_height; i++)
			for (int k = 0; k < m_width; k++) {
				m_histogram_R[m_InputImage_R[i][k]]++;
				m_histogram_G[m_InputImage_G[i][k]]++;
				m_histogram_B[m_InputImage_B[i][k]]++;
			}

		// 정규화
		MIN_R = MAX_R = m_histogram_R[0];
		MIN_G = MAX_G = m_histogram_R[0];
		MIN_B = MAX_B = m_histogram_R[0];

		for (int i = 0; i < 256; i++) {
			if (m_histogram_R[i] > MAX_R)
				MAX_R = m_histogram_R[i];
			if (m_histogram_R[i] < MIN_R)
				MIN_R = m_histogram_R[i];

			if (m_histogram_G[i] > MAX_G)
				MAX_G = m_histogram_G[i];
			if (m_histogram_G[i] < MIN_G)
				MIN_G = m_histogram_G[i];

			if (m_histogram_B[i] > MAX_B)
				MAX_B = m_histogram_B[i];
			if (m_histogram_B[i] < MIN_B)
				MIN_B = m_histogram_B[i];
		}
		//정규화된 히스토 그램.
		for (int i = 0; i < 256; i++) {
			m_scale_hist_R[i] = (unsigned char)((m_histogram_R[i] - MIN_R) / (MAX_R - MIN_R) * 255.0);
			m_scale_hist_G[i] = (unsigned char)((m_histogram_G[i] - MIN_G) / (MAX_G - MIN_G) * 255.0);
			m_scale_hist_B[i] = (unsigned char)((m_histogram_B[i] - MIN_B) / (MAX_B - MIN_B) * 255.0);
		}

		// 출력 영상 흰색으로 초기화
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage_R[i][k] = 255;
				m_OutputImage_G[i][k] = 255;
				m_OutputImage_B[i][k] = 255;
			}

		// 화면 출력
		for (int i = 0; i < 256; i++) {
			for (int k = 0; k < m_scale_hist_R[i]; k++)
				m_OutputImage_R[256 - k - 1][i] = 0;
			for (int k = 0; k < m_scale_hist_G[i]; k++)
				m_OutputImage_G[256 - k - 1][i] = 0;
			for (int k = 0; k < m_scale_hist_B[i]; k++)
				m_OutputImage_B[256 - k - 1][i] = 0;
		}
	}
}


void CImageProcDoc::OnBnClickedHistEqual()
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// 메모리 할당(출력 영상)
		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //

		int SUM = 0.0; // 누적값

		// (1) 빈도수(히스토그램) 조사
		for (int i = 0; i < 256; i++) { // 초기화
			m_histogram[i] = 0;
			m_sum_of_hist[i] = 0;
		}
		for (int i = 0; i < m_height; i++)
			for (int k = 0; k < m_width; k++)
				m_histogram[m_InputImage[i][k]]++;

		// (2) 누적 히스토그램 계산
		for (int i = 0; i < 256; i++) {
			SUM += m_histogram[i];
			m_sum_of_hist[i] = SUM;
		}

		// (3) 정규화된 누적 히스토그램 계산
		for (int i = 0; i < 256; i++)
			m_scale_hist[i] = (unsigned char)(m_sum_of_hist[i]
				* (1.0 / (m_width * m_height)) * 255.0);

		// (4) 맞춰서 출력...
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				m_OutputImage[i][k] = m_scale_hist[m_InputImage[i][k]];
			}
		}
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		int SUM_R = 0.0, SUM_G = 0.0, SUM_B = 0.0; // 누적값

		// (1) 빈도수(히스토그램) 조사
		for (int i = 0; i < 256; i++) { // 초기화
			m_histogram_R[i] = 0;
			m_histogram_G[i] = 0;
			m_histogram_B[i] = 0;
			m_sum_of_hist_R[i] = 0;
			m_sum_of_hist_G[i] = 0;
			m_sum_of_hist_B[i] = 0;
		}

		for (int i = 0; i < m_height; i++)
			for (int k = 0; k < m_width; k++) {
				m_histogram_R[m_InputImage_R[i][k]]++;
				m_histogram_G[m_InputImage_G[i][k]]++;
				m_histogram_B[m_InputImage_B[i][k]]++;
			}

		// (2) 누적 히스토그램 계산
		for (int i = 0; i < 256; i++) {
			SUM_R += m_histogram_R[i];
			m_sum_of_hist_R[i] = SUM_R;

			SUM_G += m_histogram_G[i];
			m_sum_of_hist_G[i] = SUM_G;

			SUM_B += m_histogram_B[i];
			m_sum_of_hist_B[i] = SUM_B;
		}

		// (3) 정규화된 누적 히스토그램 계산
		for (int i = 0; i < 256; i++) {
			m_scale_hist_R[i] = (unsigned char)(m_sum_of_hist_R[i] * (1.0 / (m_width * m_height)) * 255.0);
			m_scale_hist_G[i] = (unsigned char)(m_sum_of_hist_G[i] * (1.0 / (m_width * m_height)) * 255.0);
			m_scale_hist_B[i] = (unsigned char)(m_sum_of_hist_B[i] * (1.0 / (m_width * m_height)) * 255.0);
		}

		// (4) 맞춰서 출력...
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				m_OutputImage_R[i][k] = m_scale_hist_R[m_InputImage_R[i][k]];
				m_OutputImage_G[i][k] = m_scale_hist_G[m_InputImage_G[i][k]];
				m_OutputImage_B[i][k] = m_scale_hist_B[m_InputImage_B[i][k]];
			}
		}
	}
}


void CImageProcDoc::OnBnClickedEndIn(unsigned char cons1, unsigned char cons2)
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OriginalImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OriginalImage[i]);
			free(m_OriginalImage);
		}
		m_OriginalImage = NULL;

		m_Re_height = m_height;
		m_Re_width = m_width;

		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		int high = 0;
		int low = 255;
		int in, out;

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				if (m_InputImage[i][k] > high) high = m_InputImage[i][k];
				if (m_InputImage[i][k] < low) low = m_InputImage[i][k];
			}

		low += (int)cons2;
		high -= (int)cons1;

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				in = m_InputImage[i][k];

				out = (int)((double)(in - low) / (double)(high - low) * 255.0);

				if (out > 255)
					out = 255;
				if (out < 0)
					out = 0;

				m_OutputImage[i][k] = (unsigned char)out;
			}
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		int high = 0;
		int low = 255;
		int in, out;

		low += (int)cons2;
		high -= (int)cons1;

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				// R
				if (m_InputImage_R[i][k] > high) high = m_InputImage_R[i][k];
				if (m_InputImage_R[i][k] < low) low = m_InputImage_R[i][k];

				in = m_InputImage_R[i][k];
				out = (int)((double)(in - low) / (double)(high - low) * 255.0);

				if (out > 255) out = 255;
				if (out < 0) out = 0;

				m_OutputImage_R[i][k] = (unsigned char)out;
			}

		high = 0;
		low = 255;

		low += (int)cons2;
		high -= (int)cons1;

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {

				// G
				if (m_InputImage_G[i][k] > high) high = m_InputImage_G[i][k];
				if (m_InputImage_G[i][k] < low) low = m_InputImage_G[i][k];

				in = m_InputImage_G[i][k];
				out = (int)((double)(in - low) / (double)(high - low) * 255.0);

				if (out > 255) out = 255;
				if (out < 0) out = 0;

				m_OutputImage_G[i][k] = (unsigned char)out;
			}

		high = 0;
		low = 255;

		low += (int)cons2;
		high -= (int)cons1;

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				// B
				if (m_InputImage_B[i][k] > high) high = m_InputImage_B[i][k];
				if (m_InputImage_B[i][k] < low) low = m_InputImage_B[i][k];

				in = m_InputImage_B[i][k];
				out = (int)((double)(in - low) / (double)(high - low) * 255.0);

				if (out > 255) out = 255;
				if (out < 0) out = 0;

				m_OutputImage_B[i][k] = (unsigned char)out;
			}
	}
}


void CImageProcDoc::OnBnClickedVerticalEdge()
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// 메모리 할당(출력 영상)
		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		// 마스크
		double mask[3][3] = { { 0. , 0. ,  0. },
									   { -1. , 1. ,  0. },
									   { 0. , 0. ,  0. } };
		int mSize = 3;
		float **tempInput, **tempOutput, S = 0.0;
		// 임시 입력 영상
		tempInput = initMemory(tempInput, m_width + 2, m_height + 2);
		tempOutput = initMemory(tempOutput, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput[i + 1][k + 1] = m_InputImage[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						S = S + mask[n][m] * tempInput[n + i][m + k];
					}
				}
				tempOutput[i][k] = S;
				S = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput[i][k] > 255.0) tempOutput[i][k] = 255.0;
				if (tempOutput[i][k] < 0.0) tempOutput[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++)
				m_OutputImage[i][k] = (unsigned char)tempOutput[i][k];

		// 임시 메모리 해제
		if (tempInput != NULL) {
			for (int i = 0; i < m_height + 2; i++)
				free(tempInput[i]);
			free(tempInput);
		}
		tempInput = NULL;

		if (tempOutput != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(tempOutput[i]);
			free(tempOutput);
		}
		tempOutput = NULL;
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		// 마스크
		double mask[3][3] = { { 0. , 0. ,  0. },
									   { -1. , 1. ,  0. },
									   { 0. , 0. ,  0. } };
		int mSize = 3;
		float **tempInput_R, **tempInput_G, **tempInput_B;
		float **tempOutput_R, **tempOutput_G, **tempOutput_B;
		float S_R = 0.0, S_G = 0.0, S_B = 0.0;
		// 임시 입력 영상
		tempInput_R = initMemory(tempInput_R, m_width + 2, m_height + 2);
		tempInput_G = initMemory(tempInput_G, m_width + 2, m_height + 2);
		tempInput_B = initMemory(tempInput_B, m_width + 2, m_height + 2);

		tempOutput_R = initMemory(tempOutput_R, m_Re_width, m_Re_height);
		tempOutput_G = initMemory(tempOutput_G, m_Re_width, m_Re_height);
		tempOutput_B = initMemory(tempOutput_B, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput_R[i + 1][k + 1] = (float)m_InputImage_R[i][k];
				tempInput_G[i + 1][k + 1] = (float)m_InputImage_G[i][k];
				tempInput_B[i + 1][k + 1] = (float)m_InputImage_B[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						S_R = S_R + mask[n][m] * tempInput_R[n + i][m + k];
						S_G = S_G + mask[n][m] * tempInput_G[n + i][m + k];
						S_B = S_B + mask[n][m] * tempInput_B[n + i][m + k];
					}
				}
				tempOutput_R[i][k] = S_R;
				tempOutput_G[i][k] = S_G;
				tempOutput_B[i][k] = S_B;
				
				S_R = 0.0;
				S_G = 0.0;
				S_B = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput_R[i][k] > 255.0) tempOutput_R[i][k] = 255.0;
				if (tempOutput_R[i][k] < 0.0) tempOutput_R[i][k] = 0.0;

				if (tempOutput_G[i][k] > 255.0) tempOutput_G[i][k] = 255.0;
				if (tempOutput_G[i][k] < 0.0) tempOutput_G[i][k] = 0.0;

				if (tempOutput_B[i][k] > 255.0) tempOutput_B[i][k] = 255.0;
				if (tempOutput_B[i][k] < 0.0) tempOutput_B[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage_R[i][k] = (unsigned char)tempOutput_R[i][k];
				m_OutputImage_G[i][k] = (unsigned char)tempOutput_G[i][k];
				m_OutputImage_B[i][k] = (unsigned char)tempOutput_B[i][k];
			}

		// 임시 메모리 해제
		if (tempInput_R != NULL) {
			for (int i = 0; i < m_height + 2; i++) {
				free(tempInput_R[i]);
				free(tempInput_G[i]);
				free(tempInput_B[i]);
			}
			free(tempInput_R);
			free(tempInput_G);
			free(tempInput_B);
		}
		tempInput_R = NULL;
		tempInput_G = NULL;
		tempInput_B = NULL;

		if (tempOutput_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(tempOutput_R[i]);
				free(tempOutput_G[i]);
				free(tempOutput_B[i]);
			}
			free(tempOutput_R);
			free(tempOutput_G);
			free(tempOutput_B);
		}
		tempOutput_R = NULL;
		tempOutput_G = NULL;
		tempOutput_B = NULL;
	}
}


void CImageProcDoc::OnBnClickedHorizontalEdge()
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// 메모리 할당(출력 영상)
		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		// 마스크
		double mask[3][3] = { { 0. , -1. ,  0. },
									   { 0. , 1. ,  0. },
									   { 0. , 0. ,  0. } };
		int mSize = 3;
		float **tempInput, **tempOutput, S = 0.0;
		// 임시 입력 영상
		tempInput = initMemory(tempInput, m_width + 2, m_height + 2);
		tempOutput = initMemory(tempOutput, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput[i + 1][k + 1] = m_InputImage[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						S = S + mask[n][m] * tempInput[n + i][m + k];
					}
				}
				tempOutput[i][k] = S;
				S = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput[i][k] > 255.0) tempOutput[i][k] = 255.0;
				if (tempOutput[i][k] < 0.0) tempOutput[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++)
				m_OutputImage[i][k] = (unsigned char)tempOutput[i][k];

		// 임시 메모리 해제
		if (tempInput != NULL) {
			for (int i = 0; i < m_height + 2; i++)
				free(tempInput[i]);
			free(tempInput);
		}
		tempInput = NULL;

		if (tempOutput != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(tempOutput[i]);
			free(tempOutput);
		}
		tempOutput = NULL;
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		// 마스크
		double mask[3][3] = { { 0. , -1. ,  0. },
									   { 0. , 1. ,  0. },
									   { 0. , 0. ,  0. } };
		int mSize = 3;
		float **tempInput_R, **tempInput_G, **tempInput_B;
		float **tempOutput_R, **tempOutput_G, **tempOutput_B;
		float S_R = 0.0, S_G = 0.0, S_B = 0.0;
		// 임시 입력 영상
		tempInput_R = initMemory(tempInput_R, m_width + 2, m_height + 2);
		tempInput_G = initMemory(tempInput_G, m_width + 2, m_height + 2);
		tempInput_B = initMemory(tempInput_B, m_width + 2, m_height + 2);

		tempOutput_R = initMemory(tempOutput_R, m_Re_width, m_Re_height);
		tempOutput_G = initMemory(tempOutput_G, m_Re_width, m_Re_height);
		tempOutput_B = initMemory(tempOutput_B, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput_R[i + 1][k + 1] = (float)m_InputImage_R[i][k];
				tempInput_G[i + 1][k + 1] = (float)m_InputImage_G[i][k];
				tempInput_B[i + 1][k + 1] = (float)m_InputImage_B[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						S_R = S_R + mask[n][m] * tempInput_R[n + i][m + k];
						S_G = S_G + mask[n][m] * tempInput_G[n + i][m + k];
						S_B = S_B + mask[n][m] * tempInput_B[n + i][m + k];
					}
				}
				tempOutput_R[i][k] = S_R;
				tempOutput_G[i][k] = S_G;
				tempOutput_B[i][k] = S_B;

				S_R = 0.0;
				S_G = 0.0;
				S_B = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput_R[i][k] > 255.0) tempOutput_R[i][k] = 255.0;
				if (tempOutput_R[i][k] < 0.0) tempOutput_R[i][k] = 0.0;

				if (tempOutput_G[i][k] > 255.0) tempOutput_G[i][k] = 255.0;
				if (tempOutput_G[i][k] < 0.0) tempOutput_G[i][k] = 0.0;

				if (tempOutput_B[i][k] > 255.0) tempOutput_B[i][k] = 255.0;
				if (tempOutput_B[i][k] < 0.0) tempOutput_B[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage_R[i][k] = (unsigned char)tempOutput_R[i][k];
				m_OutputImage_G[i][k] = (unsigned char)tempOutput_G[i][k];
				m_OutputImage_B[i][k] = (unsigned char)tempOutput_B[i][k];
			}

		// 임시 메모리 해제
		if (tempInput_R != NULL) {
			for (int i = 0; i < m_height + 2; i++) {
				free(tempInput_R[i]);
				free(tempInput_G[i]);
				free(tempInput_B[i]);
			}
			free(tempInput_R);
			free(tempInput_G);
			free(tempInput_B);
		}
		tempInput_R = NULL;
		tempInput_G = NULL;
		tempInput_B = NULL;

		if (tempOutput_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(tempOutput_R[i]);
				free(tempOutput_G[i]);
				free(tempOutput_B[i]);
			}
			free(tempOutput_R);
			free(tempOutput_G);
			free(tempOutput_B);
		}
		tempOutput_R = NULL;
		tempOutput_G = NULL;
		tempOutput_B = NULL;
	}
}


void CImageProcDoc::OnBnClickedSimilarEdge()
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// 메모리 할당(출력 영상)
		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		int mSize = 3;
		float **tempInput, **tempOutput, S = 0.0;
		// 임시 입력 영상
		tempInput = initMemory(tempInput, m_width + 2, m_height + 2);
		tempOutput = initMemory(tempOutput, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput[i + 1][k + 1] = m_InputImage[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						if (doubleABS(tempInput[i + 1][k + 1] - tempInput[i + n][k + m]) >= S)
							S = doubleABS(tempInput[i + 1][k + 1] - tempInput[i + n][k + m]);
					}
				}
				tempOutput[i][k] = S;
				S = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput[i][k] > 255.0) tempOutput[i][k] = 255.0;
				if (tempOutput[i][k] < 0.0) tempOutput[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++)
				m_OutputImage[i][k] = (unsigned char)tempOutput[i][k];

		// 임시 메모리 해제
		if (tempInput != NULL) {
			for (int i = 0; i < m_height + 2; i++)
				free(tempInput[i]);
			free(tempInput);
		}
		tempInput = NULL;

		if (tempOutput != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(tempOutput[i]);
			free(tempOutput);
		}
		tempOutput = NULL;
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		int mSize = 3;
		float **tempInput_R, **tempInput_G, **tempInput_B;
		float **tempOutput_R, **tempOutput_G, **tempOutput_B;
		float S_R = 0.0, S_G = 0.0, S_B = 0.0;
		// 임시 입력 영상
		tempInput_R = initMemory(tempInput_R, m_width + 2, m_height + 2);
		tempInput_G = initMemory(tempInput_G, m_width + 2, m_height + 2);
		tempInput_B = initMemory(tempInput_B, m_width + 2, m_height + 2);

		tempOutput_R = initMemory(tempOutput_R, m_Re_width, m_Re_height);
		tempOutput_G = initMemory(tempOutput_G, m_Re_width, m_Re_height);
		tempOutput_B = initMemory(tempOutput_B, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput_R[i + 1][k + 1] = (float)m_InputImage_R[i][k];
				tempInput_G[i + 1][k + 1] = (float)m_InputImage_G[i][k];
				tempInput_B[i + 1][k + 1] = (float)m_InputImage_B[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						if (doubleABS(tempInput_R[i + 1][k + 1] - tempInput_R[i + n][k + m]) >= S_R)
							S_R = doubleABS(tempInput_R[i + 1][k + 1] - tempInput_R[i + n][k + m]);

						if (doubleABS(tempInput_G[i + 1][k + 1] - tempInput_G[i + n][k + m]) >= S_G)
							S_G = doubleABS(tempInput_G[i + 1][k + 1] - tempInput_G[i + n][k + m]);

						if (doubleABS(tempInput_B[i + 1][k + 1] - tempInput_B[i + n][k + m]) >= S_B)
							S_B = doubleABS(tempInput_B[i + 1][k + 1] - tempInput_B[i + n][k + m]);
					}
				}
				tempOutput_R[i][k] = S_R;
				tempOutput_G[i][k] = S_G;
				tempOutput_B[i][k] = S_B;

				S_R = 0.0;
				S_G = 0.0;
				S_B = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput_R[i][k] > 255.0) tempOutput_R[i][k] = 255.0;
				if (tempOutput_R[i][k] < 0.0) tempOutput_R[i][k] = 0.0;

				if (tempOutput_G[i][k] > 255.0) tempOutput_G[i][k] = 255.0;
				if (tempOutput_G[i][k] < 0.0) tempOutput_G[i][k] = 0.0;

				if (tempOutput_B[i][k] > 255.0) tempOutput_B[i][k] = 255.0;
				if (tempOutput_B[i][k] < 0.0) tempOutput_B[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage_R[i][k] = (unsigned char)tempOutput_R[i][k];
				m_OutputImage_G[i][k] = (unsigned char)tempOutput_G[i][k];
				m_OutputImage_B[i][k] = (unsigned char)tempOutput_B[i][k];
			}

		// 임시 메모리 해제
		if (tempInput_R != NULL) {
			for (int i = 0; i < m_height + 2; i++) {
				free(tempInput_R[i]);
				free(tempInput_G[i]);
				free(tempInput_B[i]);
			}
			free(tempInput_R);
			free(tempInput_G);
			free(tempInput_B);
		}
		tempInput_R = NULL;
		tempInput_G = NULL;
		tempInput_B = NULL;

		if (tempOutput_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(tempOutput_R[i]);
				free(tempOutput_G[i]);
				free(tempOutput_B[i]);
			}
			free(tempOutput_R);
			free(tempOutput_G);
			free(tempOutput_B);
		}
		tempOutput_R = NULL;
		tempOutput_G = NULL;
		tempOutput_B = NULL;
	}
}


void CImageProcDoc::OnBnClickedSubEdge()
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// 메모리 할당(출력 영상)
		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		float **tempInput, **tempOutput, S = 0.0;
		// 임시 입력 영상
		tempInput = initMemory(tempInput, m_width + 2, m_height + 2);
		tempOutput = initMemory(tempOutput, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput[i + 1][k + 1] = m_InputImage[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 1; i < m_height; i++) {
			for (int k = 1; k < m_width; k++) {
				S += doubleABS(tempInput[i - 1][k - 1] - tempInput[i + 1][k + 1]);
				S += doubleABS(tempInput[i - 1][k] - tempInput[i + 1][k]);
				S += doubleABS(tempInput[i - 1][k + 1] - tempInput[i + 1][k - 1]);
				S += doubleABS(tempInput[i][k - 1] - tempInput[i][k + 1]);

				tempOutput[i][k] = S;
				S = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput[i][k] > 255.0) tempOutput[i][k] = 255.0;
				if (tempOutput[i][k] < 0.0) tempOutput[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++)
				m_OutputImage[i][k] = (unsigned char)tempOutput[i][k];

		// 임시 메모리 해제
		if (tempInput != NULL) {
			for (int i = 0; i < m_height + 2; i++)
				free(tempInput[i]);
			free(tempInput);
		}
		tempInput = NULL;

		if (tempOutput != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(tempOutput[i]);
			free(tempOutput);
		}
		tempOutput = NULL;
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		float **tempInput_R, **tempInput_G, **tempInput_B;
		float **tempOutput_R, **tempOutput_G, **tempOutput_B;
		float S_R = 0.0, S_G = 0.0, S_B = 0.0;
		// 임시 입력 영상
		tempInput_R = initMemory(tempInput_R, m_width + 2, m_height + 2);
		tempInput_G = initMemory(tempInput_G, m_width + 2, m_height + 2);
		tempInput_B = initMemory(tempInput_B, m_width + 2, m_height + 2);

		tempOutput_R = initMemory(tempOutput_R, m_Re_width, m_Re_height);
		tempOutput_G = initMemory(tempOutput_G, m_Re_width, m_Re_height);
		tempOutput_B = initMemory(tempOutput_B, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput_R[i + 1][k + 1] = (float)m_InputImage_R[i][k];
				tempInput_G[i + 1][k + 1] = (float)m_InputImage_G[i][k];
				tempInput_B[i + 1][k + 1] = (float)m_InputImage_B[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 1; i < m_height; i++) {
			for (int k = 1; k < m_width; k++) {
				S_R += doubleABS(tempInput_R[i - 1][k - 1] - tempInput_R[i + 1][k + 1]);
				S_R += doubleABS(tempInput_R[i - 1][k] - tempInput_R[i + 1][k]);
				S_R += doubleABS(tempInput_R[i - 1][k + 1] - tempInput_R[i + 1][k - 1]);
				S_R += doubleABS(tempInput_R[i][k - 1] - tempInput_R[i][k + 1]);

				S_G += doubleABS(tempInput_G[i - 1][k - 1] - tempInput_G[i + 1][k + 1]);
				S_G += doubleABS(tempInput_G[i - 1][k] - tempInput_G[i + 1][k]);
				S_G += doubleABS(tempInput_G[i - 1][k + 1] - tempInput_G[i + 1][k - 1]);
				S_G += doubleABS(tempInput_G[i][k - 1] - tempInput_G[i][k + 1]);

				S_B += doubleABS(tempInput_B[i - 1][k - 1] - tempInput_B[i + 1][k + 1]);
				S_B += doubleABS(tempInput_B[i - 1][k] - tempInput_B[i + 1][k]);
				S_B += doubleABS(tempInput_B[i - 1][k + 1] - tempInput_B[i + 1][k - 1]);
				S_B += doubleABS(tempInput_B[i][k - 1] - tempInput_B[i][k + 1]);

				tempOutput_R[i][k] = S_R;
				tempOutput_G[i][k] = S_G;
				tempOutput_B[i][k] = S_B;

				S_R = 0.0;
				S_G = 0.0;
				S_B = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput_R[i][k] > 255.0) tempOutput_R[i][k] = 255.0;
				if (tempOutput_R[i][k] < 0.0) tempOutput_R[i][k] = 0.0;

				if (tempOutput_G[i][k] > 255.0) tempOutput_G[i][k] = 255.0;
				if (tempOutput_G[i][k] < 0.0) tempOutput_G[i][k] = 0.0;

				if (tempOutput_B[i][k] > 255.0) tempOutput_B[i][k] = 255.0;
				if (tempOutput_B[i][k] < 0.0) tempOutput_B[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage_R[i][k] = (unsigned char)tempOutput_R[i][k];
				m_OutputImage_G[i][k] = (unsigned char)tempOutput_G[i][k];
				m_OutputImage_B[i][k] = (unsigned char)tempOutput_B[i][k];
			}

		// 임시 메모리 해제
		if (tempInput_R != NULL) {
			for (int i = 0; i < m_height + 2; i++) {
				free(tempInput_R[i]);
				free(tempInput_G[i]);
				free(tempInput_B[i]);
			}
			free(tempInput_R);
			free(tempInput_G);
			free(tempInput_B);
		}
		tempInput_R = NULL;
		tempInput_G = NULL;
		tempInput_B = NULL;

		if (tempOutput_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(tempOutput_R[i]);
				free(tempOutput_G[i]);
				free(tempOutput_B[i]);
			}
			free(tempOutput_R);
			free(tempOutput_G);
			free(tempOutput_B);
		}
		tempOutput_R = NULL;
		tempOutput_G = NULL;
		tempOutput_B = NULL;
	}
}


void CImageProcDoc::OnBnClickedHorizontalRoberts()
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// 메모리 할당(출력 영상)
		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		// 마스크
		double mask[3][3] = { { -1. , 0. ,  0. },
									 { 0. , 1. ,  0. },
									 { 0. , 0. ,  0. } };
		int mSize = 3;
		float **tempInput, **tempOutput, S = 0.0;
		// 임시 입력 영상
		tempInput = initMemory(tempInput, m_width + 2, m_height + 2);
		tempOutput = initMemory(tempOutput, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput[i + 1][k + 1] = m_InputImage[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						S = S + mask[n][m] * tempInput[n + i][m + k];
					}
				}
				tempOutput[i][k] = S;
				S = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput[i][k] > 255.0) tempOutput[i][k] = 255.0;
				if (tempOutput[i][k] < 0.0) tempOutput[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++)
				m_OutputImage[i][k] = (unsigned char)tempOutput[i][k];

		// 임시 메모리 해제
		if (tempInput != NULL) {
			for (int i = 0; i < m_height + 2; i++)
				free(tempInput[i]);
			free(tempInput);
		}
		tempInput = NULL;

		if (tempOutput != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(tempOutput[i]);
			free(tempOutput);
		}
		tempOutput = NULL;
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		// 마스크
		double mask[3][3] = { { -1. , 0. ,  0. },
									   { 0. , 1. ,  0. },
									   { 0. , 0. ,  0. } };
		int mSize = 3;
		float **tempInput_R, **tempInput_G, **tempInput_B;
		float **tempOutput_R, **tempOutput_G, **tempOutput_B;
		float S_R = 0.0, S_G = 0.0, S_B = 0.0;
		// 임시 입력 영상
		tempInput_R = initMemory(tempInput_R, m_width + 2, m_height + 2);
		tempInput_G = initMemory(tempInput_G, m_width + 2, m_height + 2);
		tempInput_B = initMemory(tempInput_B, m_width + 2, m_height + 2);

		tempOutput_R = initMemory(tempOutput_R, m_Re_width, m_Re_height);
		tempOutput_G = initMemory(tempOutput_G, m_Re_width, m_Re_height);
		tempOutput_B = initMemory(tempOutput_B, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput_R[i + 1][k + 1] = (float)m_InputImage_R[i][k];
				tempInput_G[i + 1][k + 1] = (float)m_InputImage_G[i][k];
				tempInput_B[i + 1][k + 1] = (float)m_InputImage_B[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						S_R = S_R + mask[n][m] * tempInput_R[n + i][m + k];
						S_G = S_G + mask[n][m] * tempInput_G[n + i][m + k];
						S_B = S_B + mask[n][m] * tempInput_B[n + i][m + k];
					}
				}
				tempOutput_R[i][k] = S_R;
				tempOutput_G[i][k] = S_G;
				tempOutput_B[i][k] = S_B;

				S_R = 0.0;
				S_G = 0.0;
				S_B = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput_R[i][k] > 255.0) tempOutput_R[i][k] = 255.0;
				if (tempOutput_R[i][k] < 0.0) tempOutput_R[i][k] = 0.0;

				if (tempOutput_G[i][k] > 255.0) tempOutput_G[i][k] = 255.0;
				if (tempOutput_G[i][k] < 0.0) tempOutput_G[i][k] = 0.0;

				if (tempOutput_B[i][k] > 255.0) tempOutput_B[i][k] = 255.0;
				if (tempOutput_B[i][k] < 0.0) tempOutput_B[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage_R[i][k] = (unsigned char)tempOutput_R[i][k];
				m_OutputImage_G[i][k] = (unsigned char)tempOutput_G[i][k];
				m_OutputImage_B[i][k] = (unsigned char)tempOutput_B[i][k];
			}

		// 임시 메모리 해제
		if (tempInput_R != NULL) {
			for (int i = 0; i < m_height + 2; i++) {
				free(tempInput_R[i]);
				free(tempInput_G[i]);
				free(tempInput_B[i]);
			}
			free(tempInput_R);
			free(tempInput_G);
			free(tempInput_B);
		}
		tempInput_R = NULL;
		tempInput_G = NULL;
		tempInput_B = NULL;

		if (tempOutput_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(tempOutput_R[i]);
				free(tempOutput_G[i]);
				free(tempOutput_B[i]);
			}
			free(tempOutput_R);
			free(tempOutput_G);
			free(tempOutput_B);
		}
		tempOutput_R = NULL;
		tempOutput_G = NULL;
		tempOutput_B = NULL;
	}
}


void CImageProcDoc::OnBnClickedVerticalRoberts()
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// 메모리 할당(출력 영상)
		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		// 마스크
		double mask[3][3] = { { 0. , 0. ,  -1. },
									   { 0. , 1. ,  0. },
									   { 0. , 0. ,  0. } };
		int mSize = 3;
		float **tempInput, **tempOutput, S = 0.0;
		// 임시 입력 영상
		tempInput = initMemory(tempInput, m_width + 2, m_height + 2);
		tempOutput = initMemory(tempOutput, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput[i + 1][k + 1] = m_InputImage[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						S = S + mask[n][m] * tempInput[n + i][m + k];
					}
				}
				tempOutput[i][k] = S;
				S = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput[i][k] > 255.0) tempOutput[i][k] = 255.0;
				if (tempOutput[i][k] < 0.0) tempOutput[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++)
				m_OutputImage[i][k] = (unsigned char)tempOutput[i][k];

		// 임시 메모리 해제
		if (tempInput != NULL) {
			for (int i = 0; i < m_height + 2; i++)
				free(tempInput[i]);
			free(tempInput);
		}
		tempInput = NULL;

		if (tempOutput != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(tempOutput[i]);
			free(tempOutput);
		}
		tempOutput = NULL;
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		// 마스크
		double mask[3][3] = { { 0. , 0. ,  -1. },
									   { 0. , 1. ,  0. },
									   { 0. , 0. ,  0. } };
		int mSize = 3;
		float **tempInput_R, **tempInput_G, **tempInput_B;
		float **tempOutput_R, **tempOutput_G, **tempOutput_B;
		float S_R = 0.0, S_G = 0.0, S_B = 0.0;
		// 임시 입력 영상
		tempInput_R = initMemory(tempInput_R, m_width + 2, m_height + 2);
		tempInput_G = initMemory(tempInput_G, m_width + 2, m_height + 2);
		tempInput_B = initMemory(tempInput_B, m_width + 2, m_height + 2);

		tempOutput_R = initMemory(tempOutput_R, m_Re_width, m_Re_height);
		tempOutput_G = initMemory(tempOutput_G, m_Re_width, m_Re_height);
		tempOutput_B = initMemory(tempOutput_B, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput_R[i + 1][k + 1] = (float)m_InputImage_R[i][k];
				tempInput_G[i + 1][k + 1] = (float)m_InputImage_G[i][k];
				tempInput_B[i + 1][k + 1] = (float)m_InputImage_B[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						S_R = S_R + mask[n][m] * tempInput_R[n + i][m + k];
						S_G = S_G + mask[n][m] * tempInput_G[n + i][m + k];
						S_B = S_B + mask[n][m] * tempInput_B[n + i][m + k];
					}
				}
				tempOutput_R[i][k] = S_R;
				tempOutput_G[i][k] = S_G;
				tempOutput_B[i][k] = S_B;

				S_R = 0.0;
				S_G = 0.0;
				S_B = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput_R[i][k] > 255.0) tempOutput_R[i][k] = 255.0;
				if (tempOutput_R[i][k] < 0.0) tempOutput_R[i][k] = 0.0;

				if (tempOutput_G[i][k] > 255.0) tempOutput_G[i][k] = 255.0;
				if (tempOutput_G[i][k] < 0.0) tempOutput_G[i][k] = 0.0;

				if (tempOutput_B[i][k] > 255.0) tempOutput_B[i][k] = 255.0;
				if (tempOutput_B[i][k] < 0.0) tempOutput_B[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage_R[i][k] = (unsigned char)tempOutput_R[i][k];
				m_OutputImage_G[i][k] = (unsigned char)tempOutput_G[i][k];
				m_OutputImage_B[i][k] = (unsigned char)tempOutput_B[i][k];
			}

		// 임시 메모리 해제
		if (tempInput_R != NULL) {
			for (int i = 0; i < m_height + 2; i++) {
				free(tempInput_R[i]);
				free(tempInput_G[i]);
				free(tempInput_B[i]);
			}
			free(tempInput_R);
			free(tempInput_G);
			free(tempInput_B);
		}
		tempInput_R = NULL;
		tempInput_G = NULL;
		tempInput_B = NULL;

		if (tempOutput_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(tempOutput_R[i]);
				free(tempOutput_G[i]);
				free(tempOutput_B[i]);
			}
			free(tempOutput_R);
			free(tempOutput_G);
			free(tempOutput_B);
		}
		tempOutput_R = NULL;
		tempOutput_G = NULL;
		tempOutput_B = NULL;
	}
}


void CImageProcDoc::OnBnClickedHorizontalPrewitt()
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// 메모리 할당(출력 영상)
		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		// 마스크
		double mask[3][3] = { { -1. , -1. ,  -1. },
									   { 0. , 0. ,  0. },
									   { 1. , 1. ,  1. } };
		int mSize = 3;
		float **tempInput, **tempOutput, S = 0.0;
		// 임시 입력 영상
		tempInput = initMemory(tempInput, m_width + 2, m_height + 2);
		tempOutput = initMemory(tempOutput, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput[i + 1][k + 1] = m_InputImage[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						S = S + mask[n][m] * tempInput[n + i][m + k];
					}
				}
				tempOutput[i][k] = S;
				S = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput[i][k] > 255.0) tempOutput[i][k] = 255.0;
				if (tempOutput[i][k] < 0.0) tempOutput[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++)
				m_OutputImage[i][k] = (unsigned char)tempOutput[i][k];

		// 임시 메모리 해제
		if (tempInput != NULL) {
			for (int i = 0; i < m_height + 2; i++)
				free(tempInput[i]);
			free(tempInput);
		}
		tempInput = NULL;

		if (tempOutput != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(tempOutput[i]);
			free(tempOutput);
		}
		tempOutput = NULL;
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		// 마스크
		double mask[3][3] = { { -1. , -1. ,  -1. },
									   { 0. , 0. ,  0. },
									   { 1. , 1. ,  1. } };
		int mSize = 3;
		float **tempInput_R, **tempInput_G, **tempInput_B;
		float **tempOutput_R, **tempOutput_G, **tempOutput_B;
		float S_R = 0.0, S_G = 0.0, S_B = 0.0;
		// 임시 입력 영상
		tempInput_R = initMemory(tempInput_R, m_width + 2, m_height + 2);
		tempInput_G = initMemory(tempInput_G, m_width + 2, m_height + 2);
		tempInput_B = initMemory(tempInput_B, m_width + 2, m_height + 2);

		tempOutput_R = initMemory(tempOutput_R, m_Re_width, m_Re_height);
		tempOutput_G = initMemory(tempOutput_G, m_Re_width, m_Re_height);
		tempOutput_B = initMemory(tempOutput_B, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput_R[i + 1][k + 1] = (float)m_InputImage_R[i][k];
				tempInput_G[i + 1][k + 1] = (float)m_InputImage_G[i][k];
				tempInput_B[i + 1][k + 1] = (float)m_InputImage_B[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						S_R = S_R + mask[n][m] * tempInput_R[n + i][m + k];
						S_G = S_G + mask[n][m] * tempInput_G[n + i][m + k];
						S_B = S_B + mask[n][m] * tempInput_B[n + i][m + k];
					}
				}
				tempOutput_R[i][k] = S_R;
				tempOutput_G[i][k] = S_G;
				tempOutput_B[i][k] = S_B;

				S_R = 0.0;
				S_G = 0.0;
				S_B = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput_R[i][k] > 255.0) tempOutput_R[i][k] = 255.0;
				if (tempOutput_R[i][k] < 0.0) tempOutput_R[i][k] = 0.0;

				if (tempOutput_G[i][k] > 255.0) tempOutput_G[i][k] = 255.0;
				if (tempOutput_G[i][k] < 0.0) tempOutput_G[i][k] = 0.0;

				if (tempOutput_B[i][k] > 255.0) tempOutput_B[i][k] = 255.0;
				if (tempOutput_B[i][k] < 0.0) tempOutput_B[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage_R[i][k] = (unsigned char)tempOutput_R[i][k];
				m_OutputImage_G[i][k] = (unsigned char)tempOutput_G[i][k];
				m_OutputImage_B[i][k] = (unsigned char)tempOutput_B[i][k];
			}

		// 임시 메모리 해제
		if (tempInput_R != NULL) {
			for (int i = 0; i < m_height + 2; i++) {
				free(tempInput_R[i]);
				free(tempInput_G[i]);
				free(tempInput_B[i]);
			}
			free(tempInput_R);
			free(tempInput_G);
			free(tempInput_B);
		}
		tempInput_R = NULL;
		tempInput_G = NULL;
		tempInput_B = NULL;

		if (tempOutput_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(tempOutput_R[i]);
				free(tempOutput_G[i]);
				free(tempOutput_B[i]);
			}
			free(tempOutput_R);
			free(tempOutput_G);
			free(tempOutput_B);
		}
		tempOutput_R = NULL;
		tempOutput_G = NULL;
		tempOutput_B = NULL;
	}
}


void CImageProcDoc::OnBnClickedVerticalPrewitt()
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// 메모리 할당(출력 영상)
		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		// 마스크
		double mask[3][3] = { { 1. , 0. ,  -1. },
									   { 1. , 0. ,  -1. },
									   { 1. , 0. ,  -1. } };
		int mSize = 3;
		float **tempInput, **tempOutput, S = 0.0;
		// 임시 입력 영상
		tempInput = initMemory(tempInput, m_width + 2, m_height + 2);
		tempOutput = initMemory(tempOutput, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput[i + 1][k + 1] = m_InputImage[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						S = S + mask[n][m] * tempInput[n + i][m + k];
					}
				}
				tempOutput[i][k] = S;
				S = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput[i][k] > 255.0) tempOutput[i][k] = 255.0;
				if (tempOutput[i][k] < 0.0) tempOutput[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++)
				m_OutputImage[i][k] = (unsigned char)tempOutput[i][k];

		// 임시 메모리 해제
		if (tempInput != NULL) {
			for (int i = 0; i < m_height + 2; i++)
				free(tempInput[i]);
			free(tempInput);
		}
		tempInput = NULL;

		if (tempOutput != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(tempOutput[i]);
			free(tempOutput);
		}
		tempOutput = NULL;
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		// 마스크
		double mask[3][3] = { { 1. , 0. ,  -1. },
									   { 1. , 0. ,  -1. },
									   { 1. , 0. ,  -1. } };
		int mSize = 3;
		float **tempInput_R, **tempInput_G, **tempInput_B;
		float **tempOutput_R, **tempOutput_G, **tempOutput_B;
		float S_R = 0.0, S_G = 0.0, S_B = 0.0;
		// 임시 입력 영상
		tempInput_R = initMemory(tempInput_R, m_width + 2, m_height + 2);
		tempInput_G = initMemory(tempInput_G, m_width + 2, m_height + 2);
		tempInput_B = initMemory(tempInput_B, m_width + 2, m_height + 2);

		tempOutput_R = initMemory(tempOutput_R, m_Re_width, m_Re_height);
		tempOutput_G = initMemory(tempOutput_G, m_Re_width, m_Re_height);
		tempOutput_B = initMemory(tempOutput_B, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput_R[i + 1][k + 1] = (float)m_InputImage_R[i][k];
				tempInput_G[i + 1][k + 1] = (float)m_InputImage_G[i][k];
				tempInput_B[i + 1][k + 1] = (float)m_InputImage_B[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						S_R = S_R + mask[n][m] * tempInput_R[n + i][m + k];
						S_G = S_G + mask[n][m] * tempInput_G[n + i][m + k];
						S_B = S_B + mask[n][m] * tempInput_B[n + i][m + k];
					}
				}
				tempOutput_R[i][k] = S_R;
				tempOutput_G[i][k] = S_G;
				tempOutput_B[i][k] = S_B;

				S_R = 0.0;
				S_G = 0.0;
				S_B = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput_R[i][k] > 255.0) tempOutput_R[i][k] = 255.0;
				if (tempOutput_R[i][k] < 0.0) tempOutput_R[i][k] = 0.0;

				if (tempOutput_G[i][k] > 255.0) tempOutput_G[i][k] = 255.0;
				if (tempOutput_G[i][k] < 0.0) tempOutput_G[i][k] = 0.0;

				if (tempOutput_B[i][k] > 255.0) tempOutput_B[i][k] = 255.0;
				if (tempOutput_B[i][k] < 0.0) tempOutput_B[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage_R[i][k] = (unsigned char)tempOutput_R[i][k];
				m_OutputImage_G[i][k] = (unsigned char)tempOutput_G[i][k];
				m_OutputImage_B[i][k] = (unsigned char)tempOutput_B[i][k];
			}

		// 임시 메모리 해제
		if (tempInput_R != NULL) {
			for (int i = 0; i < m_height + 2; i++) {
				free(tempInput_R[i]);
				free(tempInput_G[i]);
				free(tempInput_B[i]);
			}
			free(tempInput_R);
			free(tempInput_G);
			free(tempInput_B);
		}
		tempInput_R = NULL;
		tempInput_G = NULL;
		tempInput_B = NULL;

		if (tempOutput_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(tempOutput_R[i]);
				free(tempOutput_G[i]);
				free(tempOutput_B[i]);
			}
			free(tempOutput_R);
			free(tempOutput_G);
			free(tempOutput_B);
		}
		tempOutput_R = NULL;
		tempOutput_G = NULL;
		tempOutput_B = NULL;
	}
}


void CImageProcDoc::OnBnClickedHorizontalSobel()
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// 메모리 할당(출력 영상)
		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		// 마스크
		double mask[3][3] = { { -1. , -2. ,  -1. },
									   { 0. , 0. ,  0. },
									   { 1. , 2. ,  1. } };
		int mSize = 3;
		float **tempInput, **tempOutput, S = 0.0;
		// 임시 입력 영상
		tempInput = initMemory(tempInput, m_width + 2, m_height + 2);
		tempOutput = initMemory(tempOutput, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput[i + 1][k + 1] = m_InputImage[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						S = S + mask[n][m] * tempInput[n + i][m + k];
					}
				}
				tempOutput[i][k] = S;
				S = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput[i][k] > 255.0) tempOutput[i][k] = 255.0;
				if (tempOutput[i][k] < 0.0) tempOutput[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++)
				m_OutputImage[i][k] = (unsigned char)tempOutput[i][k];

		// 임시 메모리 해제
		if (tempInput != NULL) {
			for (int i = 0; i < m_height + 2; i++)
				free(tempInput[i]);
			free(tempInput);
		}
		tempInput = NULL;

		if (tempOutput != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(tempOutput[i]);
			free(tempOutput);
		}
		tempOutput = NULL;
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		// 마스크
		double mask[3][3] = { { -1. , -2. ,  -1. },
									   { 0. , 0. ,  0. },
									   { 1. , 2. ,  1. } };
		int mSize = 3;
		float **tempInput_R, **tempInput_G, **tempInput_B;
		float **tempOutput_R, **tempOutput_G, **tempOutput_B;
		float S_R = 0.0, S_G = 0.0, S_B = 0.0;
		// 임시 입력 영상
		tempInput_R = initMemory(tempInput_R, m_width + 2, m_height + 2);
		tempInput_G = initMemory(tempInput_G, m_width + 2, m_height + 2);
		tempInput_B = initMemory(tempInput_B, m_width + 2, m_height + 2);

		tempOutput_R = initMemory(tempOutput_R, m_Re_width, m_Re_height);
		tempOutput_G = initMemory(tempOutput_G, m_Re_width, m_Re_height);
		tempOutput_B = initMemory(tempOutput_B, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput_R[i + 1][k + 1] = (float)m_InputImage_R[i][k];
				tempInput_G[i + 1][k + 1] = (float)m_InputImage_G[i][k];
				tempInput_B[i + 1][k + 1] = (float)m_InputImage_B[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						S_R = S_R + mask[n][m] * tempInput_R[n + i][m + k];
						S_G = S_G + mask[n][m] * tempInput_G[n + i][m + k];
						S_B = S_B + mask[n][m] * tempInput_B[n + i][m + k];
					}
				}
				tempOutput_R[i][k] = S_R;
				tempOutput_G[i][k] = S_G;
				tempOutput_B[i][k] = S_B;

				S_R = 0.0;
				S_G = 0.0;
				S_B = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput_R[i][k] > 255.0) tempOutput_R[i][k] = 255.0;
				if (tempOutput_R[i][k] < 0.0) tempOutput_R[i][k] = 0.0;

				if (tempOutput_G[i][k] > 255.0) tempOutput_G[i][k] = 255.0;
				if (tempOutput_G[i][k] < 0.0) tempOutput_G[i][k] = 0.0;

				if (tempOutput_B[i][k] > 255.0) tempOutput_B[i][k] = 255.0;
				if (tempOutput_B[i][k] < 0.0) tempOutput_B[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage_R[i][k] = (unsigned char)tempOutput_R[i][k];
				m_OutputImage_G[i][k] = (unsigned char)tempOutput_G[i][k];
				m_OutputImage_B[i][k] = (unsigned char)tempOutput_B[i][k];
			}

		// 임시 메모리 해제
		if (tempInput_R != NULL) {
			for (int i = 0; i < m_height + 2; i++) {
				free(tempInput_R[i]);
				free(tempInput_G[i]);
				free(tempInput_B[i]);
			}
			free(tempInput_R);
			free(tempInput_G);
			free(tempInput_B);
		}
		tempInput_R = NULL;
		tempInput_G = NULL;
		tempInput_B = NULL;

		if (tempOutput_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(tempOutput_R[i]);
				free(tempOutput_G[i]);
				free(tempOutput_B[i]);
			}
			free(tempOutput_R);
			free(tempOutput_G);
			free(tempOutput_B);
		}
		tempOutput_R = NULL;
		tempOutput_G = NULL;
		tempOutput_B = NULL;
	}
}


void CImageProcDoc::OnBnClickedVerticalSobel()
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// 메모리 할당(출력 영상)
		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		// 마스크
		double mask[3][3] = { { 1. , 0. ,  -1. },
									   { 2. , 0. ,  -2. },
									   { 1. , 0. ,  -1. } };
		int mSize = 3;
		float **tempInput, **tempOutput, S = 0.0;
		// 임시 입력 영상
		tempInput = initMemory(tempInput, m_width + 2, m_height + 2);
		tempOutput = initMemory(tempOutput, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput[i + 1][k + 1] = m_InputImage[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						S = S + mask[n][m] * tempInput[n + i][m + k];
					}
				}
				tempOutput[i][k] = S;
				S = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput[i][k] > 255.0) tempOutput[i][k] = 255.0;
				if (tempOutput[i][k] < 0.0) tempOutput[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++)
				m_OutputImage[i][k] = (unsigned char)tempOutput[i][k];

		// 임시 메모리 해제
		if (tempInput != NULL) {
			for (int i = 0; i < m_height + 2; i++)
				free(tempInput[i]);
			free(tempInput);
		}
		tempInput = NULL;

		if (tempOutput != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(tempOutput[i]);
			free(tempOutput);
		}
		tempOutput = NULL;
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		// 마스크
		double mask[3][3] = { { 1. , 0. ,  -1. },
									   { 2. , 0. ,  -2. },
									   { 1. , 0. ,  -1. } };
		int mSize = 3;
		float **tempInput_R, **tempInput_G, **tempInput_B;
		float **tempOutput_R, **tempOutput_G, **tempOutput_B;
		float S_R = 0.0, S_G = 0.0, S_B = 0.0;
		// 임시 입력 영상
		tempInput_R = initMemory(tempInput_R, m_width + 2, m_height + 2);
		tempInput_G = initMemory(tempInput_G, m_width + 2, m_height + 2);
		tempInput_B = initMemory(tempInput_B, m_width + 2, m_height + 2);

		tempOutput_R = initMemory(tempOutput_R, m_Re_width, m_Re_height);
		tempOutput_G = initMemory(tempOutput_G, m_Re_width, m_Re_height);
		tempOutput_B = initMemory(tempOutput_B, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput_R[i + 1][k + 1] = (float)m_InputImage_R[i][k];
				tempInput_G[i + 1][k + 1] = (float)m_InputImage_G[i][k];
				tempInput_B[i + 1][k + 1] = (float)m_InputImage_B[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						S_R = S_R + mask[n][m] * tempInput_R[n + i][m + k];
						S_G = S_G + mask[n][m] * tempInput_G[n + i][m + k];
						S_B = S_B + mask[n][m] * tempInput_B[n + i][m + k];
					}
				}
				tempOutput_R[i][k] = S_R;
				tempOutput_G[i][k] = S_G;
				tempOutput_B[i][k] = S_B;

				S_R = 0.0;
				S_G = 0.0;
				S_B = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput_R[i][k] > 255.0) tempOutput_R[i][k] = 255.0;
				if (tempOutput_R[i][k] < 0.0) tempOutput_R[i][k] = 0.0;

				if (tempOutput_G[i][k] > 255.0) tempOutput_G[i][k] = 255.0;
				if (tempOutput_G[i][k] < 0.0) tempOutput_G[i][k] = 0.0;

				if (tempOutput_B[i][k] > 255.0) tempOutput_B[i][k] = 255.0;
				if (tempOutput_B[i][k] < 0.0) tempOutput_B[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage_R[i][k] = (unsigned char)tempOutput_R[i][k];
				m_OutputImage_G[i][k] = (unsigned char)tempOutput_G[i][k];
				m_OutputImage_B[i][k] = (unsigned char)tempOutput_B[i][k];
			}

		// 임시 메모리 해제
		if (tempInput_R != NULL) {
			for (int i = 0; i < m_height + 2; i++) {
				free(tempInput_R[i]);
				free(tempInput_G[i]);
				free(tempInput_B[i]);
			}
			free(tempInput_R);
			free(tempInput_G);
			free(tempInput_B);
		}
		tempInput_R = NULL;
		tempInput_G = NULL;
		tempInput_B = NULL;

		if (tempOutput_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(tempOutput_R[i]);
				free(tempOutput_G[i]);
				free(tempOutput_B[i]);
			}
			free(tempOutput_R);
			free(tempOutput_G);
			free(tempOutput_B);
		}
		tempOutput_R = NULL;
		tempOutput_G = NULL;
		tempOutput_B = NULL;
	}
}


void CImageProcDoc::OnBnClickedSharp1()
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// 메모리 할당(출력 영상)
		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		// 마스크
		double mask[3][3] = { { -1. , -1. ,  -1. },
									   { -1. , 9. ,  -1. },
									   { -1. , -1. ,  -1. } };
		int mSize = 3;
		float **tempInput, **tempOutput, S = 0.0;
		// 임시 입력 영상
		tempInput = initMemory(tempInput, m_width + 2, m_height + 2);
		tempOutput = initMemory(tempOutput, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput[i + 1][k + 1] = m_InputImage[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						S = S + mask[n][m] * tempInput[n + i][m + k];
					}
				}
				tempOutput[i][k] = S;
				S = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput[i][k] > 255.0) tempOutput[i][k] = 255.0;
				if (tempOutput[i][k] < 0.0) tempOutput[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++)
				m_OutputImage[i][k] = (unsigned char)tempOutput[i][k];

		// 임시 메모리 해제
		if (tempInput != NULL) {
			for (int i = 0; i < m_height + 2; i++)
				free(tempInput[i]);
			free(tempInput);
		}
		tempInput = NULL;

		if (tempOutput != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(tempOutput[i]);
			free(tempOutput);
		}
		tempOutput = NULL;
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		// 마스크
		double mask[3][3] = { { -1. , -1. ,  -1. },
									   { -1. , 9. ,  -1. },
									   { -1. , -1. ,  -1. } };
		int mSize = 3;
		float **tempInput_R, **tempInput_G, **tempInput_B;
		float **tempOutput_R, **tempOutput_G, **tempOutput_B;
		float S_R = 0.0, S_G = 0.0, S_B = 0.0;
		// 임시 입력 영상
		tempInput_R = initMemory(tempInput_R, m_width + 2, m_height + 2);
		tempInput_G = initMemory(tempInput_G, m_width + 2, m_height + 2);
		tempInput_B = initMemory(tempInput_B, m_width + 2, m_height + 2);

		tempOutput_R = initMemory(tempOutput_R, m_Re_width, m_Re_height);
		tempOutput_G = initMemory(tempOutput_G, m_Re_width, m_Re_height);
		tempOutput_B = initMemory(tempOutput_B, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput_R[i + 1][k + 1] = (float)m_InputImage_R[i][k];
				tempInput_G[i + 1][k + 1] = (float)m_InputImage_G[i][k];
				tempInput_B[i + 1][k + 1] = (float)m_InputImage_B[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						S_R = S_R + mask[n][m] * tempInput_R[n + i][m + k];
						S_G = S_G + mask[n][m] * tempInput_G[n + i][m + k];
						S_B = S_B + mask[n][m] * tempInput_B[n + i][m + k];
					}
				}
				tempOutput_R[i][k] = S_R;
				tempOutput_G[i][k] = S_G;
				tempOutput_B[i][k] = S_B;

				S_R = 0.0;
				S_G = 0.0;
				S_B = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput_R[i][k] > 255.0) tempOutput_R[i][k] = 255.0;
				if (tempOutput_R[i][k] < 0.0) tempOutput_R[i][k] = 0.0;

				if (tempOutput_G[i][k] > 255.0) tempOutput_G[i][k] = 255.0;
				if (tempOutput_G[i][k] < 0.0) tempOutput_G[i][k] = 0.0;

				if (tempOutput_B[i][k] > 255.0) tempOutput_B[i][k] = 255.0;
				if (tempOutput_B[i][k] < 0.0) tempOutput_B[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage_R[i][k] = (unsigned char)tempOutput_R[i][k];
				m_OutputImage_G[i][k] = (unsigned char)tempOutput_G[i][k];
				m_OutputImage_B[i][k] = (unsigned char)tempOutput_B[i][k];
			}

		// 임시 메모리 해제
		if (tempInput_R != NULL) {
			for (int i = 0; i < m_height + 2; i++) {
				free(tempInput_R[i]);
				free(tempInput_G[i]);
				free(tempInput_B[i]);
			}
			free(tempInput_R);
			free(tempInput_G);
			free(tempInput_B);
		}
		tempInput_R = NULL;
		tempInput_G = NULL;
		tempInput_B = NULL;

		if (tempOutput_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(tempOutput_R[i]);
				free(tempOutput_G[i]);
				free(tempOutput_B[i]);
			}
			free(tempOutput_R);
			free(tempOutput_G);
			free(tempOutput_B);
		}
		tempOutput_R = NULL;
		tempOutput_G = NULL;
		tempOutput_B = NULL;
	}
}


void CImageProcDoc::OnBnClickedSharp2()
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// 메모리 할당(출력 영상)
		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		// 마스크
		double mask[3][3] = { { 0. , -1. ,  0. },
									   { -1. , 5. ,  -1. },
									   { 0. , -1. ,  0. } };
		int mSize = 3;
		float **tempInput, **tempOutput, S = 0.0;
		// 임시 입력 영상
		tempInput = initMemory(tempInput, m_width + 2, m_height + 2);
		tempOutput = initMemory(tempOutput, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput[i + 1][k + 1] = m_InputImage[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						S = S + mask[n][m] * tempInput[n + i][m + k];
					}
				}
				tempOutput[i][k] = S;
				S = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput[i][k] > 255.0) tempOutput[i][k] = 255.0;
				if (tempOutput[i][k] < 0.0) tempOutput[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++)
				m_OutputImage[i][k] = (unsigned char)tempOutput[i][k];

		// 임시 메모리 해제
		if (tempInput != NULL) {
			for (int i = 0; i < m_height + 2; i++)
				free(tempInput[i]);
			free(tempInput);
		}
		tempInput = NULL;

		if (tempOutput != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(tempOutput[i]);
			free(tempOutput);
		}
		tempOutput = NULL;
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		// 마스크
		double mask[3][3] = { { 0. , -1. ,  0. },
									   { -1. , 5. ,  -1. },
									   { 0. , -1. ,  0. } };
		int mSize = 3;
		float **tempInput_R, **tempInput_G, **tempInput_B;
		float **tempOutput_R, **tempOutput_G, **tempOutput_B;
		float S_R = 0.0, S_G = 0.0, S_B = 0.0;
		// 임시 입력 영상
		tempInput_R = initMemory(tempInput_R, m_width + 2, m_height + 2);
		tempInput_G = initMemory(tempInput_G, m_width + 2, m_height + 2);
		tempInput_B = initMemory(tempInput_B, m_width + 2, m_height + 2);

		tempOutput_R = initMemory(tempOutput_R, m_Re_width, m_Re_height);
		tempOutput_G = initMemory(tempOutput_G, m_Re_width, m_Re_height);
		tempOutput_B = initMemory(tempOutput_B, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput_R[i + 1][k + 1] = (float)m_InputImage_R[i][k];
				tempInput_G[i + 1][k + 1] = (float)m_InputImage_G[i][k];
				tempInput_B[i + 1][k + 1] = (float)m_InputImage_B[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						S_R = S_R + mask[n][m] * tempInput_R[n + i][m + k];
						S_G = S_G + mask[n][m] * tempInput_G[n + i][m + k];
						S_B = S_B + mask[n][m] * tempInput_B[n + i][m + k];
					}
				}
				tempOutput_R[i][k] = S_R;
				tempOutput_G[i][k] = S_G;
				tempOutput_B[i][k] = S_B;

				S_R = 0.0;
				S_G = 0.0;
				S_B = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput_R[i][k] > 255.0) tempOutput_R[i][k] = 255.0;
				if (tempOutput_R[i][k] < 0.0) tempOutput_R[i][k] = 0.0;

				if (tempOutput_G[i][k] > 255.0) tempOutput_G[i][k] = 255.0;
				if (tempOutput_G[i][k] < 0.0) tempOutput_G[i][k] = 0.0;

				if (tempOutput_B[i][k] > 255.0) tempOutput_B[i][k] = 255.0;
				if (tempOutput_B[i][k] < 0.0) tempOutput_B[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage_R[i][k] = (unsigned char)tempOutput_R[i][k];
				m_OutputImage_G[i][k] = (unsigned char)tempOutput_G[i][k];
				m_OutputImage_B[i][k] = (unsigned char)tempOutput_B[i][k];
			}

		// 임시 메모리 해제
		if (tempInput_R != NULL) {
			for (int i = 0; i < m_height + 2; i++) {
				free(tempInput_R[i]);
				free(tempInput_G[i]);
				free(tempInput_B[i]);
			}
			free(tempInput_R);
			free(tempInput_G);
			free(tempInput_B);
		}
		tempInput_R = NULL;
		tempInput_G = NULL;
		tempInput_B = NULL;

		if (tempOutput_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(tempOutput_R[i]);
				free(tempOutput_G[i]);
				free(tempOutput_B[i]);
			}
			free(tempOutput_R);
			free(tempOutput_G);
			free(tempOutput_B);
		}
		tempOutput_R = NULL;
		tempOutput_G = NULL;
		tempOutput_B = NULL;
	}
}


void CImageProcDoc::OnBnClickedBlur()
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// 메모리 할당(출력 영상)
		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		// 마스크
		double mask[3][3] = { { 0.111111 , 0.111111 ,  0.111111 },
							  { 0.111111 , 0.111111 ,  0.111111 },
							  { 0.111111 , 0.111111 ,  0.111111 } };
		int mSize = 3;
		float **tempInput, **tempOutput, S = 0.0;
		// 임시 입력 영상
		tempInput = initMemory(tempInput, m_width + 2, m_height + 2);
		tempOutput = initMemory(tempOutput, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput[i + 1][k + 1] = m_InputImage[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						S = S + mask[n][m] * tempInput[n + i][m + k];
					}
				}
				tempOutput[i][k] = S;
				S = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput[i][k] > 255.0) tempOutput[i][k] = 255.0;
				if (tempOutput[i][k] < 0.0) tempOutput[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++)
				m_OutputImage[i][k] = (unsigned char)tempOutput[i][k];

		// 임시 메모리 해제
		if (tempInput != NULL) {
			for (int i = 0; i < m_height + 2; i++)
				free(tempInput[i]);
			free(tempInput);
		}
		tempInput = NULL;

		if (tempOutput != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(tempOutput[i]);
			free(tempOutput);
		}
		tempOutput = NULL;
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		// 마스크
		double mask[3][3] = { { 0.111111 , 0.111111 ,  0.111111 },
							  { 0.111111 , 0.111111 ,  0.111111 },
							  { 0.111111 , 0.111111 ,  0.111111 } };
		int mSize = 3;
		float **tempInput_R, **tempInput_G, **tempInput_B;
		float **tempOutput_R, **tempOutput_G, **tempOutput_B;
		float S_R = 0.0, S_G = 0.0, S_B = 0.0;
		// 임시 입력 영상
		tempInput_R = initMemory(tempInput_R, m_width + 2, m_height + 2);
		tempInput_G = initMemory(tempInput_G, m_width + 2, m_height + 2);
		tempInput_B = initMemory(tempInput_B, m_width + 2, m_height + 2);

		tempOutput_R = initMemory(tempOutput_R, m_Re_width, m_Re_height);
		tempOutput_G = initMemory(tempOutput_G, m_Re_width, m_Re_height);
		tempOutput_B = initMemory(tempOutput_B, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput_R[i + 1][k + 1] = (float)m_InputImage_R[i][k];
				tempInput_G[i + 1][k + 1] = (float)m_InputImage_G[i][k];
				tempInput_B[i + 1][k + 1] = (float)m_InputImage_B[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						S_R = S_R + mask[n][m] * tempInput_R[n + i][m + k];
						S_G = S_G + mask[n][m] * tempInput_G[n + i][m + k];
						S_B = S_B + mask[n][m] * tempInput_B[n + i][m + k];
					}
				}
				tempOutput_R[i][k] = S_R;
				tempOutput_G[i][k] = S_G;
				tempOutput_B[i][k] = S_B;

				S_R = 0.0;
				S_G = 0.0;
				S_B = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput_R[i][k] > 255.0) tempOutput_R[i][k] = 255.0;
				if (tempOutput_R[i][k] < 0.0) tempOutput_R[i][k] = 0.0;

				if (tempOutput_G[i][k] > 255.0) tempOutput_G[i][k] = 255.0;
				if (tempOutput_G[i][k] < 0.0) tempOutput_G[i][k] = 0.0;

				if (tempOutput_B[i][k] > 255.0) tempOutput_B[i][k] = 255.0;
				if (tempOutput_B[i][k] < 0.0) tempOutput_B[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage_R[i][k] = (unsigned char)tempOutput_R[i][k];
				m_OutputImage_G[i][k] = (unsigned char)tempOutput_G[i][k];
				m_OutputImage_B[i][k] = (unsigned char)tempOutput_B[i][k];
			}

		// 임시 메모리 해제
		if (tempInput_R != NULL) {
			for (int i = 0; i < m_height + 2; i++) {
				free(tempInput_R[i]);
				free(tempInput_G[i]);
				free(tempInput_B[i]);
			}
			free(tempInput_R);
			free(tempInput_G);
			free(tempInput_B);
		}
		tempInput_R = NULL;
		tempInput_G = NULL;
		tempInput_B = NULL;

		if (tempOutput_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(tempOutput_R[i]);
				free(tempOutput_G[i]);
				free(tempOutput_B[i]);
			}
			free(tempOutput_R);
			free(tempOutput_G);
			free(tempOutput_B);
		}
		tempOutput_R = NULL;
		tempOutput_G = NULL;
		tempOutput_B = NULL;
	}
}


void CImageProcDoc::OnBnClickedEmbossing()
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		//(중요!) 출력 메모리 크기 결정
		m_Re_height = m_height;
		m_Re_width = m_width;

		// 메모리 할당(출력 영상)
		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		// 마스크
		double mask[3][3] = { { -1. , 0. ,  0. },
									   { 0. , 0. ,  0. },
									   { 0. , 0. ,  1. } };
		int mSize = 3;
		float **tempInput, **tempOutput, S = 0.0;
		// 임시 입력 영상
		tempInput = initMemory(tempInput, m_width + 2, m_height + 2);
		tempOutput = initMemory(tempOutput, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput[i + 1][k + 1] = m_InputImage[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						S = S + mask[n][m] * tempInput[n + i][m + k];
					}
				}
				tempOutput[i][k] = S + 128;
				S = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput[i][k] > 255.0) tempOutput[i][k] = 255.0;
				if (tempOutput[i][k] < 0.0) tempOutput[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++)
				m_OutputImage[i][k] = (unsigned char)tempOutput[i][k];

		// 임시 메모리 해제
		if (tempInput != NULL) {
			for (int i = 0; i < m_height + 2; i++)
				free(tempInput[i]);
			free(tempInput);
		}
		tempInput = NULL;

		if (tempOutput != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(tempOutput[i]);
			free(tempOutput);
		}
		tempOutput = NULL;
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		// *** 진짜 영상처리 알고리즘 구현 *** //
		// 마스크
		double mask[3][3] = { { -1. , 0. ,  0. },
									   { 0. , 0. ,  0. },
									   { 0. , 0. ,  1. } };
		int mSize = 3;
		float **tempInput_R, **tempInput_G, **tempInput_B;
		float **tempOutput_R, **tempOutput_G, **tempOutput_B;
		float S_R = 0.0, S_G = 0.0, S_B = 0.0;
		// 임시 입력 영상
		tempInput_R = initMemory(tempInput_R, m_width + 2, m_height + 2);
		tempInput_G = initMemory(tempInput_G, m_width + 2, m_height + 2);
		tempInput_B = initMemory(tempInput_B, m_width + 2, m_height + 2);

		tempOutput_R = initMemory(tempOutput_R, m_Re_width, m_Re_height);
		tempOutput_G = initMemory(tempOutput_G, m_Re_width, m_Re_height);
		tempOutput_B = initMemory(tempOutput_B, m_Re_width, m_Re_height);

		// 입력 --> 임시 입력
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				tempInput_R[i + 1][k + 1] = (float)m_InputImage_R[i][k];
				tempInput_G[i + 1][k + 1] = (float)m_InputImage_G[i][k];
				tempInput_B[i + 1][k + 1] = (float)m_InputImage_B[i][k];
			}
		}

		// 회선 연산 처리
		for (int i = 0; i < m_height; i++) {
			for (int k = 0; k < m_width; k++) {
				for (int n = 0; n < mSize; n++) {
					for (int m = 0; m < mSize; m++) {
						S_R = S_R + mask[n][m] * tempInput_R[n + i][m + k];
						S_G = S_G + mask[n][m] * tempInput_G[n + i][m + k];
						S_B = S_B + mask[n][m] * tempInput_B[n + i][m + k];
					}
				}
				tempOutput_R[i][k] = S_R + 128;
				tempOutput_G[i][k] = S_G + 128;
				tempOutput_B[i][k] = S_B + 128;

				S_R = 0.0;
				S_G = 0.0;
				S_B = 0.0;
			}
		}

		//  임시 출력의 범위를 0~255로
		for (int i = 0; i < m_Re_height; i++) {
			for (int k = 0; k < m_Re_width; k++) {
				if (tempOutput_R[i][k] > 255.0) tempOutput_R[i][k] = 255.0;
				if (tempOutput_R[i][k] < 0.0) tempOutput_R[i][k] = 0.0;

				if (tempOutput_G[i][k] > 255.0) tempOutput_G[i][k] = 255.0;
				if (tempOutput_G[i][k] < 0.0) tempOutput_G[i][k] = 0.0;

				if (tempOutput_B[i][k] > 255.0) tempOutput_B[i][k] = 255.0;
				if (tempOutput_B[i][k] < 0.0) tempOutput_B[i][k] = 0.0;
			}
		}

		// 임시 출력 --> 출력 메모리
		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage_R[i][k] = (unsigned char)tempOutput_R[i][k];
				m_OutputImage_G[i][k] = (unsigned char)tempOutput_G[i][k];
				m_OutputImage_B[i][k] = (unsigned char)tempOutput_B[i][k];
			}

		// 임시 메모리 해제
		if (tempInput_R != NULL) {
			for (int i = 0; i < m_height + 2; i++) {
				free(tempInput_R[i]);
				free(tempInput_G[i]);
				free(tempInput_B[i]);
			}
			free(tempInput_R);
			free(tempInput_G);
			free(tempInput_B);
		}
		tempInput_R = NULL;
		tempInput_G = NULL;
		tempInput_B = NULL;

		if (tempOutput_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(tempOutput_R[i]);
				free(tempOutput_G[i]);
				free(tempOutput_B[i]);
			}
			free(tempOutput_R);
			free(tempOutput_G);
			free(tempOutput_B);
		}
		tempOutput_R = NULL;
		tempOutput_G = NULL;
		tempOutput_B = NULL;
	}
}


void CImageProcDoc::OnBnClickedZoomin1(double cons)
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		int scale = (int)cons;

		m_Re_height = m_height * scale;
		m_Re_width = m_width * scale;

		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		for (int i = 0; i < m_height; i++)
			for (int k = 0; k < m_width; k++)
				m_OutputImage[i * scale][k * scale] = m_InputImage[i][k];
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		int scale = (int)cons;

		m_Re_height = m_height * scale;
		m_Re_width = m_width * scale;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage_R[i][k] = 0;
				m_OutputImage_G[i][k] = 0;
				m_OutputImage_B[i][k] = 0;
			}

		for (int i = 0; i < m_height; i++)
			for (int k = 0; k < m_width; k++) {
				m_OutputImage_R[i * scale][k * scale] = m_InputImage_R[i][k];
				m_OutputImage_G[i * scale][k * scale] = m_InputImage_G[i][k];
				m_OutputImage_B[i * scale][k * scale] = m_InputImage_B[i][k];
			}
	}
}


void CImageProcDoc::OnBnClickedZoomin2(double cons)
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		int scale = (int)cons;

		m_Re_height = m_height * scale;
		m_Re_width = m_width * scale;

		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++)
				m_OutputImage[i][k] = m_InputImage[i / scale][k / scale];
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		int scale = (int)cons;

		m_Re_height = m_height * scale;
		m_Re_width = m_width * scale;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage_R[i][k] = m_InputImage_R[i / scale][k / scale];
				m_OutputImage_G[i][k] = m_InputImage_G[i / scale][k / scale];
				m_OutputImage_B[i][k] = m_InputImage_B[i / scale][k / scale];
			}
	}
}


void CImageProcDoc::OnBnClickedZoomout1(double cons)
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		int scale = (int)cons;

		m_Re_height = m_height / scale;
		m_Re_width = m_width / scale;

		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		for (int i = 0; i < m_height; i++)
			for (int k = 0; k < m_width; k++)
				m_OutputImage[i / scale][k / scale] = m_InputImage[i][k];
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		int scale = (int)cons;

		m_Re_height = m_height / scale;
		m_Re_width = m_width / scale;

		// Allocate Memory
		if ((m_Re_height % 2) != 0)
			m_Re_height++;
		if ((m_Re_width % 2) != 0)
			m_Re_height++;

		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		for (int i = 0; i < m_height; i++)
			for (int k = 0; k < m_width; k++) {
				m_OutputImage_R[i / scale][k / scale] = m_InputImage_R[i][k];
				m_OutputImage_G[i / scale][k / scale] = m_InputImage_G[i][k];
				m_OutputImage_B[i / scale][k / scale] = m_InputImage_B[i][k];
			}
	}
}


void CImageProcDoc::OnBnClickedZoomout2(double cons)
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		int scale = (int)cons;

		m_Re_height = m_height / scale;
		m_Re_width = m_width / scale;

		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++)
				m_OutputImage[i][k] = m_InputImage[i * scale][k * scale];
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		int scale = (int)cons;

		m_Re_height = m_height / scale;
		m_Re_width = m_width / scale;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				m_OutputImage_R[i][k] = m_InputImage_R[i * scale][k * scale];
				m_OutputImage_G[i][k] = m_InputImage_G[i * scale][k * scale];
				m_OutputImage_B[i][k] = m_InputImage_B[i * scale][k * scale];
			}
	}
}


double CImageProcDoc::doubleABS(double num)
{
	if (num >= 0)
		return num;
	else
		return -num;
}


void CImageProcDoc::OnBnClickedPosterRasing(unsigned char cons)
{
	if ((strcmp(FNE, raw_upper) == 0 || strcmp(FNE, raw_lower) == 0)) {
		if (m_OutputImage != NULL) {
			for (int i = 0; i < m_Re_height; i++)
				free(m_OutputImage[i]);
			free(m_OutputImage);
		}
		m_OutputImage = NULL;

		m_Re_height = m_height;
		m_Re_width = m_width;

		const int axis = 256;
		int div = 256 / (int)cons;
		int num = axis - div;

		m_OutputImage = initMemory(m_OutputImage, m_Re_width, m_Re_height);

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				while (num != 0) {
					if (num >= m_InputImage[i][k])
						m_OutputImage[i][k] = (char)num + div;

					num -= div;
				}
				num = axis - div;
			}
	}
	else if (strcmp(FNE, jpg_upper) == 0 || strcmp(FNE, jpg_lower) == 0) {
		if (m_OutputImage_R != NULL) {
			for (int i = 0; i < m_Re_height; i++) {
				free(m_OutputImage_R[i]);
				free(m_OutputImage_G[i]);
				free(m_OutputImage_B[i]);
			}
			free(m_OutputImage_R);
			free(m_OutputImage_G);
			free(m_OutputImage_B);
		}
		m_OutputImage_R = NULL;
		m_OutputImage_G = NULL;
		m_OutputImage_B = NULL;

		m_Re_height = m_height;
		m_Re_width = m_width;

		// Allocate Memory
		// Red Color
		m_OutputImage_R = initMemory(m_OutputImage_R, m_Re_width, m_Re_height);

		// Green Color
		m_OutputImage_G = initMemory(m_OutputImage_G, m_Re_width, m_Re_height);

		// Blue Color
		m_OutputImage_B = initMemory(m_OutputImage_B, m_Re_width, m_Re_height);

		const int axis = 256;
		int div = 256 / (int)cons;
		int num = axis - div;

		for (int i = 0; i < m_Re_height; i++)
			for (int k = 0; k < m_Re_width; k++) {
				while (num != 0) {
					if (num >= m_InputImage_R[i][k])
						m_OutputImage_R[i][k] = (char)num + div;

					if (num >= m_InputImage_G[i][k])
						m_OutputImage_G[i][k] = (char)num + div;

					if (num >= m_InputImage_B[i][k])
						m_OutputImage_B[i][k] = (char)num + div;

					num -= div;
				}
				num = axis - div;
			}
	}
}