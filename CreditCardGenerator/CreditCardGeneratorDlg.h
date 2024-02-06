
// CreditCardGeneratorDlg.h : header file
//

#pragma once
#include <vector>

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
	bool PopulateBrandCombo();
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	bool ChangeImageOfStaticControl(const CString& FrontImagePath, const CString& BackImagePath);
	afx_msg void OnCbnSelchangeComboBrand();
	afx_msg void OnBnClickedButtonGenerate();
	afx_msg void OnBnClickedButtonIsvalid();
	bool ChangeImageOfStaticControl(const CString& imagePath);
};
