
// StatTekst2Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "StatTekst2.h"
#include "StatTekst2Dlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cctype>
#include <string>
#include <filesystem>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using std::vector;
using std::ifstream;
using std::ofstream;
using std::istreambuf_iterator;
using std::string;
using std::filesystem::recursive_directory_iterator;
using std::filesystem::path;

int chars{};
int words{};
int lines{};
int ssentences{};
int charswithoutspaces{};
int spaces{};
int whitespacechars{};
int punctuations{};
int digits{};
int letters{};
vector <char> text{};


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

};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


// CStatTekst2Dlg dialog



CStatTekst2Dlg::CStatTekst2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STATTEKST2_DIALOG, pParent)
	, numberOfChars(0)
	, numberOfLines(0)
	, numberOfWords(0)
	, numberOfCharsWithoutSpaces(0)
	, numberOfSentences(0)
	, numberOfWhiteSpaceChars(0)
	, numberOfPunctuationChars(0)
	, numberOfDigits(0)
	, numberOfAlphaChars(0)
	, numberOfSpaces(0)
	, includeTxt(FALSE)
	, includeCpp(FALSE)
	, includeH(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStatTekst2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Text(pDX, IDC_EDIT1, TextWindow);
	DDX_Text(pDX, IDC_MFCEDITBROWSE1, PathToInFolder);
	DDX_Text(pDX, NumberOfChars, numberOfChars);
	DDX_Text(pDX, NumberOfLines, numberOfLines);
	DDX_Text(pDX, NumberOfWords, numberOfWords);
	DDX_Text(pDX, NumberOfCharsWithoutSpaces, numberOfCharsWithoutSpaces);
	DDX_Text(pDX, NumberOfSentences, numberOfSentences);
	DDX_Text(pDX, NumberOfWhiteSpaceChars, numberOfWhiteSpaceChars);
	DDX_Text(pDX, NumberOfPunctuationChars, numberOfPunctuationChars);
	DDX_Text(pDX, NumberOfDigits, numberOfDigits);
	DDX_Text(pDX, NumberOfAlphaChars, numberOfAlphaChars);
	DDX_Text(pDX, NumberOfSpaces, numberOfSpaces);
	DDX_Check(pDX, IDC_CHECK1, includeTxt);
	DDX_Check(pDX, IDC_CHECK2, includeCpp);
	DDX_Check(pDX, IDC_CHECK3, includeH);
}

BEGIN_MESSAGE_MAP(CStatTekst2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_MFCEDITBROWSE1, &CStatTekst2Dlg::OnEnChangeMfceditbrowse1)
	ON_EN_CHANGE(NumberOfLines, &CStatTekst2Dlg::OnEnChangeNumberoflines)
	ON_EN_CHANGE(NumberOfWords, &CStatTekst2Dlg::OnEnChangeNumberofwords)
	ON_EN_CHANGE(NumberOfChars, &CStatTekst2Dlg::OnEnChangeNumberofchars)
	ON_BN_CLICKED(Stats, &CStatTekst2Dlg::OnBnClickedStats)
	ON_EN_CHANGE(NumberOfPunctuationChars, &CStatTekst2Dlg::OnEnChangeNumberofpunctuationchars)
	ON_EN_CHANGE(NumberOfWhiteSpaceChars, &CStatTekst2Dlg::OnEnChangeNumberofwhitespacechars)
	ON_EN_CHANGE(NumberOfSentences, &CStatTekst2Dlg::OnEnChangeNumberofsentences)
	ON_EN_CHANGE(NumberOfCharsWithoutSpaces, &CStatTekst2Dlg::OnEnChangeNumberofcharswithoutspaces)
	ON_EN_CHANGE(NumberOfDigits, &CStatTekst2Dlg::OnEnChangeNumberofdigits)
	ON_BN_CLICKED(IDC_CHECK2, &CStatTekst2Dlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK1, &CStatTekst2Dlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK3, &CStatTekst2Dlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDOK, &CStatTekst2Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CStatTekst2Dlg message handlers

BOOL CStatTekst2Dlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStatTekst2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CStatTekst2Dlg::OnPaint()
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
HCURSOR CStatTekst2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStatTekst2Dlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	
}


void CStatTekst2Dlg::OnEnChangeMfceditbrowse1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	UpdateData(TRUE);

	UpdateData(FALSE);
}

void statsloop(vector <char>& text)
{
	int iterator{};

	for (char i : text)
	{
		if (isprint(i))
		{
			chars++;
		}

		if (isgraph(i))
		{
			charswithoutspaces++;
		}

		if (i == ' ')
		{
			spaces++;
		}

		if (i == '\n')
		{
			lines++;
		}

		if (isspace(i))
		{
			whitespacechars++;
		}

		if (ispunct(i))
		{
			punctuations++;
		}

		if (isdigit(i))
		{
			digits++;
		}

		if (isalpha(i))
		{
			letters++;
		}

		iterator++;

		if (isalnum(text[iterator - 1]) && !isalnum(text[iterator]))
		{
			words++;
		}

		if (iterator >= 2)
		{
			if ((text[iterator - 2] == '.') && isspace(text[iterator - 1]))
			{
				ssentences++;
			}

			if ((text[iterator - 2] == '!') && isspace(text[iterator - 1]))
			{
				ssentences++;
			}

			if ((text[iterator - 2] == '?') && isspace(text[iterator - 1]))
			{
				ssentences++;
			}
		}
	}

	lines += 1;
}

void getstats(string& pathtofolder, BOOL& includeTxt, BOOL& includeCpp, BOOL& includeH)
{

	for (const auto& file : recursive_directory_iterator(pathtofolder))
	{
		if (path(file).extension() == ".txt" && includeTxt)
		{
			ifstream infile(file);
			vector <char> text((istreambuf_iterator<char>(infile)), (std::istreambuf_iterator<char>()));
			statsloop(text);
		}

		if (path(file).extension() == ".cpp" && includeCpp)
		{
			ifstream infile(file);
			vector <char> text((istreambuf_iterator<char>(infile)), (std::istreambuf_iterator<char>()));
			statsloop(text);
		}

		if (path(file).extension() == ".h" && includeH)
		{
			ifstream infile(file);
			vector <char> text((istreambuf_iterator<char>(infile)), (std::istreambuf_iterator<char>()));
			statsloop(text);
		}
	}
}

void CStatTekst2Dlg::OnBnClickedStats()
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

	chars = { 0 };
	words = { 0 };
	lines = { 0 };
	ssentences = { 0 };
	charswithoutspaces = { 0 };
	spaces = { 0 };
	whitespacechars = { 0 };
	punctuations = { 0 };
	digits = { 0 };
	letters = { 0 };

	CT2CA pszConvertedAnsiString(PathToInFolder);
	// construct a std::string using the LPCSTR input
	string pathtofolder(pszConvertedAnsiString);

	if (pathtofolder.size() != 0)
	{
		getstats(pathtofolder, includeTxt, includeCpp, includeH);
	}

	numberOfLines = lines;
	numberOfChars = chars;
	numberOfWords = words;
	numberOfCharsWithoutSpaces = charswithoutspaces;
	numberOfSentences = ssentences;
	numberOfWhiteSpaceChars = whitespacechars;
	numberOfPunctuationChars = punctuations;
	numberOfDigits = digits;
	numberOfSpaces = spaces;
	numberOfAlphaChars = letters;


	UpdateData(FALSE);
}

void CStatTekst2Dlg::OnEnChangeNumberoflines()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	UpdateData(TRUE);

	numberOfLines;

	UpdateData(FALSE);
}


void CStatTekst2Dlg::OnEnChangeNumberofwords()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	UpdateData(TRUE);

	numberOfWords;

	UpdateData(FALSE);
}


void CStatTekst2Dlg::OnEnChangeNumberofchars()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	UpdateData(TRUE);

	numberOfChars;

	UpdateData(FALSE);
}


void CStatTekst2Dlg::OnEnChangeNumberofpunctuationchars()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	UpdateData(TRUE);

	numberOfPunctuationChars;

	UpdateData(FALSE);
}


void CStatTekst2Dlg::OnEnChangeNumberofwhitespacechars()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	UpdateData(TRUE);

	numberOfWhiteSpaceChars;

	UpdateData(FALSE);
}


void CStatTekst2Dlg::OnEnChangeNumberofsentences()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	UpdateData(TRUE);

	numberOfSentences;

	UpdateData(FALSE);
}


void CStatTekst2Dlg::OnEnChangeNumberofcharswithoutspaces()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	UpdateData(TRUE);

	numberOfCharsWithoutSpaces;

	UpdateData(FALSE);
}


void CStatTekst2Dlg::OnEnChangeNumberofdigits()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	UpdateData(TRUE);

	numberOfDigits;

	UpdateData(FALSE);
}

void CStatTekst2Dlg::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

	includeTxt;

	UpdateData(FALSE);
}

void CStatTekst2Dlg::OnBnClickedCheck2()
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

	includeCpp;

	UpdateData(FALSE);

}

void CStatTekst2Dlg::OnBnClickedCheck3()
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

	includeH;

	UpdateData(FALSE);
}

void CStatTekst2Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}
