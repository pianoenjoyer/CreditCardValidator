#pragma once

#include <vector>

enum class CardBrand
{
    Unknown,
    Mir,
    Maestro,
    American_Express,
    MasterCard,
    Visa,
    China_Union_Pay
};

// CCreditCardGeneratorDlg dialog
class CCreditCardGeneratorDlg : public CDialogEx
{

    // Construction
public:
    CCreditCardGeneratorDlg(CWnd* pParent = nullptr);	// standard constructor

    // Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_CREDITCARDGENERATOR_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


    // Implementation
protected:
    HICON m_hIcon;
    std::vector<CString> m_cardBrands;
    CString m_pathVisaFront;
    CString m_pathVisaBack;
    CString m_pathMasterCardFront;
    CString m_pathMasterCardBack;
    // Generated message map functions
    void ValidateCardNumber();
    void SetCardBrandTitle(const CString & firstPart);
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    bool IsLuhnValid(const CString& number);
    bool ChangeImageOfStaticControl(const CString& FrontImagePath, const CString& BackImagePath);
    CString RetrieveCardNumFromControls();
    bool IsAllPartsFilled();
    afx_msg void OnBnClickedButtonGenerate();
    afx_msg void OnBnClickedButtonIsvalid();
    afx_msg void OnEnChangeEditCnump2();
    afx_msg void OnEnChangeEditCnump1();
    afx_msg void OnBnClickedBtnExit();
    afx_msg void OnBnClickedBtnOpen();
    afx_msg void OnEnChangeEditCnump3();
    afx_msg void OnEnChangeEditCnump4();
    afx_msg void OnStnClickedStaticStatus();
};
