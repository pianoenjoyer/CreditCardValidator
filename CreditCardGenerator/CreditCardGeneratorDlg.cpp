
// CreditCardGeneratorDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "CreditCardGenerator.h"
#include "CreditCardGeneratorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MASTERCARD 0
#define VISA 1

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCreditCardGeneratorDlg dialog



CCreditCardGeneratorDlg::CCreditCardGeneratorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CREDITCARDGENERATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_cardBrands = { L"MasterCard",L"Visa" };
	 m_pathVisaFront = L".\\Pictures\\VisaFront.png";
	 m_pathVisaBack = L".\\Pictures\\VisaBack.png";
	 m_pathMasterCardFront = L".\\Pictures\\MasterCardFront.png";
	 m_pathMasterCardBack = L".\\Pictures\\MasterCardBack.png";
}

void CCreditCardGeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCreditCardGeneratorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_BRAND, &CCreditCardGeneratorDlg::OnCbnSelchangeComboBrand)
	ON_BN_CLICKED(IDC_BUTTON_GENERATE, &CCreditCardGeneratorDlg::OnBnClickedButtonGenerate)
	ON_BN_CLICKED(IDC_BUTTON_ISVALID, &CCreditCardGeneratorDlg::OnBnClickedButtonIsvalid)
END_MESSAGE_MAP()


// CCreditCardGeneratorDlg message handlers

BOOL CCreditCardGeneratorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	PopulateBrandCombo();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCreditCardGeneratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCreditCardGeneratorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCreditCardGeneratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CCreditCardGeneratorDlg::PopulateBrandCombo()
{
	auto pComboBrand = (CComboBox*)GetDlgItem(IDC_COMBO_BRAND);
	if (!pComboBrand)
	{
		return false;
	}

	if (m_cardBrands.empty())
	{
		return false;
	}

	for (auto &brand : m_cardBrands)
	{
		pComboBrand->AddString(brand);
	}

	pComboBrand->SetCurSel(0);
	return true;
}

void CCreditCardGeneratorDlg::OnCbnSelchangeComboBrand()
{

	auto pComboBrand = (CComboBox*)GetDlgItem(IDC_COMBO_BRAND);
	if (!pComboBrand)
	{
		return;
	}
	int curSel = pComboBrand->GetCurSel();

	switch (curSel)
	{
		case MASTERCARD: 
			ChangeImageOfStaticControl(m_pathVisaFront, m_pathVisaBack);
		case VISA:
			ChangeImageOfStaticControl(m_pathMasterCardFront, m_pathMasterCardBack);
		default:
			break;
	}

}


void CCreditCardGeneratorDlg::OnBnClickedButtonGenerate()
{
	// TODO: Add your control notification handler code here
}


void CCreditCardGeneratorDlg::OnBnClickedButtonIsvalid()
{
	// TODO: Add your control notification handler code here
}

bool CCreditCardGeneratorDlg::ChangeImageOfStaticControl(const CString& FrontImagePath, const CString& BackImagePath)
{
	// Get a pointer to the static control
	CStatic* pCardFront = static_cast<CStatic*>(GetDlgItem(IDC_PIC_FRONT));
	CStatic* pCardBack = static_cast<CStatic*>(GetDlgItem(IDC_PIC_BACK));
	if (!pCardFront || !pCardBack)
	{
		return true;
	}

	// Load the image from the file
	CImage imageFront;
	CImage imageBack;
	if (imageFront.Load(FrontImagePath) != S_OK || imageBack.Load(BackImagePath) != S_OK)
	{
		return false;
	}

	// Get the size of the static control
	CRect rect;
	pCardFront->GetClientRect(&rect);
	int width = rect.Width();
	int height = rect.Height();
	CDC memDC;
	memDC.CreateCompatibleDC(nullptr);
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&memDC, width, height);
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);
	imageFront.StretchBlt(memDC, 0, 0, width, height, 0, 0, imageFront.GetWidth(), imageFront.GetHeight(), SRCCOPY);
	memDC.SelectObject(pOldBitmap);
	pCardFront->SetBitmap((HBITMAP)bitmap);

	pCardBack->GetClientRect(&rect);
	width = rect.Width();
	height = rect.Height();
	memDC.CreateCompatibleDC(nullptr);
	bitmap.CreateCompatibleBitmap(&memDC, width, height);
	pOldBitmap = memDC.SelectObject(&bitmap);
	imageBack.StretchBlt(memDC, 0, 0, width, height, 0, 0, imageBack.GetWidth(), imageBack.GetHeight(), SRCCOPY);
	memDC.SelectObject(pOldBitmap);
	pCardBack->SetBitmap((HBITMAP)bitmap);


}