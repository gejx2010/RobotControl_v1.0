// RobotControl.h : main header file for the ROBOTCONTROL application
//

#if !defined(AFX_ROBOTCONTROL_H__8FF8EA21_8342_48CB_842D_E72D4CD40CDB__INCLUDED_)
#define AFX_ROBOTCONTROL_H__8FF8EA21_8342_48CB_842D_E72D4CD40CDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRobotControlApp:
// See RobotControl.cpp for the implementation of this class
//

class CRobotControlApp : public CWinApp
{
public:
	CRobotControlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRobotControlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CRobotControlApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROBOTCONTROL_H__8FF8EA21_8342_48CB_842D_E72D4CD40CDB__INCLUDED_)
