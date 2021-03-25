
// StatTekst2Dlg.h : header file
//

#pragma once


// CStatTekst2Dlg dialog
class CStatTekst2Dlg : public CDialogEx
{
// Construction
public:
	CStatTekst2Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STATTEKST2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog(); 
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString TextWindow{};
	CString PathToInFolder{};
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeMfceditbrowse1();
	afx_msg void OnBnClickedExit();
	afx_msg void OnEnChangeNumberoflines();
	afx_msg void OnEnChangeNumberofwords();
	afx_msg void OnEnChangeNumberofchars();
	int numberOfChars{};
	int numberOfLines{};
	int numberOfWords{};
	afx_msg void OnBnClickedStats();
	int numberOfCharsWithoutSpaces{};
	int numberOfSentences{};
	int numberOfWhiteSpaceChars{};
	int numberOfPunctuationChars;
	afx_msg void OnEnChangeNumberofpunctuationchars();
	afx_msg void OnEnChangeNumberofwhitespacechars();
	afx_msg void OnEnChangeNumberofsentences();
	afx_msg void OnEnChangeNumberofcharswithoutspaces();
	afx_msg void OnEnChangeNumberofdigits();
	int numberOfDigits{};
	int numberOfAlphaChars{};
	int numberOfSpaces{};
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck3();
	BOOL includeTxt=FALSE;
	BOOL includeCpp=FALSE;
	BOOL includeH=FALSE;
	afx_msg void OnBnClickedOk();
};
