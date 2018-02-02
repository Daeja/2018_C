
// Image ProcDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Image Proc.h"
#include "Image ProcDlg.h"
#include "Image ProcDoc.h"
#include "afxdialogex.h"

#include "Constant1Dlg.h"
#include "Constant2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcDlg 대화 상자
CImageProcDoc pDoc;


CImageProcDlg::CImageProcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IMAGEPROC_DIALOG, pParent)
	, m_edit_R(0)
	, m_edit_G(0)
	, m_edit_B(0)
	, m_slider_R(0)
	, m_slider_G(0)
	, m_slider_B(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageProcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_CONTROL1, m_PicControl1);
	DDX_Control(pDX, IDC_PIC_CONTROL2, m_PicControl2);
	DDX_Text(pDX, IDC_EDIT_R, m_edit_R);
	DDX_Text(pDX, IDC_EDIT_G, m_edit_G);
	DDX_Text(pDX, IDC_EDIT_B, m_edit_B);
	DDX_Slider(pDX, IDC_SLIDER_R, m_slider_R);
	DDV_MinMaxInt(pDX, m_slider_R, 0, 255);
	DDX_Slider(pDX, IDC_SLIDER_G, m_slider_G);
	DDV_MinMaxInt(pDX, m_slider_G, 0, 255);
	DDX_Slider(pDX, IDC_SLIDER_B, m_slider_B);
	DDV_MinMaxInt(pDX, m_slider_B, 0, 255);
	DDX_Control(pDX, IDC_SLIDER_R, m_Slider_C_R);
	DDX_Control(pDX, IDC_EDIT_R, m_edit_C_R);
	DDX_Control(pDX, IDC_SLIDER_G, m_Slider_C_G);
	DDX_Control(pDX, IDC_SLIDER_B, m_Slider_C_B);
	DDX_Control(pDX, IDC_EDIT_G, m_edit_C_G);
	DDX_Control(pDX, IDC_EDIT_B, m_edit_C_B);
}

BEGIN_MESSAGE_MAP(CImageProcDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN_FILE, &CImageProcDlg::OnBnClickedOpenFile)
	ON_BN_CLICKED(IDC_CLOSE_DIALOG, &CImageProcDlg::OnBnClickedCloseDialog)
	ON_BN_CLICKED(IDC_SAVE_FILE, &CImageProcDlg::OnBnClickedSaveFile)
	ON_BN_CLICKED(IDC_EQUAL_IMAGE, &CImageProcDlg::OnBnClickedEqualImage)
	ON_BN_CLICKED(IDC_BRIGHT, &CImageProcDlg::OnBnClickedBright)
	ON_BN_CLICKED(IDC_DIM, &CImageProcDlg::OnBnClickedDim)
	ON_BN_CLICKED(IDC_MULTI, &CImageProcDlg::OnBnClickedMulti)
	ON_BN_CLICKED(IDC_DIVISION, &CImageProcDlg::OnBnClickedDivision)
	ON_BN_CLICKED(IDC_NEG, &CImageProcDlg::OnBnClickedNeg)
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_EXTENSION_FUNC, &CImageProcDlg::OnBnClickedExtensionFunc)
	ON_EN_CHANGE(IDC_EDIT_R, &CImageProcDlg::OnEnChangeEditR)
	ON_EN_CHANGE(IDC_EDIT_G, &CImageProcDlg::OnEnChangeEditG)
	ON_EN_CHANGE(IDC_EDIT_B, &CImageProcDlg::OnEnChangeEditB)
	ON_BN_CLICKED(IDC_RETURN, &CImageProcDlg::OnBnClickedReturn)
	ON_BN_CLICKED(IDC_TEMP_SAVE, &CImageProcDlg::OnBnClickedTempSave)
	ON_BN_CLICKED(IDC_AND, &CImageProcDlg::OnBnClickedAnd)
	ON_BN_CLICKED(IDC_OR, &CImageProcDlg::OnBnClickedOr)
	ON_BN_CLICKED(IDC_XOR, &CImageProcDlg::OnBnClickedXor)
	ON_BN_CLICKED(IDC_PARABOLA_CAP, &CImageProcDlg::OnBnClickedParabolaCap)
	ON_BN_CLICKED(IDC_PARABOLA_CUP, &CImageProcDlg::OnBnClickedParabolaCup)
	ON_BN_CLICKED(IDC_STRETCHING, &CImageProcDlg::OnBnClickedStretching)
	ON_BN_CLICKED(IDC_HIST, &CImageProcDlg::OnBnClickedHist)
	ON_BN_CLICKED(IDC_HIST_EQUAL, &CImageProcDlg::OnBnClickedHistEqual)
	ON_BN_CLICKED(IDC_END_IN, &CImageProcDlg::OnBnClickedEndIn)
	ON_BN_CLICKED(IDC_VERTICAL_EDGE, &CImageProcDlg::OnBnClickedVerticalEdge)
	ON_BN_CLICKED(IDC_HORIZONTAL_EDGE, &CImageProcDlg::OnBnClickedHorizontalEdge)
	ON_BN_CLICKED(IDC_SIMILAR_EDGE, &CImageProcDlg::OnBnClickedSimilarEdge)
	ON_BN_CLICKED(IDC_SUB_EDGE, &CImageProcDlg::OnBnClickedSubEdge)
	ON_BN_CLICKED(IDC_HORIZONTAL_ROBERTS, &CImageProcDlg::OnBnClickedHorizontalRoberts)
	ON_BN_CLICKED(IDC_VERTICAL_ROBERTS, &CImageProcDlg::OnBnClickedVerticalRoberts)
	ON_BN_CLICKED(IDC_HORIZONTAL_PREWITT, &CImageProcDlg::OnBnClickedHorizontalPrewitt)
	ON_BN_CLICKED(IDC_VERTICAL_PREWITT, &CImageProcDlg::OnBnClickedVerticalPrewitt)
	ON_BN_CLICKED(IDC_HORIZONTAL_SOBEL, &CImageProcDlg::OnBnClickedHorizontalSobel)
	ON_BN_CLICKED(IDC_VERTICAL_SOBEL, &CImageProcDlg::OnBnClickedVerticalSobel)
	ON_BN_CLICKED(IDC_SHARP1, &CImageProcDlg::OnBnClickedSharp1)
	ON_BN_CLICKED(IDC_SHARP2, &CImageProcDlg::OnBnClickedSharp2)
	ON_BN_CLICKED(IDC_BLUR, &CImageProcDlg::OnBnClickedBlur)
	ON_BN_CLICKED(IDC_EMBOSSING, &CImageProcDlg::OnBnClickedEmbossing)
	ON_BN_CLICKED(IDC_ZOOMIN1, &CImageProcDlg::OnBnClickedZoomin1)
	ON_BN_CLICKED(IDC_ZOOMIN2, &CImageProcDlg::OnBnClickedZoomin2)
	ON_BN_CLICKED(IDC_ZOOMOUT1, &CImageProcDlg::OnBnClickedZoomout1)
	ON_BN_CLICKED(IDC_ZOOMOUT2, &CImageProcDlg::OnBnClickedZoomout2)
	ON_BN_CLICKED(IDC_POSTER_RASING, &CImageProcDlg::OnBnClickedPosterRasing)
END_MESSAGE_MAP()


// CImageProcDlg 메시지 처리기

BOOL CImageProcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	// UI 조절
	int frame_width = 1280;
	int frame_height = 760;
	CStatic * pDC;

	// 메인 다이얼로그 사이즈 및 위치 조절
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	int x = (width / 2) - (frame_width / 2);
	int y = (height / 2) - (frame_height / 2);
	this->SetWindowPos(NULL, x, y, frame_width, frame_height, NULL);
	
	// 픽쳐 컨트롤 위치 조절
	int pic_control_width = 512 + 10;
	int pic_control_height = 512 + 10;

	pDC = (CStatic *)GetDlgItem(IDC_PIC_CONTROL1);
	pDC->SetWindowPos(NULL, 5, 5, pic_control_width, pic_control_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_PIC_CONTROL2);
	pDC->SetWindowPos(NULL, pic_control_width + 10, 5, pic_control_width, pic_control_height, NULL);

	// 버튼 위치 조절
	int btn_width = (frame_width - (pic_control_width * 2) - 20) / 2 - 15;
	int btn_height = 50;

	pDC = (CStatic *)GetDlgItem(IDC_EQUAL_IMAGE);
	pDC->SetWindowPos(NULL, 1063, pic_control_height - (btn_height * 4) - 15, (btn_width * 2) + 5, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_TEMP_SAVE);
	pDC->SetWindowPos(NULL, 1063, pic_control_height - (btn_height * 3) - 10, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_RETURN);
	pDC->SetWindowPos(NULL, 1161, pic_control_height - (btn_height * 3) - 10, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_SAVE_FILE);
	pDC->SetWindowPos(NULL, 1063, pic_control_height - (btn_height * 2) - 5, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_OPEN_FILE);
	pDC->SetWindowPos(NULL, 1161, pic_control_height - (btn_height * 2) - 5, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_EXTENSION_FUNC);
	pDC->SetWindowPos(NULL, 1063, pic_control_height - btn_height, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_CLOSE_DIALOG);
	pDC->SetWindowPos(NULL, 1161, pic_control_height - btn_height, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_BRIGHT);
	pDC->SetWindowPos(NULL, 15, pic_control_height + 30, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_DIM);
	pDC->SetWindowPos(NULL, 15, pic_control_height + 30 + btn_height, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_POSTER_RASING);
	pDC->SetWindowPos(NULL, 15, pic_control_height + 30 + (btn_height * 2), btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_MULTI);
	pDC->SetWindowPos(NULL, 113, pic_control_height + 30, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_DIVISION);
	pDC->SetWindowPos(NULL, 113, pic_control_height + 30 + btn_height, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_NEG);
	pDC->SetWindowPos(NULL, 113, pic_control_height + 30 + (btn_height * 2), btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_AND);
	pDC->SetWindowPos(NULL, 211, pic_control_height + 30, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_OR);
	pDC->SetWindowPos(NULL, 211, pic_control_height + 30 + btn_height, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_XOR);
	pDC->SetWindowPos(NULL, 211, pic_control_height + 30 + (btn_height * 2), btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_PARABOLA_CAP);
	pDC->SetWindowPos(NULL, 309, pic_control_height + 30, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_PARABOLA_CUP);
	pDC->SetWindowPos(NULL, 309, pic_control_height + 30 + btn_height, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_STRETCHING);
	pDC->SetWindowPos(NULL, 309, pic_control_height + 30 + (btn_height * 2), btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_HIST);
	pDC->SetWindowPos(NULL, 407, pic_control_height + 30, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_HIST_EQUAL);
	pDC->SetWindowPos(NULL, 407, pic_control_height + 30 + btn_height, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_END_IN);
	pDC->SetWindowPos(NULL, 407, pic_control_height + 30 + (btn_height * 2), btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_VERTICAL_EDGE);
	pDC->SetWindowPos(NULL, 525, pic_control_height + 30, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_HORIZONTAL_EDGE);
	pDC->SetWindowPos(NULL, 525, pic_control_height + 30 + btn_height, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_SIMILAR_EDGE);
	pDC->SetWindowPos(NULL, 525, pic_control_height + 30 + (btn_height * 2), btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_SUB_EDGE);
	pDC->SetWindowPos(NULL, 623, pic_control_height + 30, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_HORIZONTAL_ROBERTS);
	pDC->SetWindowPos(NULL, 721, pic_control_height + 30, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_HORIZONTAL_PREWITT);
	pDC->SetWindowPos(NULL, 721, pic_control_height + 30 + btn_height, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_HORIZONTAL_SOBEL);
	pDC->SetWindowPos(NULL, 721, pic_control_height + 30 + (btn_height * 2), btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_VERTICAL_ROBERTS);
	pDC->SetWindowPos(NULL, 819, pic_control_height + 30, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_VERTICAL_PREWITT);
	pDC->SetWindowPos(NULL, 819, pic_control_height + 30 + btn_height, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_VERTICAL_SOBEL);
	pDC->SetWindowPos(NULL, 819, pic_control_height + 30 + (btn_height * 2), btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_SHARP1);
	pDC->SetWindowPos(NULL, 917, pic_control_height + 30, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_SHARP2);
	pDC->SetWindowPos(NULL, 917, pic_control_height + 30 + btn_height, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_EMBOSSING);
	pDC->SetWindowPos(NULL, 1015, pic_control_height + 30, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_BLUR);
	pDC->SetWindowPos(NULL, 1015, pic_control_height + 30 + btn_height, btn_width, btn_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_ZOOMIN1);
	pDC->SetWindowPos(NULL, 1140, pic_control_height + 30, btn_width, btn_height - 20, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_ZOOMIN2);
	pDC->SetWindowPos(NULL, 1140, pic_control_height + 70, btn_width, btn_height - 20, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_ZOOMOUT1);
	pDC->SetWindowPos(NULL, 1140, pic_control_height + 110, btn_width, btn_height - 20, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_ZOOMOUT2);
	pDC->SetWindowPos(NULL, 1140, pic_control_height + 150, btn_width, btn_height - 20, NULL);

	// 라벨 및 에디트 텍스트 위치 조절
	int label_width = 150;
	int label_height = 15;
	int edit_RGB_width = 30;
	int edit_RGB_height = 20;

	pDC = (CStatic *)GetDlgItem(IDC_STATIC_RGB);
	pDC->SetWindowPos(NULL, 1069 + 20, 5, label_width, label_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_EDIT_R);
	pDC->SetWindowPos(NULL, 1069 + 10, label_height + 5, edit_RGB_width, edit_RGB_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_EDIT_G);
	pDC->SetWindowPos(NULL, 1069 + 43 + edit_RGB_width, label_height + 5, edit_RGB_width, edit_RGB_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_EDIT_B);
	pDC->SetWindowPos(NULL, 1069 + 76 + (edit_RGB_width * 2), label_height + 5, edit_RGB_width, edit_RGB_height, NULL);

	// 슬라이더 위치 조절
	int slider_width = (btn_width * 2) / 3;
	int slider_height = 256;

	pDC = (CStatic *)GetDlgItem(IDC_SLIDER_R);
	pDC->SetWindowPos(NULL, 1069 + 5, 35, slider_width, slider_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_SLIDER_G);
	pDC->SetWindowPos(NULL, 1069 + slider_width + 5, 35, slider_width, slider_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_SLIDER_B);
	pDC->SetWindowPos(NULL, 1069 + (slider_width * 2) + 5, 35, slider_width, slider_height, NULL);

	// 그룹박스 위치 조절
	pDC = (CStatic *)GetDlgItem(IDC_IMAGE_PROC_GROUP1);
	pDC->SetWindowPos(NULL, 5, pic_control_height + 5, frame_width - 30, (btn_height * 3) + 40, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_IMAGE_POINT_PROC_GROUP);
	pDC->SetWindowPos(NULL, 10, pic_control_height + 15, (btn_width * 5) + 35, (btn_height * 3) + 20, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_IMAGE_AREA_PROC_GROUP);
	pDC->SetWindowPos(NULL, 520, pic_control_height + 15, (btn_width * 6) + 40, (btn_height * 3) + 20, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_IMAGE_GEOMETRY_PROC_GROUP);
	pDC->SetWindowPos(NULL, 1128, pic_control_height + 15, btn_width + 25, (btn_height * 3) + 20, NULL);

	// 슬라이더 컨트롤 초기화
	m_Slider_C_R.SetRange(0, 255);
	m_Slider_C_G.SetRange(0, 255);
	m_Slider_C_B.SetRange(0, 255);

	m_Slider_C_R.SetRangeMin(0);
	m_Slider_C_G.SetRangeMin(0);
	m_Slider_C_B.SetRangeMin(0);

	m_Slider_C_R.SetRangeMax(255);
	m_Slider_C_G.SetRangeMax(255);
	m_Slider_C_B.SetRangeMax(255);

	m_Slider_C_R.SetTicFreq(5);
	m_Slider_C_G.SetTicFreq(5);
	m_Slider_C_B.SetTicFreq(5);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CImageProcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

		unsigned char R, G, B;

		CDC * p = m_PicControl1.GetWindowDC();
		CDC memDC;
		CBitmap * pOldBitmap;
		CBitmap bitmap;					// 메모리 DC 선언

		// 입력 이미지 정의
		memDC.CreateCompatibleDC(p);	// 객체 생성 (호환됨)
										// 화면DC와 호환되는 비트맵 생성
		bitmap.CreateCompatibleBitmap(p, pDoc.m_width, pDoc.m_height);

		pOldBitmap = memDC.SelectObject(&bitmap);

		memDC.PatBlt(0, 0, pDoc.m_width, pDoc.m_height, WHITENESS);	//초기화
															// 메모리에 출력하기
		for (int i = 0; i < pDoc.m_height; i++) {
			for (int k = 0; k < pDoc.m_width; k++) {
				if (strcmp(pDoc.FNE, pDoc.raw_upper) == 0 || strcmp(pDoc.FNE, pDoc.raw_lower) == 0)
					R = G = B = pDoc.m_InputImage[i][k];
				else if (strcmp(pDoc.FNE, pDoc.jpg_upper) == 0 || strcmp(pDoc.FNE, pDoc.jpg_lower) == 0) {
					R = pDoc.m_InputImage_R[i][k];
					G = pDoc.m_InputImage_G[i][k];
					B = pDoc.m_InputImage_B[i][k];
				}
				memDC.SetPixel(k, i, RGB(R, G, B));
			}
		}

		p->BitBlt(5, 5, pDoc.m_width, pDoc.m_height, &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(pOldBitmap);
		memDC.DeleteDC();
		bitmap.DeleteObject();


		// 출력 이미지 정의
		p = m_PicControl2.GetWindowDC();

		memDC.CreateCompatibleDC(p);

		// 화면 DC와 호환되는 bitmap 생성
		bitmap.CreateCompatibleBitmap(p, pDoc.m_Re_width, pDoc.m_Re_height);

		pOldBitmap = memDC.SelectObject(&bitmap);

		memDC.PatBlt(0, 0, pDoc.m_Re_width, pDoc.m_Re_height, WHITENESS);	//초기화
																	// 메모리에 출력하기

		// Memory에 출력
		for (int i = 0; i < pDoc.m_Re_height; i++) {
			if (pDoc.m_OutputImage == NULL && pDoc.m_InputImage != NULL)
				break;
			if (pDoc.m_OutputImage_R == NULL && pDoc.m_InputImage_R != NULL)
				break;

			for (int k = 0; k < pDoc.m_Re_width; k++) {
				if (strcmp(pDoc.FNE, pDoc.raw_upper) == 0 || strcmp(pDoc.FNE, pDoc.raw_lower) == 0)
					R = G = B = pDoc.m_OutputImage[i][k];
				else if (strcmp(pDoc.FNE, pDoc.jpg_upper) == 0 || strcmp(pDoc.FNE, pDoc.jpg_lower) == 0) {
					R = pDoc.m_OutputImage_R[i][k];
					G = pDoc.m_OutputImage_G[i][k];
					B = pDoc.m_OutputImage_B[i][k];
				}
				memDC.SetPixel(k, i, RGB(R, G, B));
			}
		}

		// Memory DC -> Display DC에 복사(고속)
		p->BitBlt(5, 5, pDoc.m_Re_width, pDoc.m_Re_height, &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(pOldBitmap);
		memDC.DeleteDC();
		bitmap.DeleteObject();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CImageProcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CImageProcDlg::OnBnClickedOpenFile()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Image (*.JPG; *.jpg; *.RAW; *.raw) | *.JPG; *.jpg; *.RAW; *.raw | All Files(*.*)|*.*||"));

	if (IDOK == dlg.DoModal()) {
		CString pathName = dlg.GetPathName();
		pDoc.OnBnClickedOpenFile(pathName);
	}

	CStatic * pDC;

	pDC = (CStatic *)GetDlgItem(IDC_EQUAL_IMAGE);
	pDC->EnableWindow(TRUE);

	Invalidate();
}

void CImageProcDlg::OnBnClickedExtensionFunc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CStatic * pDC;

	pDC = (CStatic *)GetDlgItem(IDC_EDIT_R);
	pDC->EnableWindow(TRUE);

	pDC = (CStatic *)GetDlgItem(IDC_EDIT_G);
	pDC->EnableWindow(TRUE);

	pDC = (CStatic *)GetDlgItem(IDC_EDIT_B);
	pDC->EnableWindow(TRUE);

	pDC = (CStatic *)GetDlgItem(IDC_SLIDER_R);
	pDC->EnableWindow(TRUE);

	pDC = (CStatic *)GetDlgItem(IDC_SLIDER_G);
	pDC->EnableWindow(TRUE);

	pDC = (CStatic *)GetDlgItem(IDC_SLIDER_B);
	pDC->EnableWindow(TRUE);
}


void CImageProcDlg::OnBnClickedSaveFile()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;

	if ((strcmp(pDoc.FNE, pDoc.raw_upper) == 0 || strcmp(pDoc.FNE, pDoc.raw_lower) == 0))
		str = _T("Image(*.RAW; *.raw) | *.RAW; *.raw | All Files(*.*) | *.* || ");
	else if (strcmp(pDoc.FNE, pDoc.jpg_upper) == 0 || strcmp(pDoc.FNE, pDoc.jpg_lower) == 0)
		str = _T("Image(*.JPG; *.jpg) | *.JPG; *.jpg | All Files(*.*) | *.* || ");

	CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY, str);

	if (IDOK == dlg.DoModal()) {
		CString pathName = dlg.GetPathName();
		pDoc.OnBnClickedSaveFile(pathName);
	}

	Invalidate();
}



void CImageProcDlg::OnBnClickedCloseDialog()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pDoc.OnBnClickedCloseDialog();
}

void CImageProcDlg::OnBnClickedEqualImage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CStatic * pDC;

	pDoc.OnBnClickedEqualImage();

	if (strcmp(pDoc.FNE, pDoc.raw_upper) == 0 || strcmp(pDoc.FNE, pDoc.raw_lower) == 0) {
		pDC = (CStatic *)GetDlgItem(IDC_EXTENSION_FUNC);
		pDC->EnableWindow(FALSE);
	}
	else if (strcmp(pDoc.FNE, pDoc.jpg_upper) == 0 || strcmp(pDoc.FNE, pDoc.jpg_lower) == 0) {
		pDC = (CStatic *)GetDlgItem(IDC_EXTENSION_FUNC);
		pDC->EnableWindow(TRUE);
	}
	
	pDC = (CStatic *)GetDlgItem(IDC_RETURN);
	pDC->EnableWindow(TRUE);

	pDC = (CStatic *)GetDlgItem(IDC_TEMP_SAVE);
	pDC->EnableWindow(TRUE);

	// 슬라이더 컨트롤 위치 초기화
	m_Slider_C_R.SetPos(0);
	m_Slider_C_G.SetPos(0);
	m_Slider_C_B.SetPos(0);

	if (strcmp(pDoc.FNE, pDoc.raw_upper) == 0 || strcmp(pDoc.FNE, pDoc.raw_lower) == 0)
		enableButton(TRUE);
	else if (strcmp(pDoc.FNE, pDoc.jpg_upper) == 0 || strcmp(pDoc.FNE, pDoc.jpg_lower) == 0)
		enableButton(FALSE);

	Invalidate();
}


void CImageProcDlg::OnBnClickedBright()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CConstant1Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedBright(dlg.m_Constant);

	Invalidate();
}


void CImageProcDlg::OnBnClickedDim()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CConstant1Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedDim(dlg.m_Constant);

	Invalidate();
}


void CImageProcDlg::OnBnClickedMulti()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CConstant1Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedMulti(dlg.m_Constant);

	Invalidate();
}


void CImageProcDlg::OnBnClickedDivision()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CConstant1Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedDivision(dlg.m_Constant);

	Invalidate();
}


void CImageProcDlg::OnBnClickedNeg()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pDoc.OnBnClickedNeg();

	Invalidate();
}


void CImageProcDlg::enableButton(bool flag)
{
	// 버튼 활성화
	CStatic * pDC;
	if (flag == TRUE) {
		pDC = (CStatic *)GetDlgItem(IDC_SAVE_FILE);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_BRIGHT);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_DIM);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_MULTI);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_DIVISION);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_AND);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_OR);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_XOR);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_NEG);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_POSTER_RASING);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_STRETCHING);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_END_IN);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_PARABOLA_CAP);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_PARABOLA_CUP);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_HIST);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_HIST_EQUAL);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_VERTICAL_EDGE);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_HORIZONTAL_EDGE);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_HORIZONTAL_SOBEL);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_SUB_EDGE);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_SIMILAR_EDGE);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_HORIZONTAL_ROBERTS);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_HORIZONTAL_PREWITT);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_VERTICAL_ROBERTS);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_VERTICAL_PREWITT);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_VERTICAL_SOBEL);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_EMBOSSING);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_SHARP1);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_SHARP2);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_BLUR);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_ZOOMIN1);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_ZOOMIN2);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_ZOOMOUT1);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_ZOOMOUT2);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_EDIT_R);
		pDC->EnableWindow(FALSE);

		pDC = (CStatic *)GetDlgItem(IDC_EDIT_G);
		pDC->EnableWindow(FALSE);

		pDC = (CStatic *)GetDlgItem(IDC_EDIT_B);
		pDC->EnableWindow(FALSE);

		pDC = (CStatic *)GetDlgItem(IDC_SLIDER_R);
		pDC->EnableWindow(FALSE);

		pDC = (CStatic *)GetDlgItem(IDC_SLIDER_G);
		pDC->EnableWindow(FALSE);

		pDC = (CStatic *)GetDlgItem(IDC_SLIDER_B);
		pDC->EnableWindow(FALSE);

		pDC = (CStatic *)GetDlgItem(IDC_EXTENSION_FUNC);
		pDC->EnableWindow(FALSE);
	}
	else {
		pDC = (CStatic *)GetDlgItem(IDC_SAVE_FILE);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_BRIGHT);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_DIM);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_MULTI);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_DIVISION);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_AND);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_OR);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_XOR);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_NEG);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_POSTER_RASING);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_STRETCHING);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_END_IN);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_PARABOLA_CAP);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_PARABOLA_CUP);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_HIST);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_HIST_EQUAL);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_VERTICAL_EDGE);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_HORIZONTAL_EDGE);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_HORIZONTAL_SOBEL);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_SUB_EDGE);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_SIMILAR_EDGE);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_HORIZONTAL_ROBERTS);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_HORIZONTAL_PREWITT);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_VERTICAL_ROBERTS);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_VERTICAL_PREWITT);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_VERTICAL_SOBEL);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_EMBOSSING);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_SHARP1);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_SHARP2);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_BLUR);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_ZOOMIN1);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_ZOOMIN2);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_ZOOMOUT1);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_ZOOMOUT2);
		pDC->EnableWindow(TRUE);

		pDC = (CStatic *)GetDlgItem(IDC_EXTENSION_FUNC);
		pDC->EnableWindow(TRUE);
	}
}

void CImageProcDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString str;

	if (pScrollBar)
	{
		// 어떤 슬라이더인지 검사
		if (pScrollBar == (CScrollBar*) & m_Slider_C_R)
			m_edit_R = (unsigned char)m_Slider_C_R.GetPos();
		str.Format(_T("%d"), m_edit_R);
		m_edit_C_R.SetWindowTextW(str);

		if (pScrollBar == (CScrollBar*) & m_Slider_C_G)
			m_edit_G = (unsigned char)m_Slider_C_G.GetPos();
		str.Format(_T("%d"), m_edit_G);
		m_edit_C_G.SetWindowTextW(str);

		if (pScrollBar == (CScrollBar*) & m_Slider_C_B)
			m_edit_B = (unsigned char)m_Slider_C_B.GetPos();
		str.Format(_T("%d"), m_edit_B);
		m_edit_C_B.SetWindowTextW(str);
	}
	
	// 존나 깜빡임
	pDoc.update_Extension_Func(m_edit_R, m_edit_G, m_edit_B);
	Invalidate(FALSE);

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CImageProcDlg::OnEnChangeEditR()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int num_R;
	CString str;

	m_edit_C_R.GetWindowTextW(str);
	num_R = _wtoi(str);
	m_Slider_C_R.SetPos(num_R);
}


void CImageProcDlg::OnEnChangeEditG()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int num_G;
	CString str;
	m_edit_C_G.GetWindowTextW(str);
	num_G = _wtoi(str);
	m_Slider_C_G.SetPos(num_G);
}


void CImageProcDlg::OnEnChangeEditB()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int num_B;
	CString str;

	m_edit_C_B.GetWindowTextW(str);
	num_B = _wtoi(str);
	m_Slider_C_B.SetPos(num_B);
}


void CImageProcDlg::OnBnClickedReturn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pDoc.OnBnClickedReturn();

	m_Slider_C_R.SetPos(0);
	m_Slider_C_G.SetPos(0);
	m_Slider_C_B.SetPos(0);

	Invalidate();
}


void CImageProcDlg::OnBnClickedTempSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pDoc.OnBnClickedTempSave();

	Invalidate();
}


void CImageProcDlg::OnBnClickedAnd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CConstant1Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedAnd(dlg.m_Constant);

	Invalidate();
}


void CImageProcDlg::OnBnClickedOr()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CConstant1Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedOr(dlg.m_Constant);

	Invalidate();
}


void CImageProcDlg::OnBnClickedXor()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CConstant1Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedXor(dlg.m_Constant);

	Invalidate();
}


void CImageProcDlg::OnBnClickedParabolaCap()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pDoc.OnBnClickedParabolaCap();

	Invalidate();
}


void CImageProcDlg::OnBnClickedParabolaCup()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pDoc.OnBnClickedParabolaCup();

	Invalidate();
}


void CImageProcDlg::OnBnClickedStretching()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CConstant2Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedStretching(dlg.m_Constant2_1, dlg.m_Constant2_2);

	Invalidate();
}


void CImageProcDlg::OnBnClickedHist()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pDoc.OnBnClickedHist();

	Invalidate();
}


void CImageProcDlg::OnBnClickedHistEqual()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pDoc.OnBnClickedHistEqual();

	Invalidate();
}


void CImageProcDlg::OnBnClickedEndIn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CConstant2Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedEndIn(dlg.m_Constant2_1, dlg.m_Constant2_2);

	Invalidate();
}


void CImageProcDlg::OnBnClickedVerticalEdge()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pDoc.OnBnClickedVerticalEdge();

	Invalidate();
}


void CImageProcDlg::OnBnClickedHorizontalEdge()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pDoc.OnBnClickedHorizontalEdge();

	Invalidate();
}


void CImageProcDlg::OnBnClickedSimilarEdge()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pDoc.OnBnClickedSimilarEdge();

	Invalidate();
}


void CImageProcDlg::OnBnClickedSubEdge()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pDoc.OnBnClickedSubEdge();

	Invalidate();
}


void CImageProcDlg::OnBnClickedHorizontalRoberts()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pDoc.OnBnClickedHorizontalRoberts();

	Invalidate();
}


void CImageProcDlg::OnBnClickedVerticalRoberts()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pDoc.OnBnClickedVerticalRoberts();

	Invalidate();
}


void CImageProcDlg::OnBnClickedHorizontalPrewitt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pDoc.OnBnClickedHorizontalPrewitt();

	Invalidate();
}


void CImageProcDlg::OnBnClickedVerticalPrewitt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pDoc.OnBnClickedVerticalPrewitt();

	Invalidate();
}


void CImageProcDlg::OnBnClickedHorizontalSobel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pDoc.OnBnClickedHorizontalSobel();

	Invalidate();
}


void CImageProcDlg::OnBnClickedVerticalSobel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pDoc.OnBnClickedVerticalSobel();

	Invalidate();
}


void CImageProcDlg::OnBnClickedSharp1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pDoc.OnBnClickedSharp1();

	Invalidate();
}


void CImageProcDlg::OnBnClickedSharp2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pDoc.OnBnClickedSharp2();

	Invalidate();
}


void CImageProcDlg::OnBnClickedBlur()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pDoc.OnBnClickedBlur();

	Invalidate();
}


void CImageProcDlg::OnBnClickedEmbossing()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pDoc.OnBnClickedEmbossing();

	Invalidate();
}


void CImageProcDlg::OnBnClickedZoomin1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CConstant1Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedZoomin1(dlg.m_Constant);

	Invalidate();
}


void CImageProcDlg::OnBnClickedZoomin2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CConstant1Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedZoomin2(dlg.m_Constant);

	Invalidate();
}


void CImageProcDlg::OnBnClickedZoomout1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CConstant1Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedZoomout1(dlg.m_Constant);

	Invalidate();
}


void CImageProcDlg::OnBnClickedZoomout2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CConstant1Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedZoomout2(dlg.m_Constant);

	Invalidate();
}


void CImageProcDlg::OnBnClickedPosterRasing()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CConstant1Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedPosterRasing(dlg.m_Constant);

	Invalidate();
}
