
// CreditCardGeneratorDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "CreditCardGenerator.h"
#include "CreditCardGeneratorDlg.h"
#include "afxdialogex.h"
#include "resource.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
    m_cardBrands = { L"Mir",L"Maestro", L"American Express", L"Master Card", L"Visa", L"China Union Pay" };
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
    ON_EN_CHANGE(IDC_EDIT_CNUMP2, &CCreditCardGeneratorDlg::OnEnChangeEditCnump2)
    ON_EN_CHANGE(IDC_EDIT_CNUMP1, &CCreditCardGeneratorDlg::OnEnChangeEditCnump1)
    ON_EN_CHANGE(IDC_EDIT_CNUMP3, &CCreditCardGeneratorDlg::OnEnChangeEditCnump3)
    ON_EN_CHANGE(IDC_EDIT_CNUMP4, &CCreditCardGeneratorDlg::OnEnChangeEditCnump4)
    ON_STN_CLICKED(IDC_STATIC_STATUS, &CCreditCardGeneratorDlg::OnStnClickedStaticStatus)
END_MESSAGE_MAP()

bool SetImage(CStatic* pPicCtrl, CString path)
{
    CImage image;
    if (SUCCEEDED(image.Load(path)))
    {
        HBITMAP hBmp = image.Detach();
        pPicCtrl->SetBitmap(hBmp);
        return true;
    }
    else
    {
        return false;
    }

}
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
    this->SetBackgroundColor(RGB(255,255,255));
    CEdit* cardNumP1 = static_cast<CEdit*>(GetDlgItem(IDC_EDIT_CNUMP1));
    CEdit* cardNumP2 = static_cast<CEdit*>(GetDlgItem(IDC_EDIT_CNUMP2));
    CEdit* cardNumP3 = static_cast<CEdit*>(GetDlgItem(IDC_EDIT_CNUMP3));
    CEdit* cardNumP4 = static_cast<CEdit*>(GetDlgItem(IDC_EDIT_CNUMP4));
    CStatic* pPicCtrl = (CStatic*)GetDlgItem(IDC_PIC_FRONT);
    if (cardNumP1 || cardNumP2 || cardNumP3 || cardNumP4 || pPicCtrl)
    {
        cardNumP1->SetLimitText(4);
        cardNumP2->SetLimitText(4);
        cardNumP3->SetLimitText(4);
        cardNumP4->SetLimitText(4);
        //SetImage(pPicCtrl, L".\\res\\GenericCard.png");
    }

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


void CCreditCardGeneratorDlg::OnBnClickedButtonGenerate()
{
    // TODO: Add your control notification handler code here
}

CString CCreditCardGeneratorDlg::RetrieveCardNumFromControls()
{
    CEdit* cardNumP1 = static_cast<CEdit*>(GetDlgItem(IDC_EDIT_CNUMP1));
    CEdit* cardNumP2 = static_cast<CEdit*>(GetDlgItem(IDC_EDIT_CNUMP2));
    CEdit* cardNumP3 = static_cast<CEdit*>(GetDlgItem(IDC_EDIT_CNUMP3));
    CEdit* cardNumP4 = static_cast<CEdit*>(GetDlgItem(IDC_EDIT_CNUMP4));

    CString buffer;
    CString wholeNum;
    cardNumP1->GetWindowTextW(buffer);
    wholeNum += buffer;
    cardNumP2->GetWindowTextW(buffer);
    wholeNum += buffer;
    cardNumP3->GetWindowTextW(buffer);
    wholeNum += buffer;
    cardNumP4->GetWindowTextW(buffer);
    wholeNum += buffer;

    return wholeNum;
}

void CCreditCardGeneratorDlg::ValidateCardNumber()
{
    auto pStaticStatus = GetDlgItem(IDC_STATIC_STATUS);
    if (!pStaticStatus)
    {
        return;
    }

    CString cardNumber = RetrieveCardNumFromControls();
    auto pEditBrandTitle = GetDlgItem(IDC_EDIT_BRAND);

    if (cardNumber.IsEmpty())
    {
        MessageBox(L"Enter card number!");
        return;
    }
    if (IsLuhnValid(cardNumber))
    {
        //MessageBox(L"Valid");
        pStaticStatus->SetWindowTextW(L"Valid");
    }
    else
    {
        //MessageBox(L"Not valid");
        pStaticStatus->SetWindowTextW(L"Not valid");
    }
};

void CCreditCardGeneratorDlg::OnBnClickedButtonIsvalid()
{
    ValidateCardNumber();
}

bool CCreditCardGeneratorDlg::ChangeImageOfStaticControl(const CString& FrontImagePath, const CString& BackImagePath)
{
    // Get pointers to the static controls
    CStatic* pCardFront = static_cast<CStatic*>(GetDlgItem(IDC_PIC_FRONT));
    if (!pCardFront)
    {
        return false; // One or both static controls are not found
    }

    // Load the front image
    CImage imageFront;
    if (imageFront.Load(FrontImagePath) != S_OK)
    {
        return false; // Failed to load front image
    }

    // Get the size of the static controls
    CRect rect;
    pCardFront->GetClientRect(&rect);
    int width = rect.Width();
    int height = rect.Height();

    // Create compatible memory DC for front image
    CDC memDCFront;
    memDCFront.CreateCompatibleDC(nullptr);
    CBitmap bitmapFront;
    bitmapFront.CreateCompatibleBitmap(&memDCFront, width, height);
    CBitmap* pOldBitmapFront = memDCFront.SelectObject(&bitmapFront);
    imageFront.StretchBlt(memDCFront, 0, 0, width, height, 0, 0, imageFront.GetWidth(), imageFront.GetHeight(), SRCCOPY);
    memDCFront.SelectObject(pOldBitmapFront);
    pCardFront->SetBitmap((HBITMAP)bitmapFront);

}

bool CCreditCardGeneratorDlg::IsLuhnValid(const CString& number)
{
    if (number.IsEmpty())
    {
        return false;
    }
    int sum = 0;
    bool alternate = false;
    for (int i = number.GetLength() - 1; i >= 0; --i) {
        int digit = number[i] - '0';
        if (alternate) {
            digit *= 2;
            if (digit > 9) {
                digit -= 9;
            }
        }
        sum += digit;
        alternate = !alternate;
    }
    return (sum % 10 == 0);
}

void CCreditCardGeneratorDlg::OnEnChangeEditCnump2()
{
    if (IsAllPartsFilled())
    {
        OnBnClickedButtonIsvalid();
    }
}

void CCreditCardGeneratorDlg::SetCardBrandTitle(const CString & firstPart) 
{
    auto pEditBrandTitle = GetDlgItem(IDC_EDIT_BRAND);
    if (!pEditBrandTitle)
    {
        return;
    }

    int valueToCheck = firstPart[0];

    switch (valueToCheck)
    {
    case 50:
        pEditBrandTitle->SetWindowTextW(L"Mir");
        break;
    case 51:
        pEditBrandTitle->SetWindowTextW(L"American Express");
        break;
    case 52:
        pEditBrandTitle->SetWindowTextW(L"Visa");
        break;
    case 53:
        pEditBrandTitle->SetWindowTextW(L"MasterCard");
        break;
    case 54:
        pEditBrandTitle->SetWindowTextW(L"Union Pay");
        break;
    default:
        pEditBrandTitle->SetWindowTextW(L"Unknown");
        break;
    }


}

void CCreditCardGeneratorDlg::OnEnChangeEditCnump1()
{
    CEdit* cardNumP1 = static_cast<CEdit*>(GetDlgItem(IDC_EDIT_CNUMP1));
    if (!cardNumP1)
    {
        return;
    }
    CString firstPartOfNum;
    cardNumP1->GetWindowText(firstPartOfNum);

    SetCardBrandTitle(firstPartOfNum);

    if (IsAllPartsFilled())
    {
        OnBnClickedButtonIsvalid();
    }

}


void CCreditCardGeneratorDlg::OnBnClickedBtnExit()
{
    this->EndDialog(IDOK);
}

bool CCreditCardGeneratorDlg::IsAllPartsFilled()
{
    CEdit* cardNumP1 = static_cast<CEdit*>(GetDlgItem(IDC_EDIT_CNUMP1));
    CEdit* cardNumP2 = static_cast<CEdit*>(GetDlgItem(IDC_EDIT_CNUMP2));
    CEdit* cardNumP3 = static_cast<CEdit*>(GetDlgItem(IDC_EDIT_CNUMP3));
    CEdit* cardNumP4 = static_cast<CEdit*>(GetDlgItem(IDC_EDIT_CNUMP4));

    CString firstPart;
    CString secondPart;
    CString thirdPart;
    CString forthPart;

    cardNumP1->GetWindowTextW(firstPart);
    cardNumP2->GetWindowTextW(secondPart);
    cardNumP3->GetWindowTextW(thirdPart);
    cardNumP4->GetWindowTextW(forthPart);

    if (firstPart.GetLength() == 4 &&
        secondPart.GetLength() == 4 &&
        thirdPart.GetLength() == 4 &&
        forthPart.GetLength() == 4
        )
    {
        return true;
    }
    else
    {
        return false;
    }


}

void CCreditCardGeneratorDlg::OnBnClickedBtnOpen()
{
    std::ifstream inputFile("example.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open file!" << std::endl;
    }
}


void CCreditCardGeneratorDlg::OnEnChangeEditCnump3()
{
    if (IsAllPartsFilled())
    {
        OnBnClickedButtonIsvalid();
    }
}


void CCreditCardGeneratorDlg::OnEnChangeEditCnump4()
{
    if (IsAllPartsFilled())
    {
        OnBnClickedButtonIsvalid();
    }
}


void CCreditCardGeneratorDlg::OnStnClickedStaticStatus()
{
    // TODO: Add your control notification handler code here
}
