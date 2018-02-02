
// Image ProcDlg.cpp : ���� ����
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


// CImageProcDlg ��ȭ ����
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


// CImageProcDlg �޽��� ó����

BOOL CImageProcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	// UI ����
	int frame_width = 1280;
	int frame_height = 760;
	CStatic * pDC;

	// ���� ���̾�α� ������ �� ��ġ ����
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	int x = (width / 2) - (frame_width / 2);
	int y = (height / 2) - (frame_height / 2);
	this->SetWindowPos(NULL, x, y, frame_width, frame_height, NULL);
	
	// ���� ��Ʈ�� ��ġ ����
	int pic_control_width = 512 + 10;
	int pic_control_height = 512 + 10;

	pDC = (CStatic *)GetDlgItem(IDC_PIC_CONTROL1);
	pDC->SetWindowPos(NULL, 5, 5, pic_control_width, pic_control_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_PIC_CONTROL2);
	pDC->SetWindowPos(NULL, pic_control_width + 10, 5, pic_control_width, pic_control_height, NULL);

	// ��ư ��ġ ����
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

	// �� �� ����Ʈ �ؽ�Ʈ ��ġ ����
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

	// �����̴� ��ġ ����
	int slider_width = (btn_width * 2) / 3;
	int slider_height = 256;

	pDC = (CStatic *)GetDlgItem(IDC_SLIDER_R);
	pDC->SetWindowPos(NULL, 1069 + 5, 35, slider_width, slider_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_SLIDER_G);
	pDC->SetWindowPos(NULL, 1069 + slider_width + 5, 35, slider_width, slider_height, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_SLIDER_B);
	pDC->SetWindowPos(NULL, 1069 + (slider_width * 2) + 5, 35, slider_width, slider_height, NULL);

	// �׷�ڽ� ��ġ ����
	pDC = (CStatic *)GetDlgItem(IDC_IMAGE_PROC_GROUP1);
	pDC->SetWindowPos(NULL, 5, pic_control_height + 5, frame_width - 30, (btn_height * 3) + 40, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_IMAGE_POINT_PROC_GROUP);
	pDC->SetWindowPos(NULL, 10, pic_control_height + 15, (btn_width * 5) + 35, (btn_height * 3) + 20, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_IMAGE_AREA_PROC_GROUP);
	pDC->SetWindowPos(NULL, 520, pic_control_height + 15, (btn_width * 6) + 40, (btn_height * 3) + 20, NULL);

	pDC = (CStatic *)GetDlgItem(IDC_IMAGE_GEOMETRY_PROC_GROUP);
	pDC->SetWindowPos(NULL, 1128, pic_control_height + 15, btn_width + 25, (btn_height * 3) + 20, NULL);

	// �����̴� ��Ʈ�� �ʱ�ȭ
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

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CImageProcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

		unsigned char R, G, B;

		CDC * p = m_PicControl1.GetWindowDC();
		CDC memDC;
		CBitmap * pOldBitmap;
		CBitmap bitmap;					// �޸� DC ����

		// �Է� �̹��� ����
		memDC.CreateCompatibleDC(p);	// ��ü ���� (ȣȯ��)
										// ȭ��DC�� ȣȯ�Ǵ� ��Ʈ�� ����
		bitmap.CreateCompatibleBitmap(p, pDoc.m_width, pDoc.m_height);

		pOldBitmap = memDC.SelectObject(&bitmap);

		memDC.PatBlt(0, 0, pDoc.m_width, pDoc.m_height, WHITENESS);	//�ʱ�ȭ
															// �޸𸮿� ����ϱ�
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


		// ��� �̹��� ����
		p = m_PicControl2.GetWindowDC();

		memDC.CreateCompatibleDC(p);

		// ȭ�� DC�� ȣȯ�Ǵ� bitmap ����
		bitmap.CreateCompatibleBitmap(p, pDoc.m_Re_width, pDoc.m_Re_height);

		pOldBitmap = memDC.SelectObject(&bitmap);

		memDC.PatBlt(0, 0, pDoc.m_Re_width, pDoc.m_Re_height, WHITENESS);	//�ʱ�ȭ
																	// �޸𸮿� ����ϱ�

		// Memory�� ���
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

		// Memory DC -> Display DC�� ����(���)
		p->BitBlt(5, 5, pDoc.m_Re_width, pDoc.m_Re_height, &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(pOldBitmap);
		memDC.DeleteDC();
		bitmap.DeleteObject();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CImageProcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CImageProcDlg::OnBnClickedOpenFile()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pDoc.OnBnClickedCloseDialog();
}

void CImageProcDlg::OnBnClickedEqualImage()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	// �����̴� ��Ʈ�� ��ġ �ʱ�ȭ
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CConstant1Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedBright(dlg.m_Constant);

	Invalidate();
}


void CImageProcDlg::OnBnClickedDim()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CConstant1Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedDim(dlg.m_Constant);

	Invalidate();
}


void CImageProcDlg::OnBnClickedMulti()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CConstant1Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedMulti(dlg.m_Constant);

	Invalidate();
}


void CImageProcDlg::OnBnClickedDivision()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CConstant1Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedDivision(dlg.m_Constant);

	Invalidate();
}


void CImageProcDlg::OnBnClickedNeg()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pDoc.OnBnClickedNeg();

	Invalidate();
}


void CImageProcDlg::enableButton(bool flag)
{
	// ��ư Ȱ��ȭ
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CString str;

	if (pScrollBar)
	{
		// � �����̴����� �˻�
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
	
	// ���� ������
	pDoc.update_Extension_Func(m_edit_R, m_edit_G, m_edit_B);
	Invalidate(FALSE);

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CImageProcDlg::OnEnChangeEditR()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int num_R;
	CString str;

	m_edit_C_R.GetWindowTextW(str);
	num_R = _wtoi(str);
	m_Slider_C_R.SetPos(num_R);
}


void CImageProcDlg::OnEnChangeEditG()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int num_G;
	CString str;
	m_edit_C_G.GetWindowTextW(str);
	num_G = _wtoi(str);
	m_Slider_C_G.SetPos(num_G);
}


void CImageProcDlg::OnEnChangeEditB()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int num_B;
	CString str;

	m_edit_C_B.GetWindowTextW(str);
	num_B = _wtoi(str);
	m_Slider_C_B.SetPos(num_B);
}


void CImageProcDlg::OnBnClickedReturn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pDoc.OnBnClickedReturn();

	m_Slider_C_R.SetPos(0);
	m_Slider_C_G.SetPos(0);
	m_Slider_C_B.SetPos(0);

	Invalidate();
}


void CImageProcDlg::OnBnClickedTempSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pDoc.OnBnClickedTempSave();

	Invalidate();
}


void CImageProcDlg::OnBnClickedAnd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CConstant1Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedAnd(dlg.m_Constant);

	Invalidate();
}


void CImageProcDlg::OnBnClickedOr()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CConstant1Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedOr(dlg.m_Constant);

	Invalidate();
}


void CImageProcDlg::OnBnClickedXor()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CConstant1Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedXor(dlg.m_Constant);

	Invalidate();
}


void CImageProcDlg::OnBnClickedParabolaCap()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pDoc.OnBnClickedParabolaCap();

	Invalidate();
}


void CImageProcDlg::OnBnClickedParabolaCup()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pDoc.OnBnClickedParabolaCup();

	Invalidate();
}


void CImageProcDlg::OnBnClickedStretching()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CConstant2Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedStretching(dlg.m_Constant2_1, dlg.m_Constant2_2);

	Invalidate();
}


void CImageProcDlg::OnBnClickedHist()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pDoc.OnBnClickedHist();

	Invalidate();
}


void CImageProcDlg::OnBnClickedHistEqual()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pDoc.OnBnClickedHistEqual();

	Invalidate();
}


void CImageProcDlg::OnBnClickedEndIn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CConstant2Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedEndIn(dlg.m_Constant2_1, dlg.m_Constant2_2);

	Invalidate();
}


void CImageProcDlg::OnBnClickedVerticalEdge()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pDoc.OnBnClickedVerticalEdge();

	Invalidate();
}


void CImageProcDlg::OnBnClickedHorizontalEdge()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pDoc.OnBnClickedHorizontalEdge();

	Invalidate();
}


void CImageProcDlg::OnBnClickedSimilarEdge()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pDoc.OnBnClickedSimilarEdge();

	Invalidate();
}


void CImageProcDlg::OnBnClickedSubEdge()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pDoc.OnBnClickedSubEdge();

	Invalidate();
}


void CImageProcDlg::OnBnClickedHorizontalRoberts()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pDoc.OnBnClickedHorizontalRoberts();

	Invalidate();
}


void CImageProcDlg::OnBnClickedVerticalRoberts()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pDoc.OnBnClickedVerticalRoberts();

	Invalidate();
}


void CImageProcDlg::OnBnClickedHorizontalPrewitt()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pDoc.OnBnClickedHorizontalPrewitt();

	Invalidate();
}


void CImageProcDlg::OnBnClickedVerticalPrewitt()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pDoc.OnBnClickedVerticalPrewitt();

	Invalidate();
}


void CImageProcDlg::OnBnClickedHorizontalSobel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pDoc.OnBnClickedHorizontalSobel();

	Invalidate();
}


void CImageProcDlg::OnBnClickedVerticalSobel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pDoc.OnBnClickedVerticalSobel();

	Invalidate();
}


void CImageProcDlg::OnBnClickedSharp1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pDoc.OnBnClickedSharp1();

	Invalidate();
}


void CImageProcDlg::OnBnClickedSharp2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pDoc.OnBnClickedSharp2();

	Invalidate();
}


void CImageProcDlg::OnBnClickedBlur()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pDoc.OnBnClickedBlur();

	Invalidate();
}


void CImageProcDlg::OnBnClickedEmbossing()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pDoc.OnBnClickedEmbossing();

	Invalidate();
}


void CImageProcDlg::OnBnClickedZoomin1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CConstant1Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedZoomin1(dlg.m_Constant);

	Invalidate();
}


void CImageProcDlg::OnBnClickedZoomin2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CConstant1Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedZoomin2(dlg.m_Constant);

	Invalidate();
}


void CImageProcDlg::OnBnClickedZoomout1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CConstant1Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedZoomout1(dlg.m_Constant);

	Invalidate();
}


void CImageProcDlg::OnBnClickedZoomout2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CConstant1Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedZoomout2(dlg.m_Constant);

	Invalidate();
}


void CImageProcDlg::OnBnClickedPosterRasing()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CConstant1Dlg dlg;
	INT_PTR yn = dlg.DoModal();

	if (yn != IDOK) return;

	pDoc.OnBnClickedPosterRasing(dlg.m_Constant);

	Invalidate();
}
