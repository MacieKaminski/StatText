
// StatTekst2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CStatTekst2App:
// See StatTekst2.cpp for the implementation of this class
//

class CStatTekst2App : public CWinApp
{
public:
	CStatTekst2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CStatTekst2App theApp;
